#ifndef xdpacket_h_
#define xdpacket_h_

/*	xdpacket.h
 * Program-wide defines: include before all source files.
 * (c) 2018 Sirio Balmelli and Alan Morrissett
 */

/* variable (interface, matcher, field) names are _short_ */
#define MAXLINELEN 64

/* TCP port for xdpacket socket.
 * This is the 16bit fnv1a hash of "xdpacket"
 */
#define PORT "7044"


#endif /* xdpacket_h_ */
