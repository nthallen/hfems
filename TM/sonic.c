/* Sonic anemometer serial interface
   Written by NTA 5/9/97
 */
#include <sys/dev.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include "nortlib.h"
#include "collect.h"
#include "msg.h"
#include "oui.h"
#include "cltsrvr.h"
#include "sonic.h"

#define SONIC_REC_SIZE 35
char buf[SONIC_REC_SIZE+1];
int sonic_fd;
int buf_high, buf_low;
int chars_accepted = 0;
pid_t collect_proxy;
pid_t quit_proxy;
pid_t serdev_proxy;
send_id col_id;
static sonic_t collect_buf;
static long resynchs = 0, untransferred = 0, retransferred = 0;

void sonic_record( short U, short V, short W, short T ) {
  collect_buf.U = U;
  collect_buf.V = V;
  collect_buf.W = W;
  collect_buf.T = T;
  if ( collect_buf.transferred )
	untransferred++;
  collect_buf.transferred++;
}

static void got_collect_proxy( void ) {
  if ( collect_buf.transferred ) {
	Col_send(col_id);
	collect_buf.transferred = 0;
  } else retransferred++;
}

static void got_quit_proxy( void ) {
  msg( 0, "Resynchronized %ld times", resynchs );
  msg( 0, "Untransferred records: %ld", untransferred );
  msg( 0, "Retransferred records: %ld", retransferred );
  DONE_MSG;
  exit(0);
}

static void sonic_fillbuf( void ) {
  static armed = 0;
  unsigned n;
  
  while ( armed ) {
	pid_t who = Receive( 0, NULL, 0 );
	if ( who == collect_proxy ) got_collect_proxy();
	else if ( who == quit_proxy ) got_quit_proxy();
	else if ( who == serdev_proxy ) armed = 0;
  }
  n = ( chars_accepted >= SONIC_REC_SIZE ) ?
		1 : SONIC_REC_SIZE - chars_accepted;
  buf_high = dev_read( sonic_fd, buf, SONIC_REC_SIZE, n, 0, 0,
						serdev_proxy, &armed );
  if ( buf_high == -1 )
	msg( 2, "Error %d reading from sonic", errno );
  buf_low = 0;
}

/* sonic_getc() get a character */
static int sonic_getc( void ) {
  while ( buf_low >= buf_high ) sonic_fillbuf();
  chars_accepted++;
  return buf[buf_low++];
}

/* returns non-zero if the next character from sonic is not c */
static int sonic_not_c( int c ) {
  return ( sonic_getc() != c );
}

/* returns non-zero if input isn't of the form:
		[ -][0-9][0-9].[0-9][0-9]
   Assigns the result to *num
*/
static int sonic_not_num( signed short *num ) {
  int sign;
  int c;
  int n = 0;

  sign = sonic_getc();
  if ( sign != ' ' && sign != '-' ) return 1;
  c = sonic_getc(); if ( ! isdigit(c) ) return 1; n = c - '0';
  c = sonic_getc(); if ( ! isdigit(c) ) return 1; n = (n*10) + c - '0';
  if ( sonic_not_c( '.' ) ) return 1;
  c = sonic_getc(); if ( ! isdigit(c) ) return 1; n = (n*10) + c - '0';
  c = sonic_getc(); if ( ! isdigit(c) ) return 1; n = (n*10) + c - '0';
  if ( sign == '-' ) n = -n;
  *num = n;
  return 0;
}

void sonic_operate( void ) {
  for (;;) {
	do { chars_accepted = 0; } while ( sonic_not_c( '\n' ) );
	resynchs++;
	for (;;) {
	  short U, V, W, T;

	  chars_accepted = 0;
	  if ( sonic_not_c( 'U' ) ) break;
	  if ( sonic_not_num( &U ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( 'V' ) ) break;
	  if ( sonic_not_num( &V ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( 'W' ) ) break;
	  if ( sonic_not_num( &W ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( ' ' ) ) break;
	  if ( sonic_not_c( 'T' ) ) break;
	  if ( sonic_not_num( &T ) ) break;
	  if ( sonic_not_c( '\r' ) ) break;
	  if ( sonic_not_c( '\n' ) ) break;
	  sonic_record( U, V, W, T );
	}
  }
}

void main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  BEGIN_MSG;

  if ( optind >= argc )
	msg( 3, "Must specify a serial device: optind = %d", optind );
  sonic_fd = open( argv[optind], O_RDONLY );
  if ( sonic_fd == -1 )
	msg( 3, "Unable to open serial device \"%s\"", argv[optind] );

  collect_proxy = Col_set_proxy( SONIC_PROXY, 0 );
  quit_proxy    = cc_quit_request( 0 );
  serdev_proxy  = qnx_proxy_attach( 0, NULL, 0, -1 );

  if ( serdev_proxy == -1 )	msg( 3, "Unable to attach proxy" );
  col_id = Col_send_init( "SonicData", &collect_buf, sizeof(collect_buf) );

  sonic_operate();
}
