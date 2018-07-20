/* extmain.skel include file for extraction
 * $Log: extmain.skel,v $
 * Revision 1.11  2011/04/10 19:51:47  ntallen
 * Remove redundant Shutdown message
 *
 * Revision 1.10  2011/01/05 21:06:21  ntallen
 * Support for nctable in addition to photon
 *
 * Revision 1.9  2009/05/04 15:52:04  ntallen
 * debugged
 *
 * Revision 1.8  2008/08/25 15:37:55  ntallen
 * Use atexit() for shutdown message
 *
 * Revision 1.7  2008/08/25 14:37:25  ntallen
 * Need nortlib.h
 *
 * Revision 1.6  2008/08/25 14:36:06  ntallen
 * Add startup and shutdown messages
 *
 * Revision 1.5  2008/08/20 18:08:50  ntallen
 * enable oui_init_options()
 * refer to ext_data_client instead of data_client
 *
 * Revision 1.4  2008/08/01 15:06:21  ntallen
 * Changes required while moving functionality into libraries
 *
 * Revision 1.3  2008/07/23 17:53:15  ntallen
 * First cut at QNX6 skeleton
 *
 * Revision 1.2  2008/07/03 20:58:07  ntallen
 * In the process of testing.
 *
 * Revision 1.1  2008/07/03 15:11:07  ntallen
 * Copied from QNX4 version V1R9
 */
/* Skeleton headers section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "nortlib.h"
#include "oui.h"
#include "DC.h"

static char emrcsid[] =
      "$Id: extmain.skel,v 1.11 2011/04/10 19:51:47 ntallen Exp $";


  /* types.tmc defines data types for HFEMS	*/



 typedef double VOLTS;
 typedef unsigned char UCHAR;
 typedef   signed char SCHART;
 typedef unsigned char SCHAR;
 typedef unsigned short UINT;
 typedef signed short SINT;
 typedef unsigned long int TMLONG;


 typedef unsigned short AD12;
 typedef short AD12_Biplr;

 typedef short AD12_Biplrx2;

 typedef AD12 AD12_2_5;

 typedef AD12 AD12_2_5x2;

 typedef AD12 AD12_2_5x_25;

 typedef AD12 AD12_2_5_RH;

 typedef UINT Ct16;
 typedef UINT DASPt;

 typedef unsigned char DStat;

 typedef SINT Anemo;
 typedef unsigned char UBYTE;

 typedef float Drift_t;
 typedef unsigned short CPU_PCT_text;
 typedef unsigned char CPU_Pct_t;
 typedef double PERCENT;
 typedef unsigned short TMDF_Rpt;
  #include "tmctime.h"


 typedef long int flttime_t;
flttime_t flttime;
  #include <stdlib.h>

  int initial_day = 0;

  #include "nortlib.h"
  #include "tma.h"
  char ci_version[] = "$CGID: HFEMScmd.cc: Wed Mar  7 18:26:56 2018 $";

  tma_state Initialize_cmds_[] = {
    {       0, ">telemetry start\n" },
    {       0, ">Soldrv select Mode 0\n" },
    {       1, ">Set Pman setpoint 5.5\n" },
    {       1, ">Set PrCO2p setpoint 4.5\n" },
    {       1, ">Set FlCO2p setpoint 2.0\n" },
    {       1, ">Set FlCO setpoint 2.25\n" },
    {       1, ">Set PrCO setpoint 5.75\n" },
    {       3, ">Set fcNO_NOx setpoint 0\n" },
    {       3, ">Set fcNO2_NOx setpoint 0\n" },
    {       3, ">Set fc_CO2e setpoint 0\n" },
    {       3, ">Set fcNO_NOy setpoint 0 \n" },
    {       3, ">Set fcEff_NOy setpoint 0\n" },
    {       3, ">Set fcZer_NOy setpoint 0\n" },
    {       3, ">Set FlNOx setpoint 0\n" },
    {       3, ">Set FlNOy setpoint 0\n" },
    {       3, ">Set FlCO2e3 setpoint 2.9\n" },
    {       3, ">Set PrCO2e1 setpoint 0.0\n" },
    {       3, ">Set PrCO2e2 setpoint 0\n" },
    {       3, ">Soldrv select Mode 0\n" },
    {       3, "#2" }, /* RunMode */
    {      -1, NULL }
  };

  tma_state RunMode_cmds_[] = {
    {       2, ">Set PrCO2p setpoint 4.5\n" },
    {       2, ">Set PrCO2p setpoint 4.5\n" },
    {       2, ">Set PrCO2p setpoint 4.5\n" },
    {       5, ">Set Pman setpoint 5.5\n" },
    {       5, ">Set Pman setpoint 5.5\n" },
    {       5, ">Set Pman setpoint 5.5\n" },
    {       9, ">Set FlCO2p setpoint 2.0\n" },
    {       9, ">Set FlCO2p setpoint 2.0\n" },
    {       9, ">Set FlCO2p setpoint 2.0\n" },
    {       9, ">Set FlCO2e3 setpoint 2.9\n" },
    {       9, ">Set FlCO2e3 setpoint 2.9\n" },
    {      14, ">Set FlCO setpoint 2.25\n" },
    {      14, ">Set FlCO setpoint 2.25\n" },
    {      14, ">Set FlCO setpoint 2.25\n" },
    {      20, ">Set PrCO setpoint 5.75\n" },
    {      20, ">Set PrCO setpoint 5.75\n" },
    {      20, ">Set PrCO setpoint 5.75\n" },
    {     320, ">Soldrv Select Mode 3\n" },
    {     320, "#6" }, /* RunMode_end_ */
    {      -1, NULL }
  };

  tma_state Shutdown_cmds_[] = {
    {       0, ">Soldrv Select Mode 7\n" },
    {       0, "?2,2700,7,3" }, /* Shutdown_1_ */
    {       0, ">Soldrv Select Mode 0\n" },
    {       0, "#5" }, /* part_0_idle_ */
    {       0, ">Savelog Automatic Restart\n" },
    {       0, ">Quit\n" },
    {      -1, NULL }
  };

  tma_state Shutdown_Cal_cmds_[] = {
    {       0, ">Soldrv Select Mode 8\n" },
    {       0, "?2,3300,8,4" }, /* Shutdown_Cal_1_ */
    {       0, ">Soldrv Select Mode 0\n" },
    {       0, "#5" }, /* part_0_idle_ */
    {       0, ">Savelog Restart with Archive Cal;\n" },
    {       0, ">Quit\n" },
    {      -1, NULL }
  };

  const int tma_n_partitions = 1;

/* Skeleton console_functions section */
#ifdef TABLELIB_H
  #define phdisplay(x,y) tbl_dispfield(x,y)
#endif

unsigned char V0 = 0x1;
unsigned char V1 = 0x1;
unsigned char V2 = 0x1;
UINT  MFCtr;
UINT  Synch;
union home_row {
  struct __attribute__((__packed__)) {
    Anemo      teddy1;
    Anemo      weddy1;
    Anemo      veddy1;
    Anemo      ueddy1;
    Anemo      teddy2;
    Anemo      weddy2;
    Anemo      veddy2;
    Anemo      ueddy2;
    Ct16 NOy;
    Ct16 NOx;
    Ct16 CtStat;
    SCHAR      sdev_stale1;
    SCHAR      sdev_stale2;
    UCHAR      sdrv_stale1;
    UCHAR      sdrv_stale2;
    AD12_Biplrx2 vCO2e1;
    AD12_Biplrx2 vCO2e2;
    AD12_Biplrx2 vH2Oe1;
    AD12_Biplrx2 vH2Oe2;
    AD12_2_5 vO3ed;
    AD12_2_5 Ta7;
    AD12_2_5 Ta8;
    UBYTE      SolSt;
    char U1[1];
    AD12_2_5 Ta10;
    UINT  Synch;
  } U0;
  struct __attribute__((__packed__)) {
    char U3[26];
    AD12_2_5 Ta2;
    AD12_Biplr vCO;
    AD12_Biplr vCO2prf;
    AD12_Biplr vO3prf;
    AD12_2_5 Ta6;
    AD12_2_5 Ts2;
    AD12_2_5 TS3;
    AD12_2_5 Ta1;
    AD12_2_5 Tcal;
  } U2;
  struct __attribute__((__packed__)) {
    char U5[26];
    AD12_2_5 Tr2;
    AD12_2_5 Ta3;
    AD12_2_5 Ta4;
    AD12_2_5 Ta5;
    AD12_2_5 TS11;
    AD12_2_5 Ts6;
    AD12_2_5 Ts7;
    AD12_2_5 Ta9;
    AD12_2_5 Tr1;
  } U4;
  struct __attribute__((__packed__)) {
    char U7[26];
    AD12_2_5_RH RH10;
    AD12_2_5 Tr3;
    AD12_2_5 Ts1;
    AD12_2_5 Ts10;
    AD12_2_5_RH RH5;
    AD12_2_5_RH RH6;
    AD12_2_5_RH RH7;
    AD12_2_5 Ts4;
    AD12_2_5 Ts5;
  } U6;
  struct __attribute__((__packed__)) {
    char U9[26];
    AD12_Biplrx2 FlowT;
    AD12_2_5_RH RH2;
    AD12_2_5_RH RH3;
    AD12_2_5_RH RH4;
    AD12_2_5 PPFD_cal;
    AD12_Biplr Rnet;
    AD12_Biplr Rnet_cal;
    AD12_2_5 TS8;
    AD12_2_5 TS9;
  } U8;
  struct __attribute__((__packed__)) {
    char U11[26];
    AD12_Biplrx2 fcEff_NOy;
    AD12_2_5x_25 Pamb;
    AD12_2_5x_25 Pman;
    AD12_2_5x_25 PrCO2p;
    AD12_Biplrx2 FlCO2p;
    AD12_Biplrx2 FlNOy;
    AD12_2_5 PPFD_top;
    AD12_2_5_RH RH8;
    AD12_2_5_RH RH1;
  } U10;
  struct __attribute__((__packed__)) {
    char U13[26];
    AD12_2_5 T_MB;
    AD12_Biplrx2 FlCO2e2;
    AD12_Biplrx2 fcNO2_NOx;
    DASPt Pman_SP;
    AD12_Biplrx2 fcNO_NOx;
    AD12_2_5x2 TCO2e1;
    AD12_2_5 PPFD_gnd;
    AD12_2_5 PPFD_mid;
    AD12_2_5_RH RH9;
  } U12;
  struct __attribute__((__packed__)) {
    char U15[26];
    AD12_Biplrx2 FlCO2e1;
    AD12_2_5x_25 PrCO2e2;
    AD12_2_5x_25 FlCO2e3;
    DASPt fcNO2_NOx_SP;
    DStat      DSt2;
    DStat      DSt3;
    AD12_2_5 PPFD_t;
    AD12_2_5x_25 PrNOx;
    AD12_Biplrx2 FlNOx;
    AD12_2_5 PPFD_ref;
  } U14;
  struct __attribute__((__packed__)) {
    char U17[26];
    DASPt PrCO2e1_SP;
    DASPt fcEff_NOy_SP;
    DASPt PrCO2e2_SP;
    DASPt FlCO2e3_SP;
    DASPt PrCO2p_SP;
    AD12_2_5 PPFD_d;
    AD12_Biplrx2 fcNO_NOy;
    AD12_Biplrx2 FlO3_NOx;
    AD12_Biplrx2 fcZer_NOy;
  } U16;
  struct __attribute__((__packed__)) {
    char U19[36];
    DStat      DSt4;
    DStat      DSt5;
    AD12_Biplrx2 fc_CO2e;
    AD12_2_5x_25 PrNOy;
    AD12_Biplrx2 FlO3_NOy;
  } U18;
  struct __attribute__((__packed__)) {
    char U21[36];
    DASPt FlCO2p_SP;
    AD12_2_5x2 TCO2e2;
    AD12_2_5x_25 PrCO;
    AD12_2_5x_25 PrCO2e1;
  } U20;
  struct __attribute__((__packed__)) {
    char U23[36];
    DASPt PrCO_SP;
    DStat      DSt6;
    DStat      DSt7;
    AD12_2_5x2 TCO2p;
    AD12_Biplrx2 FlCO;
  } U22;
  struct __attribute__((__packed__)) {
    char U25[36];
    DASPt fcNO_NOx_SP;
    DASPt FlNOy_SP;
    DASPt fc_CO2e_SP;
    DASPt FlNOx_SP;
  } U24;
  struct __attribute__((__packed__)) {
    char U27[36];
    DASPt fcZer_NOy_SP;
    DASPt FlCO_SP;
    DASPt fcNO_NOy_SP;
    CPU_Pct_t CPU_Pct;
    DStat      DSt0;
  } U26;
  struct __attribute__((__packed__)) {
    char U29[36];
    Drift_t TDrift;
    TMDF_Rpt Disk;
    char U30[1];
    DStat      DSt1;
  } U28;
} *home;

static void VSET_1_(unsigned short newstate);
static void VSET_0_(unsigned short newstate);

static void VSET_1_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
    case 4: /* Shutdown_Cal_1_ */
      V2 |= 0x1;
      break;
    case 3: /* Shutdown_1_ */
      V1 |= 0x1;
      break;
    case 2: /* RunMode_end_ */
      V0 |= 0x1;
      break;
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* Shutdown_Cal_1_ */
      V2 &= ~0x1;
      break;
    case 3: /* Shutdown_1_ */
      V1 &= ~0x1;
      break;
    case 2: /* RunMode_end_ */
      V0 &= ~0x1;
      break;
  }
}
static void VSET_0_(unsigned short newstate) {
  static unsigned short oldstate;
  
  switch (oldstate) {
  }
  oldstate = newstate;
  switch (newstate) {
    case 4: /* Shutdown_Cal */ {
        {
          tma_init_state( 0, Shutdown_Cal_cmds_, "Shutdown_Cal" ); VSET_1_(1);
        }
      }
      break;
    case 3: /* Shutdown */ {
        {
          tma_init_state( 0, Shutdown_cmds_, "Shutdown" ); VSET_1_(1);
        }
      }
      break;
    case 2: /* RunMode */ {
        {
          tma_init_state( 0, RunMode_cmds_, "RunMode" ); VSET_1_(1);
        }
      }
      break;
    case 1: /* Initialize */ {
        {
          tma_init_state( 0, Initialize_cmds_, "Initialize" ); VSET_1_(1);
        }
      }
      break;
  }
}
void tminitfunc(void) {VSET_0_(1);VSET_1_(1);
}

static void nullfunc(void);
static void BF1_0(void) {
}

static void BF8_0(void) {
  BF1_0();
  {
    flttime = itime();
  }
  if (!(V0)) {
    {
              int cur_day;
              cur_day = (itime()-(5*3600))/86400L;
    
              if (initial_day == 0) {
                initial_day = cur_day;
              } else if (initial_day != cur_day) {
                if ((cur_day % 8) == 0) { VSET_0_(4);
                } else { VSET_0_(3);
                }
              }
            }
  }
  {
    long int it;
    int subcase;
  
    it = itime();
    ci_settime( it );
    while ( (subcase = tma_process( it )) ) {
  	switch (subcase) {
  	  case -1:
  	  case 0: break;
  	  case 1: VSET_0_(1); break;
  	  case 2: VSET_0_(2); break;
  	  case 3: VSET_0_(3); break;
  	  case 4: VSET_0_(4); break;
  	  case 5: VSET_1_(1); break;
  	  case 6: VSET_1_(2); break;
  	  case 7: VSET_1_(3); break;
  	  case 8: VSET_1_(4); break;
  	  default:
  		nl_error( 1, "Unexpected return value from tma_process" );
  		break;
  	}
    }
  }
}

static void BF16_15(void) {
  BF1_0();
  if (!(V1)) {
    {
      if (home->U0.SolSt == 1) {
        tma_succeed( 0, 7 ); VSET_1_(1);
      }
    }
  }
  if (!(V2)) {
    {
      if (home->U0.SolSt == 1) {
        tma_succeed( 0, 8 ); VSET_1_(1);
      }
    }
  }
}

static void (*efuncs[16])() = {
  BF8_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF8_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF1_0,
  BF16_15
};

#define TRN 80
#define TRD 1
#define LOWLIM (-720)
#define HIGHLIM (720)
#define NBROW 48
#define NROWMINF 1
#define NSECSPER 1
#define NROWSPER 8
#define LCMMN 16
#define ROLLOVER_MFC 0
#define SYNCHVAL 0xABB4
#define INVSYNCH 0
#define NROWMAJF 16
#define MFSECNUM 8
#define MFSECDEN 1
#define SECDRIFT 90
#define TM_DATA_TYPE TMTYPE_DATA_T3

/* Skeleton data_defs section */
#ifndef EXTRACTION_INIT
  #define EXTRACTION_INIT
#endif
#ifndef EXTRACTION_TERM
  #define EXTRACTION_TERM
#endif

/* Skeleton main_program section */
#ifdef TABLELIB_H
  #include "DCph.h"
  typedef ph_data_client DATA_CLIENT;
#else
  #ifdef NCTABLE_H_INCLUDED
    #include "DCnc.h"
    typedef nc_data_client DATA_CLIENT;
  #else
    typedef ext_data_client DATA_CLIENT;
  #endif
#endif

int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Startup" );
  DATA_CLIENT DC(4096, 1, 0);
  EXTRACTION_INIT;
  DC.operate();
  EXTRACTION_TERM;
  nl_error( 0, "Shutdown" );
  return 0;
}


/* Skeleton rest of the file */

#define incmod(x,y) if (x==((y)-1)) x = 0; else x++

#if (NROWMINF == 1)
  #define MINF_ROW 0
  #define MINF_ROW_ZERO
  #define MINF_ROW_INC
#else
  #define MINF_ROW data_client::minf_row
  #define MINF_ROW_ZERO data_client::minf_row = 0
  #define MINF_ROW_INC ++data_client::minf_row
#endif

#define incmod(x,y) if (x==((y)-1)) x = 0; else x++

#if TM_DATA_TYPE == TMTYPE_DATA_T3
void DATA_CLIENT::process_data() {
  tm_data_t3_t *data = &msg->body.data3;
  unsigned char *raw;
  int n_rows = data->n_rows;
  MFCtr = data->mfctr;
  #ifdef IVFUNCS
    unsigned short delta = MFCtr - next_minor_frame;
    if (delta != 0) {
        // Because we are TMTYPE_DATA_T3, we know NROWMINF == 1
        if (delta > NROWMAJF) delta = NROWMAJF;
        while (delta-- > 0) {
          ivfuncs[majf_row]();
          incmod(majf_row, NROWMAJF);
        }
    }
  #endif
  majf_row = (((unsigned short)MFCtr) % NROWMAJF);

  for ( raw = &data->data[0]; n_rows > 0; --n_rows, raw += nbQrow ) {
    home = (union home_row *) raw;
    efuncs[majf_row]();
    incmod(majf_row, NROWMAJF);
    ++MFCtr;
  }
  next_minor_frame = MFCtr;
}
#else
  #error Data types TMTYPE_DATA_T1 and TMTYPE_DATA_T2 not implemented in extmain.skel
#endif

#ifdef NEED_TIME_FUNCS
  #define ROWS(x) (((unsigned long)(x))*NROWMINF+MINF_ROW)
  #define FRACSECS(x) (((unsigned long)ROWS(x))*NSECSPER)

  long itime(void) {
      return(tm_info.t_stmp.secs +
        FRACSECS(MFCtr-tm_info.t_stmp.mfc_num) / NROWSPER );
  }
  double dtime(void) {
      return(tm_info.t_stmp.secs +
        (double) FRACSECS(MFCtr-tm_info.t_stmp.mfc_num) / NROWSPER );
  }
  double etime(void) {
    double t;
    static double t0 = -1e9;
    
    t = dtime();
    if (t0 == -1e9) t0 = t;
    return(t - t0);
  }
#endif

/* Skeleton End of File */

tm_info_t tm_info = {
  {   /* tm_dac_t tm; */
    { /* tmid_t tmid; */
      /* version: '1.3' */
      {  49,  46,  51,   0,   0,   0,   0,   0,
          0,   0,   0,   0,   0,   0,   0,   0 },
      /* md5: */
      { 0x4C, 0x67, 0x09, 0xDE, 0x4F, 0x71, 0x9A, 0x51,
        0x95, 0xE9, 0xE4, 0x5F, 0x5B, 0xFF, 0xE7, 0x3C }
    },
    48, /* nbminf */
    48, /* nbrow */
    16, /* nrowsmajf */
    1, /* nsecsper */
    8, /* nrowsper */
    0, 1, /* mfc_lsb, mfc_msb */
    0xABB4, /* synch */
    0 /* flags: not inverted */
  }
};
