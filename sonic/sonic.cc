#include <errno.h>
#include "sonic_int.h"
#include "nortlib.h"
#include "oui.h"

const char *sonic_path = "/dev/ser1";

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    Sonic_t SCdata;
    Sonic SC( sonic_path, &SCdata );
    SC.setup(9600, 7, 'e', 1, 35, 0 );
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
  TMdata = data;
  TMdata->U = 0;
  TMdata->V = 0;
  TMdata->W = 0;
  TMdata->T = 0;
  TMdata->SC_stale = 0;
  flags |= Selector::gflag(0);
  nl_error( 0, "Sonic fd = %d, flags = %d", fd, flags );
}

int Sonic::ProcessData(int flag) {
  if ( flag & Selector::gflag(0) ) {
	++TMdata->SC_stale;
  }else {
    //int addr1, addr2;
    int U, V, W, T;
    if ( flag & Selector::Sel_Read ) {
      // Read and parse data
	  // U 32767  V-32767  W 32767  T-32767\r\n
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
	      TMdata->SC_stale = 0;
	    }
	    consume(cp);
	  }
    }
  }
  return 0;
}
int Sonic::not_signed_int( int &val ){
  int sign;
  sign = sign_val();
  if ( not_int( val ) ) return 1;
  val *= sign;
  return 0;
}

int Sonic::sign_val(){
   switch (buf[cp]){
	case '+': 
      cp++;
      return 1;
	case ' ':
	  cp++;
	  return 1;
	case '-':
      cp++;
      return -1;
    default:  
      report_err( "Expected '+',' ', or '-' at column %d", cp );
	  return 1; //assuming number and not signed.
  }
}
