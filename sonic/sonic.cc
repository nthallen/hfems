#include <errno.h>
#include "sonic_int.h"
#include "nortlib.h"
#include "oui.h"
#define SONIC_REC_SIZE 36
const char *sonic_path = "/dev/ser1";
const char *sonic_name = "Sonic";

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  { Selector S;
    Sonic_t SCdata;
    Sonic SC( sonic_path, &SCdata );
    SC.setup(9600, 7, 'e', 1, SONIC_REC_SIZE, 0 );
    Cmd_Selectee QC;
    TM_Selectee TM( sonic_name, &SCdata, sizeof(SCdata) );
    S.add_child(&SC);
    S.add_child(&QC);
    S.add_child(&TM);
    S.event_loop();
  }
  nl_error( 0, "Terminating" );
}

Sonic::Sonic( const char *path, Sonic_t *data ) :
    Ser_Sel( path, O_RDONLY | O_NONBLOCK, SONIC_REC_SIZE*3 ) {
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
  } else {
    //int addr1, addr2;
    int U, V, W, T;
    if ( flag & Selector::Sel_Read ) {
      // Read and parse data
      // U 32.00  V-32.99  W 32.11  T-32.22\r\n
      if ( fillbuf() ) return 1;
      cp = 0;

      // Do check for a complete record
      if( not_found( 'U' )) return 0;
      if( cp > 1 ) consume(cp-1);
      cp = 0;
      if( nc < SONIC_REC_SIZE )
        return 0;

      while ( cp < nc ) {
        if( not_str( "U" ) ||
            not_signed_ffloat( U ) ||
            not_str( "  V" ) ||
            not_signed_ffloat( V ) ||
            not_str( "  W" ) ||
            not_signed_ffloat( W ) ||
            not_str( "  T" ) ||
            not_signed_ffloat( T ) ||
            not_str( "\r\n" )) {
          if ( cp < nc ) {
            consume(cp > 0 ? cp : 1);
          }
        } else {
          TMdata->U = U;
          TMdata->V = V;
          TMdata->W = W;
          TMdata->T = T;
          --TMdata->SC_stale;
          consume(cp);
          report_ok();
        }
      }
    }
  }
  return 0;
}

// Looking for "sign" int "." int and converting to a fixed float stored as 1 int
int Sonic::not_signed_ffloat( int &val ){
  int sign, temp;
  if (not_sign( sign) ||
      not_int(temp))
    return 1;
  val = temp * 100;
  if (not_str( "." ) ||
      not_int( temp ))
    return 1;
  val = (val + temp) * sign;
  return 0;
}

int Sonic::not_sign(int &val) {
  if (cp >= nc) return 0;
  switch (buf[cp]) {
    case '+': 
    case ' ':
      val = 1;
      break;
    case '-':
      val = -1;
      break;
    default:  
      report_err( "Expected '+',' ', or '-' at column %d", cp );
      return 1;
  }
  cp++;
  return 0;
}
