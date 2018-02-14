/* Skeleton headers section */
/* colmain.skel Skeleton for collection main program
 * $Log: colmain.skel,v $
 * Revision 1.12  2012/03/13 17:43:16  ntallen
 * Eliminate obsolete comment
 *
 * Revision 1.11  2011/03/08 14:05:30  ntallen
 * Check for dg_event_quit in addition to dg_event_stop
 *
 * Revision 1.10  2008/09/07 16:11:19  ntallen
 * Pre-declare VSET functions
 *
 * Revision 1.9  2008/08/25 14:36:06  ntallen
 * Add startup and shutdown messages
 *
 * Revision 1.8  2008/08/20 18:39:21  ntallen
 * Enable oui_init_options()
 *
 * Revision 1.7  2008/08/01 15:06:21  ntallen
 * Changes required while moving functionality into libraries
 *
 * Revision 1.6  2008/07/29 20:11:22  ntallen
 * Changes for Col_send
 *
 * Revision 1.5  2008/07/29 18:57:10  ntallen
 * Fixed handling of MFCtr, minf_row and majf_row
 *
 * Revision 1.4  2008/07/23 17:41:07  ntallen
 * Compilation tweaks
 *
 * Revision 1.3  2008/07/23 17:08:00  ntallen
 * First cut at QNX6 collection skeleton
 *
 * Revision 1.2  2008/07/03 20:58:07  ntallen
 * In the process of testing.
 *
 * Revision 1.1  2008/07/03 15:11:07  ntallen
 * Copied from QNX4 version V1R9
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include "nortlib.h"
#include "oui.h"
#include "tm.h"
#include "DGcol.h"

static char cmrcsid[] =
      "$Id: colmain.skel,v 1.12 2012/03/13 17:43:16 ntallen Exp $";


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
  #include "subbus.h"
  unsigned int SolStatA;

  #include "sonic.h"
  Sonic_t SonicData1;
  Sonic_t SonicData2;
  static void Ct64_init( void ) {
   sbwr( 0x600, 0x0100 ); /* 8 Hz */
  }

  #include <time.h>

  float get_drift() {
    struct timespec ts;
    double tmtime, systime;
    tmtime = dtime();
    clock_gettime(CLOCK_REALTIME, &ts);
    systime = ts.tv_sec + ts.tv_nsec*1e-9;
    return((float)(tmtime - systime));
  }

  #include "cpu_usage.h"
  cpu_usage CPU;

  #include "tmdf.h"
  TMDF_t TMDF;


 /* receive objects */
 DG_data *TMDF_obj;
 DG_data *SonicData2_obj;
 DG_data *SonicData1_obj;
 DG_data *SolStatA_obj;

/* Skeleton console_functions section */
/* Photon and resource manager probably don't mix */

UINT  MFCtr;
UINT  Synch;
Ct16 NOx;
Ct16 NOy;
Ct16 CtStat;
Anemo      ueddy1;
Anemo      veddy1;
Anemo      weddy1;
Anemo      teddy1;
SCHAR      sdev_stale1;
UCHAR      sdrv_stale1;
Anemo      ueddy2;
Anemo      veddy2;
Anemo      weddy2;
Anemo      teddy2;
SCHAR      sdev_stale2;
UCHAR      sdrv_stale2;
UBYTE      SolSt;
AD12_Biplrx2 vCO2e1;
AD12_Biplrx2 vH2Oe1;
AD12_Biplrx2 vCO2e2;
AD12_Biplrx2 vH2Oe2;
AD12_2_5 vO3ed;
AD12_Biplr vCO2prf;
AD12_Biplr vO3prf;
AD12_Biplr vCO;
AD12_2_5 Ta1;
AD12_2_5 Ta2;
AD12_2_5 Ta3;
AD12_2_5 Ta4;
AD12_2_5 Ta5;
AD12_2_5 Ta6;
AD12_2_5 Ta7;
AD12_2_5 Ta8;
AD12_2_5 Ta9;
AD12_2_5 Ta10;
AD12_2_5 Tcal;
AD12_2_5 Tr1;
AD12_2_5 Tr2;
AD12_2_5 Tr3;
AD12_2_5 Ts1;
AD12_2_5 Ts2;
AD12_2_5 TS3;
AD12_2_5 Ts4;
AD12_2_5 Ts5;
AD12_2_5 Ts6;
AD12_2_5 Ts7;
AD12_2_5 TS8;
AD12_2_5 TS9;
AD12_2_5 Ts10;
AD12_2_5 TS11;
AD12_2_5_RH RH1;
AD12_2_5_RH RH2;
AD12_2_5_RH RH3;
AD12_2_5_RH RH4;
AD12_2_5_RH RH5;
AD12_2_5_RH RH6;
AD12_2_5_RH RH7;
AD12_2_5_RH RH8;
AD12_2_5_RH RH9;
AD12_2_5_RH RH10;
AD12_Biplr Rnet;
AD12_Biplr Rnet_cal;
AD12_2_5 PPFD_top;
AD12_2_5 PPFD_mid;
AD12_2_5 PPFD_ref;
AD12_2_5 PPFD_cal;
AD12_2_5 PPFD_gnd;
AD12_2_5x_25 Pamb;
AD12_Biplrx2 FlowT;
AD12_2_5x_25 Pman;
AD12_Biplrx2 FlCO2p;
AD12_2_5x_25 PrCO2p;
AD12_Biplrx2 FlNOx;
AD12_Biplrx2 FlO3_NOx;
AD12_Biplrx2 fcNO_NOx;
AD12_Biplrx2 fcNO2_NOx;
AD12_2_5x_25 PrNOx;
AD12_Biplrx2 FlNOy;
AD12_Biplrx2 fcNO_NOy;
AD12_Biplrx2 fcEff_NOy;
AD12_Biplrx2 fcZer_NOy;
AD12_Biplrx2 FlO3_NOy;
AD12_2_5x_25 PrNOy;
AD12_2_5 T_MB;
AD12_Biplrx2 FlCO2e1;
AD12_Biplrx2 fc_CO2e;
AD12_2_5x_25 PrCO2e1;
AD12_2_5x2 TCO2e1;
AD12_Biplrx2 FlCO2e2;
AD12_2_5x_25 PrCO2e2;
AD12_2_5x2 TCO2e2;
AD12_2_5x_25 FlCO2e3;
AD12_Biplrx2 FlCO;
AD12_2_5x_25 PrCO;
AD12_2_5x2 TCO2p;
AD12_2_5 PPFD_t;
AD12_2_5 PPFD_d;
DStat      DSt0;
DStat      DSt1;
DStat      DSt2;
DStat      DSt3;
DStat      DSt4;
DStat      DSt5;
DStat      DSt6;
DStat      DSt7;
DASPt Pman_SP;
DASPt PrCO2p_SP;
DASPt FlCO2p_SP;
DASPt PrCO2e1_SP;
DASPt PrCO2e2_SP;
DASPt PrCO_SP;
DASPt fc_CO2e_SP;
DASPt fcNO2_NOx_SP;
DASPt fcNO_NOx_SP;
DASPt fcNO_NOy_SP;
DASPt fcEff_NOy_SP;
DASPt fcZer_NOy_SP;
DASPt FlNOx_SP;
DASPt FlNOy_SP;
DASPt FlCO2e3_SP;
DASPt FlCO_SP;
Drift_t TDrift;
CPU_Pct_t CPU_Pct;
TMDF_Rpt Disk;
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


void tminitfunc(void) {
  Ct64_init();
   CPU.init();
  
}

static void nullfunc(void);
static void CF1_0(void) {
  {
    ueddy2 = SonicData2.U;
    veddy2 = SonicData2.V;
    weddy2 = SonicData2.W;
    teddy2 = SonicData2.T;
    sdev_stale2 = SonicData2.SC_stale;
    sdrv_stale2 = SonicData2_obj->stale(255);
    SonicData2_obj->synch();
  }
  {
    ueddy1 = SonicData1.U;
    veddy1 = SonicData1.V;
    weddy1 = SonicData1.W;
    teddy1 = SonicData1.T;
    sdev_stale1 = SonicData1.SC_stale;
    sdrv_stale1 = SonicData1_obj->stale(255);
    SonicData1_obj->synch();
  }
  {
    CtStat = sbrwa( 0x600 );
    NOx = sbrwa( 0x610 );
    NOy = sbrwa( 0x618 );
  }
  home->U0.CtStat = CtStat;
  home->U0.NOx = NOx;
  home->U0.NOy = NOy;
  home->U0.ueddy2 = ueddy2;
  home->U0.veddy2 = veddy2;
  home->U0.weddy2 = weddy2;
  home->U0.teddy2 = teddy2;
  home->U0.ueddy1 = ueddy1;
  home->U0.veddy1 = veddy1;
  home->U0.weddy1 = weddy1;
  home->U0.teddy1 = teddy1;
  home->U0.sdrv_stale2 = sdrv_stale2;
  home->U0.sdrv_stale1 = sdrv_stale1;
  home->U0.sdev_stale2 = sdev_stale2;
  home->U0.sdev_stale1 = sdev_stale1;
}

static void CF2_0(void) {
  CF1_0();
  vO3ed = (sbrwa(0xC40) & 0x0FFF)<<4;
  vH2Oe2 = (sbrwa(0xC16) & 0x0fff) << 4;
  vCO2e2 = (sbrwa(0xC14) & 0x0fff) << 4;
  vH2Oe1 = (sbrwa(0xC12) & 0x0fff) << 4;
  vCO2e1 = (sbrwa(0xC10) & 0x0fff) << 4;
  home->U0.vO3ed = vO3ed;
  home->U0.vH2Oe2 = vH2Oe2;
  home->U0.vH2Oe1 = vH2Oe1;
  home->U0.vCO2e2 = vCO2e2;
  home->U0.vCO2e1 = vCO2e1;
}

static void CF8_0(void) {
  CF2_0();
  {
    Disk = TMDF.usage;
    TMDF_obj->synch();
  }
  CPU_Pct = CPU.report(1);
  TDrift = get_drift();
  home->U26.CPU_Pct = CPU_Pct;
  home->U28.Disk = Disk;
  home->U28.TDrift = TDrift;
}

static void EF8_0(void) {
  {
    flttime = itime();
  }
}

static void BF16_0(void) {
  CF8_0();
  DSt0 = sbrba(0x80A);
  home->U26.DSt0 = DSt0;
  EF8_0();
}

static void BF16_1(void) {
  CF1_0();
  fcEff_NOy_SP = sbrwa(0xCE4) & 0xFFF;
  fcNO_NOy_SP = sbrwa(0xCE2) & 0xFFF;
  fcNO_NOx_SP = sbrwa(0xCE0) & 0xFFF;
  fcNO2_NOx_SP = sbrwa(0xC6E) & 0xFFF;
  fcZer_NOy = (sbrwa(0xC34) & 0x0fff) << 4;
  fcEff_NOy = (sbrwa(0xC32) & 0x0fff) << 4;
  fcNO_NOy = (sbrwa(0xC30) & 0x0fff) << 4;
  fcNO2_NOx = (sbrwa(0xC2C) & 0x0fff) << 4;
  fcNO_NOx = (sbrwa(0xC3A) & 0x0fff) << 4;
  home->U16.fcZer_NOy = fcZer_NOy;
  home->U26.fcNO_NOy_SP = fcNO_NOy_SP;
  home->U16.fcNO_NOy = fcNO_NOy;
  home->U24.fcNO_NOx_SP = fcNO_NOx_SP;
  home->U12.fcNO_NOx = fcNO_NOx;
  home->U14.fcNO2_NOx_SP = fcNO2_NOx_SP;
  home->U12.fcNO2_NOx = fcNO2_NOx;
  home->U16.fcEff_NOy_SP = fcEff_NOy_SP;
  home->U10.fcEff_NOy = fcEff_NOy;
}

static void BF16_2(void) {
  CF2_0();
  fcZer_NOy_SP = sbrwa(0xCE6) & 0xFFF;
  fc_CO2e_SP = sbrwa(0xC6C) & 0xFFF;
  FlCO = (sbrwa(0xC3E) & 0x0fff) << 4;
  fc_CO2e = (sbrwa(0xC2A) & 0x0fff) << 4;
  home->U22.FlCO = FlCO;
  home->U24.fc_CO2e_SP = fc_CO2e_SP;
  home->U18.fc_CO2e = fc_CO2e;
  home->U26.fcZer_NOy_SP = fcZer_NOy_SP;
}

static void BF16_3(void) {
  CF1_0();
  FlCO_SP = sbrwa(0xCEE) & 0xFFF;
  FlCO2e3_SP = sbrwa(0xCEC) & 0xFFF;
  FlNOx_SP = sbrwa(0xCE8) & 0xFFF;
  FlCO2p_SP = sbrwa(0xC64) & 0xFFF;
  FlCO2e3 = (sbrwa(0xC9A) & 0x0FFF)<<4;
  FlCO2e2 = (sbrwa(0xC3C) & 0x0fff) << 4;
  FlCO2e1 = (sbrwa(0xC38) & 0x0fff) << 4;
  FlNOx = (sbrwa(0xC26) & 0x0fff) << 4;
  FlCO2p = (sbrwa(0xC24) & 0x0fff) << 4;
  home->U24.FlNOx_SP = FlNOx_SP;
  home->U14.FlNOx = FlNOx;
  home->U26.FlCO_SP = FlCO_SP;
  home->U20.FlCO2p_SP = FlCO2p_SP;
  home->U10.FlCO2p = FlCO2p;
  home->U16.FlCO2e3_SP = FlCO2e3_SP;
  home->U14.FlCO2e3 = FlCO2e3;
  home->U12.FlCO2e2 = FlCO2e2;
  home->U14.FlCO2e1 = FlCO2e1;
}

static void BF16_4(void) {
  CF2_0();
  FlNOy_SP = sbrwa(0xCEA) & 0xFFF;
  FlO3_NOy = (sbrwa(0xC36) & 0x0fff) << 4;
  FlNOy = (sbrwa(0xC2E) & 0x0fff) << 4;
  FlO3_NOx = (sbrwa(0xC28) & 0x0fff) << 4;
  home->U18.FlO3_NOy = FlO3_NOy;
  home->U16.FlO3_NOx = FlO3_NOx;
  home->U24.FlNOy_SP = FlNOy_SP;
  home->U10.FlNOy = FlNOy;
}

static void BF16_5(void) {
  CF1_0();
  Pman_SP = sbrwa(0xC60) & 0xFFF;
  PPFD_d = (sbrwa(0xCD4) & 0x0FFF)<<4;
  Pman = (sbrwa(0xC58) & 0x0FFF)<<4;
  FlowT = (sbrwa(0xC22) & 0x0fff) << 4;
  Pamb = (sbrwa(0xC56) & 0x0FFF)<<4;
  PPFD_gnd = (sbrwa(0xCDE) & 0x0FFF)<<4;
  PPFD_cal = (sbrwa(0xCDC) & 0x0FFF)<<4;
  PPFD_ref = (sbrwa(0xCDA) & 0x0FFF)<<4;
  PPFD_mid = (sbrwa(0xCD8) & 0x0FFF)<<4;
  home->U14.PPFD_ref = PPFD_ref;
  home->U12.PPFD_mid = PPFD_mid;
  home->U12.PPFD_gnd = PPFD_gnd;
  home->U16.PPFD_d = PPFD_d;
  home->U8.PPFD_cal = PPFD_cal;
  home->U12.Pman_SP = Pman_SP;
  home->U10.Pman = Pman;
  home->U10.Pamb = Pamb;
  home->U8.FlowT = FlowT;
}

static void BF16_6(void) {
  CF2_0();
  PPFD_t = (sbrwa(0xCD2) & 0x0FFF)<<4;
  PrCO = (sbrwa(0xC9C) & 0x0FFF)<<4;
  PrCO2e1 = (sbrwa(0xC92) & 0x0FFF)<<4;
  PPFD_top = (sbrwa(0xCD6) & 0x0FFF)<<4;
  home->U20.PrCO2e1 = PrCO2e1;
  home->U20.PrCO = PrCO;
  home->U10.PPFD_top = PPFD_top;
  home->U14.PPFD_t = PPFD_t;
}

static void BF16_7(void) {
  CF1_0();
  PrCO_SP = sbrwa(0xC6A) & 0xFFF;
  PrCO2e2_SP = sbrwa(0xC68) & 0xFFF;
  PrCO2e1_SP = sbrwa(0xC66) & 0xFFF;
  PrCO2p_SP = sbrwa(0xC62) & 0xFFF;
  PrCO2e2 = (sbrwa(0xC96) & 0x0FFF)<<4;
  PrNOy = (sbrwa(0xC5E) & 0x0FFF)<<4;
  PrNOx = (sbrwa(0xC5C) & 0x0FFF)<<4;
  PrCO2p = (sbrwa(0xC5A) & 0x0FFF)<<4;
  RH1 = (sbrwa(0xC42) & 0x0FFF)<<4;
  home->U10.RH1 = RH1;
  home->U18.PrNOy = PrNOy;
  home->U14.PrNOx = PrNOx;
  home->U22.PrCO_SP = PrCO_SP;
  home->U16.PrCO2p_SP = PrCO2p_SP;
  home->U10.PrCO2p = PrCO2p;
  home->U16.PrCO2e2_SP = PrCO2e2_SP;
  home->U14.PrCO2e2 = PrCO2e2;
  home->U16.PrCO2e1_SP = PrCO2e1_SP;
}

static void BF16_8(void) {
  CF8_0();
  DSt1 = sbrba(0x815);
  home->U28.DSt1 = DSt1;
  EF8_0();
}

static void BF16_9(void) {
  CF1_0();
  RH10 = (sbrwa(0xC54) & 0x0FFF)<<4;
  RH9 = (sbrwa(0xC52) & 0x0FFF)<<4;
  RH8 = (sbrwa(0xC50) & 0x0FFF)<<4;
  RH7 = (sbrwa(0xC4E) & 0x0FFF)<<4;
  RH6 = (sbrwa(0xC4C) & 0x0FFF)<<4;
  RH5 = (sbrwa(0xC4A) & 0x0FFF)<<4;
  RH4 = (sbrwa(0xC48) & 0x0FFF)<<4;
  RH3 = (sbrwa(0xC46) & 0x0FFF)<<4;
  RH2 = (sbrwa(0xC44) & 0x0FFF)<<4;
  home->U12.RH9 = RH9;
  home->U10.RH8 = RH8;
  home->U6.RH7 = RH7;
  home->U6.RH6 = RH6;
  home->U6.RH5 = RH5;
  home->U8.RH4 = RH4;
  home->U8.RH3 = RH3;
  home->U8.RH2 = RH2;
  home->U6.RH10 = RH10;
}

static void BF16_10(void) {
  CF2_0();
  Rnet_cal = (sbrwa(0xC20) & 0x0fff) << 4;
  Rnet = (sbrwa(0xC1E) & 0x0fff) << 4;
  Ta10 = (sbrwa(0xCB2) & 0x0FFF)<<4;
  Ta1 = (sbrwa(0xCA0) & 0x0FFF)<<4;
  home->U0.Ta10 = Ta10;
  home->U2.Ta1 = Ta1;
  home->U8.Rnet_cal = Rnet_cal;
  home->U8.Rnet = Rnet;
}

static void BF16_11(void) {
  CF1_0();
  Tcal = (sbrwa(0xCB4) & 0x0FFF)<<4;
  Ta9 = (sbrwa(0xCB0) & 0x0FFF)<<4;
  Ta8 = (sbrwa(0xCAE) & 0x0FFF)<<4;
  Ta7 = (sbrwa(0xCAC) & 0x0FFF)<<4;
  Ta6 = (sbrwa(0xCAA) & 0x0FFF)<<4;
  Ta5 = (sbrwa(0xCA8) & 0x0FFF)<<4;
  Ta4 = (sbrwa(0xCA6) & 0x0FFF)<<4;
  Ta3 = (sbrwa(0xCA4) & 0x0FFF)<<4;
  Ta2 = (sbrwa(0xCA2) & 0x0FFF)<<4;
  home->U2.Tcal = Tcal;
  home->U4.Ta9 = Ta9;
  home->U0.Ta8 = Ta8;
  home->U0.Ta7 = Ta7;
  home->U2.Ta6 = Ta6;
  home->U4.Ta5 = Ta5;
  home->U4.Ta4 = Ta4;
  home->U4.Ta3 = Ta3;
  home->U2.Ta2 = Ta2;
}

static void BF16_12(void) {
  CF2_0();
  TCO2p = (sbrwa(0xC9E) & 0x0FFF)<<4;
  TCO2e2 = (sbrwa(0xC98) & 0x0FFF)<<4;
  TCO2e1 = (sbrwa(0xC94) & 0x0FFF)<<4;
  Tr1 = (sbrwa(0xCB6) & 0x0FFF)<<4;
  home->U4.Tr1 = Tr1;
  home->U22.TCO2p = TCO2p;
  home->U20.TCO2e2 = TCO2e2;
  home->U12.TCO2e1 = TCO2e1;
}

static void BF16_13(void) {
  CF1_0();
  TS11 = (sbrwa(0xCD0) & 0x0FFF)<<4;
  Ts10 = (sbrwa(0xCCE) & 0x0FFF)<<4;
  Ts5 = (sbrwa(0xCC4) & 0x0FFF)<<4;
  Ts4 = (sbrwa(0xCC2) & 0x0FFF)<<4;
  TS3 = (sbrwa(0xCC0) & 0x0FFF)<<4;
  Ts2 = (sbrwa(0xCBE) & 0x0FFF)<<4;
  Ts1 = (sbrwa(0xCBC) & 0x0FFF)<<4;
  Tr3 = (sbrwa(0xCBA) & 0x0FFF)<<4;
  Tr2 = (sbrwa(0xCB8) & 0x0FFF)<<4;
  home->U6.Ts5 = Ts5;
  home->U6.Ts4 = Ts4;
  home->U2.TS3 = TS3;
  home->U2.Ts2 = Ts2;
  home->U4.TS11 = TS11;
  home->U6.Ts10 = Ts10;
  home->U6.Ts1 = Ts1;
  home->U6.Tr3 = Tr3;
  home->U4.Tr2 = Tr2;
}

static void BF16_14(void) {
  CF2_0();
  TS9 = (sbrwa(0xCCC) & 0x0FFF)<<4;
  TS8 = (sbrwa(0xCCA) & 0x0FFF)<<4;
  Ts7 = (sbrwa(0xCC8) & 0x0FFF)<<4;
  Ts6 = (sbrwa(0xCC6) & 0x0FFF)<<4;
  home->U8.TS9 = TS9;
  home->U8.TS8 = TS8;
  home->U4.Ts7 = Ts7;
  home->U4.Ts6 = Ts6;
}

static void BF16_15(void) {
  CF1_0();
  DSt7 = sbrba(0x875);
  DSt6 = sbrba(0x86A);
  DSt5 = sbrba(0x855);
  DSt4 = sbrba(0x84A);
  DSt3 = sbrba(0x835);
  DSt2 = sbrba(0x82A);
  T_MB = (sbrwa(0xC90) & 0x0FFF)<<4;
  vCO = (sbrwa(0xC1C) & 0x0fff) << 4;
  vO3prf = (sbrwa(0xC1A) & 0x0fff) << 4;
  vCO2prf = (sbrwa(0xC18) & 0x0fff) << 4;
  SolSt = SolStatA;
  home->U0.SolSt = SolSt;
  home->U22.DSt7 = DSt7;
  home->U22.DSt6 = DSt6;
  home->U18.DSt5 = DSt5;
  home->U18.DSt4 = DSt4;
  home->U14.DSt3 = DSt3;
  home->U14.DSt2 = DSt2;
  home->U2.vO3prf = vO3prf;
  home->U2.vCO2prf = vCO2prf;
  home->U2.vCO = vCO;
  home->U12.T_MB = T_MB;
}

static void (*efuncs[16])() = {
  BF16_0,
  BF16_1,
  BF16_2,
  BF16_3,
  BF16_4,
  BF16_5,
  BF16_6,
  BF16_7,
  BF16_8,
  BF16_9,
  BF16_10,
  BF16_11,
  BF16_12,
  BF16_13,
  BF16_14,
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
/* Some temporary defs until everything is in the right place */
#ifndef TS_MFC_LIMIT
  #define TS_MFC_LIMIT 32767
#endif

/* for debugging */
int check_ts = 1;

#define incmod(x,y) if (x==((y)-1)) x = 0; else x++

//static short rowlets;

#if (NROWMINF == 1)
  #define MINF_ROW 0
  #define MINF_ROW_INC
#else
  #define MINF_ROW collector::minf_row
  #define MINF_ROW_INC incmod(collector::minf_row,NROWMINF)
#endif


/* Skeleton main_program section */
int main(int argc, char **argv) {
  oui_init_options(argc, argv);
  nl_error( 0, "Startup");
  tmc_collector col;
  col.init();
  col.init_senders();
  tminitfunc();
  col.operate();
  nl_error( 0, "Shutdown" );
  return 0;
}


/* Skeleton Collect_Row section */
/**
 * Called from a slow timer to make sure we aren't drifting.
 */
void tmc_collector::ts_check() {
  rowlets -= TRN;
  if (rowlets < LOWLIM || rowlets > HIGHLIM)
    ts_checks = TSCHK_RTIME | TSCHK_CHECK;
}

void tmc_collector::event(enum dg_event evt) {
  collector::event(evt);
  if ( evt == dg_event_start ) {
    rowlets = 0;
    ts_checks =  TSCHK_RTIME | TSCHK_REQUIRED;
  #ifdef SUBBUS_H_INCLUDED
    } else if ( evt == dg_event_stop ||
		evt == dg_event_quit ) {
      disarm_sic();
  #endif
  }
}

/**
 * Should come up with a test to guarantee that the right thing
 * happens in all circumstances. 
 */
void tmc_collector::service_row_timer() {
  time_t rtime;
  long dt;
  
  #ifdef SUBBUS_H_INCLUDED
    tick_sic();
  #endif
  if (ts_checks & TSCHK_RTIME) {
    rtime = time(NULL);
    // It's only reasonable to check realtime at even second boundaries
    // This check assumes tm_info.t_stmp.mfc_num % MFSECNUM == 0
    if ((ts_checks & TSCHK_CHECK) && next_minor_frame%MFSECNUM == 0) {
      dt = (next_minor_frame - tm_info.t_stmp.mfc_num)/MFSECNUM;
      dt *= MFSECDEN;
      dt = rtime - dt - tm_info.t_stmp.secs;
      if (dt > SECDRIFT || dt < -SECDRIFT)
        ts_checks |= TSCHK_REQUIRED;
    }
  }
  if ((ts_checks & TSCHK_RTIME) && (ts_checks & TSCHK_REQUIRED)) {
    next_minor_frame = next_minor_frame % LCMMN;
    commit_tstamp( next_minor_frame, rtime );
  } else if ( next_minor_frame == 0 ) {
    //m* = (2^16)%lcm(M,n)
    //m1 = 0
    //t1 = t0 + d(2^16 - m* - m0)/n
    next_minor_frame = ROLLOVER_MFC;
    commit_tstamp( 0, tm_info.t_stmp.secs +
      MFSECDEN *
      ((long)USHRT_MAX - tm_info.t_stmp.mfc_num - next_minor_frame + 1) /
      MFSECNUM );
  } else if ( next_minor_frame - tm_info.t_stmp.mfc_num > TS_MFC_LIMIT) {
    // q = floor((m-m0)/n)
    // m1 = m0+q*n
    // t1 = t0 + d*(m1-m0)/n = t0 + d*q
    unsigned short q = (next_minor_frame - tm_info.t_stmp.mfc_num)/MFSECNUM;
    commit_tstamp( tm_info.t_stmp.mfc_num + q * MFSECNUM,
        tm_info.t_stmp.secs + MFSECDEN * q );
  }
  ts_checks = 0;
  if ( NROWMINF == 1 || MINF_ROW == NROWMINF-1 ) {
    /* Last row of minor frame: Synch Calculations */
    Synch = ( INVSYNCH && collector::majf_row == NROWMAJF-1) ?
      ~SYNCHVAL : SYNCHVAL;
  }

  if ( MINF_ROW == 0 ) {
    MFCtr = next_minor_frame;
    next_minor_frame++;
  }
  
  /* appropriate collection function */
  home = (union home_row *) row[last];
  efuncs[collector::majf_row]();
  rowlets += TRD;
  commit_rows(MFCtr, MINF_ROW, 1);
  MINF_ROW_INC;
  incmod(collector::majf_row, NROWMAJF);
  transmit_data(0);
}


/* Skeleton init_senders_head */
void tmc_collector::init_senders() {
  TMDF_obj = receive("TMDF", &TMDF, sizeof(TMDF), 1);
  SonicData2_obj = receive("SonicData2", &SonicData2, sizeof(SonicData2), 1);
  SonicData1_obj = receive("SonicData1", &SonicData1, sizeof(SonicData1), 1);
  SolStatA_obj = receive("SolStatA", &SolStatA, sizeof(SolStatA), 0);

/* Skeleton init_senders_tail section */
}

/* Skeleton "rest of the file" section */

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
