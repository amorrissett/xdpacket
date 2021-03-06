{
  # options
  buildtype ? "release",
  compiler ? "clang",
  dep_type ? "shared",
  mesonFlags ? "",

  # deps
  system ? builtins.currentSystem,
  nixpkgs ? import <nixpkgs> { inherit system; }
}:

with nixpkgs;

nixpkgs.stdenv.mkDerivation rec {
  name = "xdpacket";
  version = "0.1.0";
  outputs = [ "out" ];

  meta = with nixpkgs.stdenv.lib; {
    description = "the eXtremely Direct Packet handler";
    homepage = https://siriobalmelli.github.io/xdpacket/;
    license = licenses.gpl2;
    platforms = platforms.unix;
    maintainers = [ "https://github.com/siriobalmelli" ];
  };

  libjudy = nixpkgs.libjudy or import ./libjudy {};
  nonlibc = nixpkgs.nonlibc or import ./nonlibc {};

  inputs = [
    nixpkgs.gcc
    nixpkgs.clang
    nixpkgs.meson
    nixpkgs.ninja
    nixpkgs.pandoc
    nixpkgs.pkgconfig
    nixpkgs.dpkg
    nixpkgs.fpm
    nixpkgs.rpm
    nixpkgs.zip
  ];
  buildInputs = if ! lib.inNixShell then inputs else inputs ++ [
    nixpkgs.cscope
    nixpkgs.gdb
    nixpkgs.pahole
    nixpkgs.valgrind
    nixpkgs.which
  ];
  propagatedBuildInputs = [
    nixpkgs.libyaml
    libjudy
    nonlibc
  ];

  # just work with the current directory (aka: Git repo), no fancy tarness
  src = if lib.inNixShell then null else ./.;

  # Override the setupHook in the meson nix derviation,
  # so that meson doesn't automatically get invoked from there.
  meson = nixpkgs.pkgs.meson.overrideAttrs ( oldAttrs: rec { setupHook = ""; });

  # don't harden away position-dependent speedups for static builds
  hardeningDisable = [ "pic" "pie" ];

  # build
  mFlags = mesonFlags
    + " --buildtype=${buildtype}"
    + " -Ddep_type=${dep_type}";

  configurePhase = ''
      echo "flags: $mFlags"
      echo "prefix: $out"
      CC=${compiler} meson --prefix=$out build $mFlags
      cd build
  '';

  buildPhase = ''
      ninja
  '';
  doCheck = true;
  checkPhase = ''
      ninja test
  '';
  installPhase = ''
      ninja install
  '';

  # Build packages outside $out then move them in: fpm seems to ignore
  #+	the '-x' flag that we need to avoid packaging packages inside packages
  # NOTE also the `''` escape so that Nix will leave `${` alone (facepalms internally)
  postFixup = ''
      # manual dependency listing
      declare -A DEPS=( \
          ["deb"]="-d nonlibc -d libyaml-dev -d libjudy-dev" \
          ["rpm"]="-d nonlibc -d libyaml -d libjudy" \
          ["tar"]="" \
          ["zip"]="")

      mkdir temp
      for pk in "deb" "rpm" "tar" "zip"; do
          if ! fpm -f -t $pk -s dir -p temp/ -n $name -v $version \
              --description "${meta.description}" \
              --license "${meta.license.spdxId}" \
              --url "${meta.homepage}" \
              --maintainer "${builtins.head meta.maintainers}" \
              -x "nix-support" \
              ''${DEPS[$pk]} \
              "$out/=/"
          then
              echo "ERROR (non-fatal): could not build $pk package" >&2
          fi
      done
      mkdir -p $out/var/cache/packages
      mv -fv temp/* $out/var/cache/packages/
  '';
}
