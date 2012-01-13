/* Sonic anemometer serial interface
   Written by NTA 5/9/97
*/
#include <termios.h>
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
#include "Selector.h"
#include "Timeout.h"
#define SONIC_REC_SIZE 35


/** Establish connection to Quit stream */
Quitter::Quitter() : Selectee() {
  int resp = set_response(1);
  fd = tm_open_name(tm_dev_name("cmd/Quit"),NULL,O_RDONLY);
  flags = Selector::Sel_Read;
  set_response(resp);
}

/** If Quitter is ready for read, it's time to quit */
int Quitter::ProcessData(int flag) {
  msg( 0, "Resynchronized %ld times", resynchs );
  msg( 0, "Untransferred records: %ld", untransferred );
  msg( 0, "Retransferred records: %ld", retransferred );
  DONE_MSG;
  return 1;
}

/*
void got_quit_proxy( void ) {
  msg( 0, "Resynchronized %ld times", resynchs );
  msg( 0, "Untransferred records: %ld", untransferred );
  msg( 0, "Retransferred records: %ld", retransferred );
  DONE_MSG;
  exit(0);
}
*/

/** Constructor, sets to NULL so that easier to detect if no connection */
TMcollect::TMcollect() : Selectee() {
  par = NULL;
  TMid = NULL;
}

int TMcollect::ProcessData( int flag ){
  flags = 0;
  par->Request();
  return 0;
}

/** Initialize Col_send */
int TMcollect::init(sonic_ctrl *par_in, const char *name,
	    void *data, int data_size){
  par = par_in;
  TMid = Col_send_init(name, data, data_size, 0);
  fd = TMid->fd;
  flags = Selector::Sel_Write;
  nl_error( -2, "TM initialized: fd = %d", fd );
  return 0;
}
/** Set collection flag to write */
int TMcollect::send(){
  Col_send(TMid);
  flags = Selector::Sel_Write;
  return 0;
}

sonic_ctrl::sonic_ctrl() : Selectee() {
  
  buf = new char[SONIC_REC_SIZE+1];
  TM.init( this, "Sonic", &TMdata, sizeof(TMdata) );
  chars_accepted = 0;
  resynchs = 0;
  untransferred = 0;
  retransferred = 0;
  sonic_fd = open( argv[optind], O_RDONLY );
  if ( sonic_fd == -1 )
	msg( 3, "Unable to open serial device \"%s\"", argv[optind] );  
  collect_proxy = Col_set_proxy( SONIC_PROXY, 0 );
  quit_proxy    = cc_quit_request( 0 );
  serdev_proxy  = qnx_proxy_attach( 0, NULL, 0, -1 );
  if ( serdev_proxy == -1 )	msg( 3, "Unable to attach proxy" );
  if( tcgetattr( fd, &termios_p ) )
    nl_error( 3, "Invalid fildes" );
  // following are just place holder values until I figure out what
  // they should actually be.
  termios_p.c_cc[VMIN]  =  1; // minimum number of bytes to be read in before a return/ amount of data you'll settle for
							  // if VMIN set to zero it is PURE timed read. (VMIN = VTIME = 0 non-blocking read)
  termios_p.c_cc[VTIME] =  0; // measured in 1/10 of a second resets after each char, find out how long typcial delay is.
  termios_p.c_lflag &= ~( ECHO|ICANON|ISIG|ECHOE|ECHOK|ECHONL );
  termios_p.c_oflag &= ~( OPOST );
  if( tcsetattr( fd, TCSADRAIN, &termios_p ) )
    nl_error( 3, "Argument action is invalid for member of termios_p" );
}

void sonic_ctrl::sonic_record( short U, short V, short W, short T ) {
  collect_buf.U = U;
  collect_buf.V = V;
  collect_buf.W = W;
  collect_buf.T = T;
  if ( collect_buf.transferred )
	untransferred++;
  collect_buf.transferred++;
}

void got_collect_proxy( void ) {
  if ( collect_buf.transferred ) {
	Col_send(col_id);
	collect_buf.transferred = 0;
  } else retransferred++;
}

void sonic_ctrl::sonic_fillbuf( void ) {
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

/** sonic_getc() get a character */
int sonic_ctrl::sonic_getc( void ) {
  while ( buf_low >= buf_high ) sonic_fillbuf();
  chars_accepted++;
  return buf[buf_low++];
}

/** returns non-zero if the next character from sonic is not c */
int sonic_ctrl::sonic_not_c( int c ) {
  return ( sonic_getc() != c );
}

/** returns non-zero if input isn't of the form:
		[ -][0-9][0-9].[0-9][0-9]
   Assigns the result to *num
*/
int sonic_ctrl::sonic_not_num( signed short *num ) {
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

//void sonic_operate( void ) {
int sonic_ctrl::ProcessData( int flag ){
//  for (;;) {
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

void main( int argc, char **argv ) {
  oui_init_options(argc, argv);
  BEGIN_MSG;
  Selector.Sr;
  if ( optind >= argc )
	msg( 3, "Must specify a serial device: optind = %d", optind );
  Quitter Q;
  sonic_ctrl SC( optind );
  if ( Q.fd >= 0)
    Sr.add_child(&Q);
  Sr.add_child(&SC);
  Sr.add_child(&SC.TM);
  if ( serdev_proxy == -1 )	msg( 3, "Unable to attach proxy" );
  Sr.event_loop();
}
