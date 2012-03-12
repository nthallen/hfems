#include <errno.h>
#include "sonic_int.h"
#include "nortlib.h"
#include "oui.h"

#define SONIC_REC_SIZE 35
const char *sonic_path = "/net/path/to/device";

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    Sonic_t SCdata;
    Sonic SC( sonic_path, &SCdata );
    SC.setup(38400, 8, 'n', 1, 28, 1 ); //need parameters for Sonic setup
    Cmd_Selectee QC;
    TM_Selectee TM( "Sonic", &SCdata, sizeof(SCdata) );
    S.add_child(&SC);
    S.add_child(&QC);
    S.add_child(&TM);
    S.event_loop();
  }
  nl_error( 0, "Terminating" );
}

Sonic::Sonic( const char *path, Sonic_t *data ) :
    Ser_Sel( path, O_RDWR | O_NONBLOCK, 40 ) {
  state = Q1;
  query_pending = 0;
  TMdata = data;
  flags |= Selector::gflag(0);
  //initialize TMdata if necessary
  TMdata->SC_stat = SC_PRESENT;
  nl_error( 0, "Sonic fd = %d, flags = %d", fd, flags );
}

int Sonic::ProcessData(int flag) {
  int sign;
  if ( flag & Selector::gflag(0) ) {
    IssueQuery(1);
  }else {
    //int addr1, addr2;
    int U, V, W, T;
    if ( flag & Selector::Sel_Read ) {
      // Read and parse data
	  // U32767  V32767  W32767  T32767\r\n
      if ( fillbuf() ) return 1;
      cp = 0;
	  // Do check for a complete record
	  if( not_found( '\n' )) return 0;
	  cp = 0;
      while ( cp < nc ) {
		if( not_str( "U" ) ||
		not_signed_int( U ) ||
		not_str( "  V" ) ||
		not_signed_int( V ) ||
		not_str( "  W" ) ||
		not_signed_int( W ) ||
		not_str( "  T" ) ||
		not_signed_int( T ) ||
		not_str( "\r\n" )){
    	  if ( cp < nc ) {
	        consume(cp);
	      }
	    } else {
	      TMdata->U = U;
		  TMdata->V = V;
		  TMdata->W = W;
		  TMdata->T = T;
	      TMdata->SC_stat |= SC_FRESH;
	      state = Q1;
	    }
	    consume(cp);
	    if (query_pending )
	      IssueQuery(0);
	  }
    }
  }
  return 0;
}
int not_signed_int( int &val ){
  int sign;
  sign = sign_val();
  if ( not_int( val ) ) return 1;
  val *= sign;
  return 0;
}

int sign_val(){
  if ( '+' == buf[cp] ){
    cp++;
    return 1;
  }
  else if ( '-' == buf[cp] ){
    cp++;
    return -1;
  }
  else{
    report_err( "Expected +/- at column %d", cp );
	return 1; //returning 1 so it doesn't break
  }
}

void Sonic::IssueQuery(bool synch) {
  const char *query;
  query_pending = synch;
  int rv;

  if ( synch ) {
    TMdata->SC_stat &= ~(SC_FRESH);
  }
  switch (state) {
    case R1:
      report_err("Timeout reading from device");
      // fall through
    case Q1:
      query = "replace with what a query looks like?";
      state = R1;
      break;
  }
  rv = write( fd, query, 11 );
  if ( rv < 0 ) {
    report_err( "Error %d writing to Sonic", errno );
  } else if ( rv < 11 ) {
    report_err( "Wrote only %d bytes", rv );
  }
}