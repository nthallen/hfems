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
flttime_t flttime; /* edf2ext.awk reading HFEMSall.cdf */
  #include "csv_file.h"
  #include "msg.h"
  #include "tmctime.h"

  #define Ct24_Long(x) (0xFFFFFF & *(TMLONG *)&x)
  #define Ct24_Double(x) (double)Ct24_Long(x)
  #define To_Double(x) (double)(x)

  static double ext_delta = 0.;

  csv_file sonic1("sonic1.csv", 7, "-9999");
  csv_file sonic2("sonic2.csv", 7, "-9999");
  csv_file eddy1("eddy1.csv", 3, "-9999");
  csv_file eddy2("eddy2.csv", 3, "-9999");
  csv_file eddyO3("eddyO3.csv", 2, "-9999");
  csv_file counts("counts.csv", 4, "-9999");
  csv_file status("status.csv", 7, "-9999");
  csv_file pressures("pressures.csv", 9, "-9999");
  csv_file flows("flows.csv", 17, "-9999");
  csv_file profile("profile.csv", 4, "-9999");
  csv_file radiation("radiation.csv", 10, "-9999");
  csv_file RH("RH.csv", 11, "-9999");
  csv_file tair("tair.csv", 12, "-9999");
  csv_file troom("troom.csv", 4, "-9999");
  csv_file tsoil("tsoil.csv", 12, "-9999");
  csv_file tcells("tcells.csv", 5, "-9999");
  csv_file cpu("cpu.csv", 4, "-9999");
  csv_file setpt("setpt.csv", 17, "-9999");
  void initialize(void) {
    {
      char *s;
      s = getenv("EXT_DELTA");
      if (s != NULL) {
        ext_delta=atof(s);
        msg(MSG, "Using Time Delta of %lf", ext_delta);
      }
    }
    sonic1.init();
    sonic1.init_col(0, "Time", "%.3lf");
    sonic1.init_col(1, "ueddy1");
    sonic1.init_col(2, "veddy1");
    sonic1.init_col(3, "weddy1");
    sonic1.init_col(4, "Teddy1");
    sonic1.init_col(5, "sdev_stale1");
    sonic1.init_col(6, "sdrv_stale1");
    sonic2.init();
    sonic2.init_col(0, "Time", "%.3lf");
    sonic2.init_col(1, "ueddy2");
    sonic2.init_col(2, "veddy2");
    sonic2.init_col(3, "weddy2");
    sonic2.init_col(4, "Teddy2");
    sonic2.init_col(5, "sdev_stale2");
    sonic2.init_col(6, "sdrv_stale2");
    eddy1.init();
    eddy1.init_col(0, "Time", "%.2lf");
    eddy1.init_col(1, "vCO2e1", "%.4lf");
    eddy1.init_col(2, "vH2Oe1", "%.4lf");
    eddy2.init();
    eddy2.init_col(0, "Time", "%.2lf");
    eddy2.init_col(1, "vCO2e2", "%.4lf");
    eddy2.init_col(2, "vH2Oe2", "%.4lf");
    eddyO3.init();
    eddyO3.init_col(0, "Time", "%.2lf");
    eddyO3.init_col(1, "vO3ed", "%.4lf");
    counts.init();
    counts.init_col(0, "Time", "%.3lf");
    counts.init_col(1, "NOx");
    counts.init_col(2, "NOy");
    counts.init_col(3, "CtStat");
    status.init();
    status.init_col(0, "Time", "%.1lf");
    status.init_col(1, "DSt0", "%3.0f");
    status.init_col(2, "DSt1", "%3.0f");
    status.init_col(3, "DSt4", "%3.0f");
    status.init_col(4, "DSt5", "%3.0f");
    status.init_col(5, "Dst6", "%3.0f");
    status.init_col(6, "SolSt");
    pressures.init();
    pressures.init_col(0, "Time", "%.1lf");
    pressures.init_col(1, "Pamb");
    pressures.init_col(2, "Pman");
    pressures.init_col(3, "PrCO2p");
    pressures.init_col(4, "PrNOx");
    pressures.init_col(5, "PrNOy");
    pressures.init_col(6, "PrCO2e1");
    pressures.init_col(7, "PrCO2e2");
    pressures.init_col(8, "PrCO");
    flows.init();
    flows.init_col(0, "Time", "%.1lf");
    flows.init_col(1, "FlowT", "%.4lf");
    flows.init_col(2, "FlCO2p", "%.4lf");
    flows.init_col(3, "FlNOx", "%.4lf");
    flows.init_col(4, "FlO3_NOx", "%.4lf");
    flows.init_col(5, "fcNO_NOx", "%.4lf");
    flows.init_col(6, "fcNO2_NOx", "%.4lf");
    flows.init_col(7, "FlNOy", "%.4lf");
    flows.init_col(8, "fcNO_NOy", "%.4lf");
    flows.init_col(9, "fcEff_NOy", "%.4lf");
    flows.init_col(10, "fcZer_NOy", "%.4lf");
    flows.init_col(11, "FlO3_NOy", "%.4lf");
    flows.init_col(12, "FlCO2e1", "%.4lf");
    flows.init_col(13, "FlCO2e2", "%.4lf");
    flows.init_col(14, "FlCO2e3", "%.4lf");
    flows.init_col(15, "fc_CO2e", "%.4lf");
    flows.init_col(16, "FlCO", "%.4lf");
    profile.init();
    profile.init_col(0, "Time", "%.1lf");
    profile.init_col(1, "vCO2prf", "%.4lf");
    profile.init_col(2, "vO3prf", "%.4lf");
    profile.init_col(3, "vCO", "%.4lf");
    radiation.init();
    radiation.init_col(0, "Time", "%.1lf");
    radiation.init_col(1, "Rnet", "%.4lf");
    radiation.init_col(2, "PPFD_top", "%.4lf");
    radiation.init_col(3, "PPFD_mid", "%.4lf");
    radiation.init_col(4, "PPFD_gnd", "%.4lf");
    radiation.init_col(5, "PPFD_ref", "%.4lf");
    radiation.init_col(6, "PPFD_t", "%.4lf");
    radiation.init_col(7, "PPFD_d", "%.4lf");
    radiation.init_col(8, "Rnet_cal", "%.4lf");
    radiation.init_col(9, "PPFD_cal", "%.4lf");
    RH.init();
    RH.init_col(0, "Time", "%.1lf");
    RH.init_col(1, "RH1");
    RH.init_col(2, "RH2");
    RH.init_col(3, "RH3");
    RH.init_col(4, "RH4");
    RH.init_col(5, "RH5");
    RH.init_col(6, "RH6");
    RH.init_col(7, "RH7");
    RH.init_col(8, "RH8");
    RH.init_col(9, "RH9");
    RH.init_col(10, "RH10");
    tair.init();
    tair.init_col(0, "Time", "%.1lf");
    tair.init_col(1, "Ta1", "%.4lf");
    tair.init_col(2, "Ta2", "%.4lf");
    tair.init_col(3, "Ta3", "%.4lf");
    tair.init_col(4, "Ta4", "%.4lf");
    tair.init_col(5, "Ta5", "%.4lf");
    tair.init_col(6, "Ta6", "%.4lf");
    tair.init_col(7, "Ta7", "%.4lf");
    tair.init_col(8, "Ta8", "%.4lf");
    tair.init_col(9, "Ta9", "%.4lf");
    tair.init_col(10, "Ta10", "%.4lf");
    tair.init_col(11, "Tcal", "%.4lf");
    troom.init();
    troom.init_col(0, "Time", "%.1lf");
    troom.init_col(1, "Tr1", "%.4lf");
    troom.init_col(2, "Tr2", "%.4lf");
    troom.init_col(3, "Tr3", "%.4lf");
    tsoil.init();
    tsoil.init_col(0, "Time", "%.1lf");
    tsoil.init_col(1, "Ts1", "%.4lf");
    tsoil.init_col(2, "Ts2", "%.4lf");
    tsoil.init_col(3, "TS3", "%.4lf");
    tsoil.init_col(4, "Ts4", "%.4lf");
    tsoil.init_col(5, "Ts5", "%.4lf");
    tsoil.init_col(6, "Ts6", "%.4lf");
    tsoil.init_col(7, "Ts7", "%.4lf");
    tsoil.init_col(8, "TS8", "%.4lf");
    tsoil.init_col(9, "TS9", "%.4lf");
    tsoil.init_col(10, "Ts10", "%.4lf");
    tsoil.init_col(11, "Ts11", "%.4lf");
    tcells.init();
    tcells.init_col(0, "Time", "%.1lf");
    tcells.init_col(1, "T_MB");
    tcells.init_col(2, "TCO2e1");
    tcells.init_col(3, "TCO2e2");
    tcells.init_col(4, "TCO2p");
    cpu.init();
    cpu.init_col(0, "Time");
    cpu.init_col(1, "CPU_Pct");
    cpu.init_col(2, "Disk");
    cpu.init_col(3, "TDrift");
    setpt.init();
    setpt.init_col(0, "Time", "%.1lf");
    setpt.init_col(1, "Pman_SP");
    setpt.init_col(2, "PrCO2p_SP");
    setpt.init_col(3, "FlCO2p_SP");
    setpt.init_col(4, "PrCO2e1_SP");
    setpt.init_col(5, "PrCO2e2_SP");
    setpt.init_col(6, "PrCO_SP");
    setpt.init_col(7, "fcNO_NOx_SP");
    setpt.init_col(8, "fcNO2_NOx_SP");
    setpt.init_col(9, "fc_CO2e_SP");
    setpt.init_col(10, "fcNO_NOy_SP");
    setpt.init_col(11, "fcEff_NOy_SP");
    setpt.init_col(12, "fcZer_NOy_SP");
    setpt.init_col(13, "FlNOx_SP");
    setpt.init_col(14, "FlNOy_SP");
    setpt.init_col(15, "FlCO2e3_SP");
    setpt.init_col(16, "FlCO_SP");
  }

/* Skeleton console_functions section */
#ifdef TABLELIB_H
  #define phdisplay(x,y) tbl_dispfield(x,y)
#endif

unsigned char V0 = 0x3;
unsigned char V1 = 0x3;
unsigned char V2 = 0xF;
unsigned char V3 = 0x3;
unsigned char V4 = 0x1;
unsigned char V5 = 0x1;
unsigned char V6 = 0x1;
unsigned char V7 = 0x1;
unsigned char V8 = 0x1;
unsigned char V9 = 0x1F;
UINT  MFCtr;
UINT  Synch;
AD12_2_5 Ta1;
AD12_2_5 Ta10;
AD12_2_5 Tr1;
AD12_2_5 Ts1;
AD12_2_5 Ts2;
AD12_2_5 TS3;
AD12_2_5 Ts4;
AD12_2_5 Ts5;
AD12_2_5 Ts10;
AD12_2_5 TS11;
AD12_2_5_RH RH1;
AD12_2_5 PPFD_top;
AD12_2_5 PPFD_mid;
AD12_2_5 PPFD_ref;
AD12_2_5 PPFD_cal;
AD12_2_5 PPFD_gnd;
AD12_2_5x_25 Pamb;
AD12_2_5x_25 Pman;
AD12_Biplrx2 FlCO2p;
AD12_Biplrx2 FlNOx;
AD12_Biplrx2 FlO3_NOx;
AD12_Biplrx2 fcNO_NOx;
AD12_Biplrx2 fcNO2_NOx;
AD12_Biplrx2 FlNOy;
AD12_Biplrx2 fcNO_NOy;
AD12_Biplrx2 fcEff_NOy;
AD12_Biplrx2 fcZer_NOy;
AD12_Biplrx2 FlO3_NOy;
AD12_Biplrx2 FlCO2e1;
AD12_Biplrx2 fc_CO2e;
AD12_2_5x_25 PrCO2e1;
AD12_2_5x2 TCO2e1;
AD12_Biplrx2 FlCO2e2;
AD12_2_5x2 TCO2e2;
AD12_2_5x_25 FlCO2e3;
AD12_Biplrx2 FlCO;
AD12_2_5x_25 PrCO;
AD12_2_5x2 TCO2p;
AD12_2_5 PPFD_t;
AD12_2_5 PPFD_d;
DStat      DSt0;
DStat      DSt1;
DASPt Pman_SP;
DASPt FlCO2p_SP;
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

/* int icvt for TMDF_Rpt -> PERCENT */
static unsigned long int _CVT_0( TMDF_Rpt x) {
  unsigned long int ov;

  if (x < 65535) {
    ov = (x*(5000L)+16383)/(32767);
  } else {
    ov = 100000;
  }
  return ov;
}
const char *US_5_2_f_c( unsigned short int x) {
  static char obuf[6];

  if (x > 9999) return("*****");
  obuf[5] = '\0';
  obuf[4] = (x % 10) + '0';
  x /= 10;
  obuf[3] = (x % 10) + '0';
  x /= 10;
  obuf[2] = '.';
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space0;
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_1() int tcvt TMDF_Rpt -> PERCENT */
const char *_CVT_1(TMDF_Rpt x) {
  unsigned long int iv;

  iv = _CVT_0( x );
  if ( iv > 9999 )
	return "*****";
  return US_5_2_f_c( iv );
}
/* Text array for CPU_Pct_t -> CPU_PCT_text */
static char _CVT_2[256][4] = {
  "  0", "  1", "  2", "  3", "  4", "  5", "  6", "  7", "  8", "  9",
  " 10", " 11", " 12", " 13", " 14", " 15", " 16", " 17", " 18", " 19",
  " 20", " 21", " 22", " 23", " 24", " 25", " 26", " 27", " 28", " 29",
  " 30", " 31", " 32", " 33", " 34", " 35", " 36", " 37", " 38", " 39",
  " 40", " 41", " 42", " 43", " 44", " 45", " 46", " 47", " 48", " 49",
  " 50", " 51", " 52", " 53", " 54", " 55", " 56", " 57", " 58", " 59",
  " 60", " 61", " 62", " 63", " 64", " 65", " 66", " 67", " 68", " 69",
  " 70", " 71", " 72", " 73", " 74", " 75", " 76", " 77", " 78", " 79",
  " 80", " 81", " 82", " 83", " 84", " 85", " 86", " 87", " 88", " 89",
  " 90", " 91", " 92", " 93", " 94", " 95", " 96", " 97", " 98", " 99",
  "100", "101", "102", "103", "104", "105", "106", "107", "108", "109",
  "110", "111", "112", "113", "114", "115", "116", "117", "118", "119",
  "120", "121", "122", "123", "124", "125", "126", "127", "128", "129",
  "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
  "140", "141", "142", "143", "144", "145", "146", "147", "148", "149",
  "150", "151", "152", "153", "154", "155", "156", "157", "158", "159",
  "160", "161", "162", "163", "164", "165", "166", "167", "168", "169",
  "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
  "180", "181", "182", "183", "184", "185", "186", "187", "188", "189",
  "190", "191", "192", "193", "194", "195", "196", "197", "198", "199",
  "200", "201", "202", "203", "204", "205", "206", "207", "208", "209",
  "210", "211", "212", "213", "214", "215", "216", "217", "218", "219",
  "220", "221", "222", "223", "224", "225", "226", "227", "228", "229",
  "230", "231", "232", "233", "234", "235", "236", "237", "238", "239",
  "240", "241", "242", "243", "244", "245", "246", "247", "248", "249",
  "250", "251", "252", "253", "254", "***"
};
/* doub icvt for Drift_t -> Drift_t */
double _CVT_3( Drift_t x ) {
  return (double) floor(  x  * 1E3 + .5 );
}
const char *SL_7_3_f_4( long int x) {
  static char obuf[8];
  int neg;
  int iov;

  if (x < -99999 || x > 999999) return("*******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[7] = '\0';
  obuf[6] = (x % 10) + '0';
  x /= 10;
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = (iov % 10) + '0';
  iov /= 10;
  obuf[3] = '.';
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_4() int tcvt Drift_t -> Drift_t */
const char *_CVT_4(Drift_t x) {
  double iv;

  iv = _CVT_3( x );
  if ( iv < -99999 || iv > 999999 )
	return "*******";
  return SL_7_3_f_4( iv );
}
/* Text array for UBYTE -> UBYTE */
static char _CVT_5[256][4] = {
  "  0", "  1", "  2", "  3", "  4", "  5", "  6", "  7", "  8", "  9",
  " 10", " 11", " 12", " 13", " 14", " 15", " 16", " 17", " 18", " 19",
  " 20", " 21", " 22", " 23", " 24", " 25", " 26", " 27", " 28", " 29",
  " 30", " 31", " 32", " 33", " 34", " 35", " 36", " 37", " 38", " 39",
  " 40", " 41", " 42", " 43", " 44", " 45", " 46", " 47", " 48", " 49",
  " 50", " 51", " 52", " 53", " 54", " 55", " 56", " 57", " 58", " 59",
  " 60", " 61", " 62", " 63", " 64", " 65", " 66", " 67", " 68", " 69",
  " 70", " 71", " 72", " 73", " 74", " 75", " 76", " 77", " 78", " 79",
  " 80", " 81", " 82", " 83", " 84", " 85", " 86", " 87", " 88", " 89",
  " 90", " 91", " 92", " 93", " 94", " 95", " 96", " 97", " 98", " 99",
  "100", "101", "102", "103", "104", "105", "106", "107", "108", "109",
  "110", "111", "112", "113", "114", "115", "116", "117", "118", "119",
  "120", "121", "122", "123", "124", "125", "126", "127", "128", "129",
  "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
  "140", "141", "142", "143", "144", "145", "146", "147", "148", "149",
  "150", "151", "152", "153", "154", "155", "156", "157", "158", "159",
  "160", "161", "162", "163", "164", "165", "166", "167", "168", "169",
  "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
  "180", "181", "182", "183", "184", "185", "186", "187", "188", "189",
  "190", "191", "192", "193", "194", "195", "196", "197", "198", "199",
  "200", "201", "202", "203", "204", "205", "206", "207", "208", "209",
  "210", "211", "212", "213", "214", "215", "216", "217", "218", "219",
  "220", "221", "222", "223", "224", "225", "226", "227", "228", "229",
  "230", "231", "232", "233", "234", "235", "236", "237", "238", "239",
  "240", "241", "242", "243", "244", "245", "246", "247", "248", "249",
  "250", "251", "252", "253", "254", "255"
};
const char *SS_6_2_f_c( short int x) {
  static char obuf[7];
  int neg;

  if (x < -9999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  x /= 10;
  obuf[4] = (x % 10) + '0';
  x /= 10;
  obuf[3] = '.';
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[1] = '-'; goto space0; }
    else goto space1;
  }
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_6() int tcvt Anemo -> Anemo */
const char *_CVT_6(Anemo x) {
  if ( x < -9999 )
	return "******";
  return SS_6_2_f_c( x );
}
const char *US_4_2_u_0( unsigned short int x) {
  static char obuf[5];

  if (x > 9999) return("****");
  obuf[4] = '\0';
  obuf[3] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space2;
  obuf[2] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space1;
  obuf[1] = (x % 10) + '0';
  x /= 10;
  if (x == 0) goto space0;
  obuf[0] = (x % 10) + '0';
  goto nospace;
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_7() int tcvt DASPt -> DASPt */
const char *_CVT_7(DASPt x) {
  if ( x > 9999 )
	return "****";
  return US_4_2_u_0( x );
}
const char *US_5_11_u_0( unsigned short int x) {
  static char obuf[6];
  int iov;

  obuf[5] = '\0';
  obuf[4] = (x % 10) + '0';
  iov = x/10;
  if (iov == 0) goto space3;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space2;
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space1;
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space0;
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space3: obuf[3] = ' ';
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}

/* int icvt for AD12_2_5_RH -> VOLTS */
static unsigned short int _CVT_8( AD12_2_5_RH x) {
  unsigned short int ov;

  ov = (x*(125L)+4096)/(8192);
  return ov;
}
const char *US_6_1_f_c( unsigned short int x) {
  static char obuf[7];
  int iov;

  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = '.';
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space2;
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space1;
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space0;
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space2: obuf[2] = ' ';
  space1: obuf[1] = ' ';
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}

/* int icvt for AD12_2_5x_25 -> VOLTS */
static unsigned short int _CVT_9( AD12_2_5x_25 x) {
  unsigned short int ov;

  ov = (x*(625L)+2048)/(4096);
  return ov;
}
const char *US_6_3_f_c( unsigned short int x) {
  static char obuf[7];
  int iov;

  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = (iov % 10) + '0';
  iov /= 10;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  obuf[2] = '.';
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) goto space0;
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}

/* int icvt for AD12_2_5x2 -> VOLTS */
static unsigned short int _CVT_10( AD12_2_5x2 x) {
  unsigned short int ov;

  ov = (x*(625L)+4096)/(8192);
  return ov;
}

/* int icvt for AD12_2_5 -> VOLTS */
static unsigned short int _CVT_11( AD12_2_5 x) {
  unsigned short int ov;

  ov = (x*(625L)+8192)/(16384);
  return ov;
}

/* int icvt for AD12_Biplrx2 -> VOLTS */
static long int _CVT_12( AD12_Biplrx2 x) {
  long int ov;

  ov = (x*(3125L)+102401024)/(2048)-50000;
  return ov;
}

/* int icvt for AD12_Biplr -> VOLTS */
static long int _CVT_13( AD12_Biplr x) {
  long int ov;

  ov = (x*(3125L)+102400512)/(1024)-100000;
  return ov;
}
/* Text array for SCHAR -> SCHART */
static char _CVT_14[256][5] = {
  "   0", "   1", "   2", "   3", "   4", "   5", "   6", "   7",
  "   8", "   9", "  10", "  11", "  12", "  13", "  14", "  15",
  "  16", "  17", "  18", "  19", "  20", "  21", "  22", "  23",
  "  24", "  25", "  26", "  27", "  28", "  29", "  30", "  31",
  "  32", "  33", "  34", "  35", "  36", "  37", "  38", "  39",
  "  40", "  41", "  42", "  43", "  44", "  45", "  46", "  47",
  "  48", "  49", "  50", "  51", "  52", "  53", "  54", "  55",
  "  56", "  57", "  58", "  59", "  60", "  61", "  62", "  63",
  "  64", "  65", "  66", "  67", "  68", "  69", "  70", "  71",
  "  72", "  73", "  74", "  75", "  76", "  77", "  78", "  79",
  "  80", "  81", "  82", "  83", "  84", "  85", "  86", "  87",
  "  88", "  89", "  90", "  91", "  92", "  93", "  94", "  95",
  "  96", "  97", "  98", "  99", " 100", " 101", " 102", " 103",
  " 104", " 105", " 106", " 107", " 108", " 109", " 110", " 111",
  " 112", " 113", " 114", " 115", " 116", " 117", " 118", " 119",
  " 120", " 121", " 122", " 123", " 124", " 125", " 126", " 127",
  "-128", "-127", "-126", "-125", "-124", "-123", "-122", "-121",
  "-120", "-119", "-118", "-117", "-116", "-115", "-114", "-113",
  "-112", "-111", "-110", "-109", "-108", "-107", "-106", "-105",
  "-104", "-103", "-102", "-101", "-100", " -99", " -98", " -97",
  " -96", " -95", " -94", " -93", " -92", " -91", " -90", " -89",
  " -88", " -87", " -86", " -85", " -84", " -83", " -82", " -81",
  " -80", " -79", " -78", " -77", " -76", " -75", " -74", " -73",
  " -72", " -71", " -70", " -69", " -68", " -67", " -66", " -65",
  " -64", " -63", " -62", " -61", " -60", " -59", " -58", " -57",
  " -56", " -55", " -54", " -53", " -52", " -51", " -50", " -49",
  " -48", " -47", " -46", " -45", " -44", " -43", " -42", " -41",
  " -40", " -39", " -38", " -37", " -36", " -35", " -34", " -33",
  " -32", " -31", " -30", " -29", " -28", " -27", " -26", " -25",
  " -24", " -23", " -22", " -21", " -20", " -19", " -18", " -17",
  " -16", " -15", " -14", " -13", " -12", " -11", " -10", "  -9",
  "  -8", "  -7", "  -6", "  -5", "  -4", "  -3", "  -2", "  -1"
};
/* Text array for UCHAR -> UCHAR */
static char _CVT_15[256][4] = {
  "  0", "  1", "  2", "  3", "  4", "  5", "  6", "  7", "  8", "  9",
  " 10", " 11", " 12", " 13", " 14", " 15", " 16", " 17", " 18", " 19",
  " 20", " 21", " 22", " 23", " 24", " 25", " 26", " 27", " 28", " 29",
  " 30", " 31", " 32", " 33", " 34", " 35", " 36", " 37", " 38", " 39",
  " 40", " 41", " 42", " 43", " 44", " 45", " 46", " 47", " 48", " 49",
  " 50", " 51", " 52", " 53", " 54", " 55", " 56", " 57", " 58", " 59",
  " 60", " 61", " 62", " 63", " 64", " 65", " 66", " 67", " 68", " 69",
  " 70", " 71", " 72", " 73", " 74", " 75", " 76", " 77", " 78", " 79",
  " 80", " 81", " 82", " 83", " 84", " 85", " 86", " 87", " 88", " 89",
  " 90", " 91", " 92", " 93", " 94", " 95", " 96", " 97", " 98", " 99",
  "100", "101", "102", "103", "104", "105", "106", "107", "108", "109",
  "110", "111", "112", "113", "114", "115", "116", "117", "118", "119",
  "120", "121", "122", "123", "124", "125", "126", "127", "128", "129",
  "130", "131", "132", "133", "134", "135", "136", "137", "138", "139",
  "140", "141", "142", "143", "144", "145", "146", "147", "148", "149",
  "150", "151", "152", "153", "154", "155", "156", "157", "158", "159",
  "160", "161", "162", "163", "164", "165", "166", "167", "168", "169",
  "170", "171", "172", "173", "174", "175", "176", "177", "178", "179",
  "180", "181", "182", "183", "184", "185", "186", "187", "188", "189",
  "190", "191", "192", "193", "194", "195", "196", "197", "198", "199",
  "200", "201", "202", "203", "204", "205", "206", "207", "208", "209",
  "210", "211", "212", "213", "214", "215", "216", "217", "218", "219",
  "220", "221", "222", "223", "224", "225", "226", "227", "228", "229",
  "230", "231", "232", "233", "234", "235", "236", "237", "238", "239",
  "240", "241", "242", "243", "244", "245", "246", "247", "248", "249",
  "250", "251", "252", "253", "254", "255"
};


void tminitfunc(void) {
  initialize();
  
}

static void nullfunc(void);
static void EF1_0(void) {
  {
    sonic1.set_time(dtime()+ext_delta);
    sonic1.set_col(1,_CVT_6(home->U0.ueddy1));
    sonic1.set_col(2,_CVT_6(home->U0.veddy1));
    sonic1.set_col(3,_CVT_6(home->U0.weddy1));
    sonic1.set_col(4,_CVT_6(home->U0.teddy1));
    sonic1.set_col(5,_CVT_14[home->U0.sdev_stale1]);
    sonic1.set_col(6,_CVT_15[home->U0.sdrv_stale1]);
  }
  {
    sonic2.set_time(dtime()+ext_delta);
    sonic2.set_col(1,_CVT_6(home->U0.ueddy2));
    sonic2.set_col(2,_CVT_6(home->U0.veddy2));
    sonic2.set_col(3,_CVT_6(home->U0.weddy2));
    sonic2.set_col(4,_CVT_6(home->U0.teddy2));
    sonic2.set_col(5,_CVT_14[home->U0.sdev_stale2]);
    sonic2.set_col(6,_CVT_15[home->U0.sdrv_stale2]);
  }
  {
    counts.set_time(dtime()+ext_delta);
    counts.set_col(1,US_5_11_u_0(home->U0.NOx));
    counts.set_col(2,US_5_11_u_0(home->U0.NOy));
    counts.set_col(3,US_5_11_u_0(home->U0.CtStat));
  }
}

static void EF2_0(void) {
  EF1_0();
  {
    eddy1.set_time(dtime()+ext_delta);
    eddy1.set_col(1,(_CVT_12(home->U0.vCO2e1)*1E-4));
    eddy1.set_col(2,(_CVT_12(home->U0.vH2Oe1)*1E-4));
  }
  {
    eddy2.set_time(dtime()+ext_delta);
    eddy2.set_col(1,(_CVT_12(home->U0.vCO2e2)*1E-4));
    eddy2.set_col(2,(_CVT_12(home->U0.vH2Oe2)*1E-4));
  }
  {
    eddyO3.set_time(dtime()+ext_delta);
    eddyO3.set_col(1,(_CVT_11(home->U0.vO3ed)*1E-3));
  }
}

static void EF8_0(void) {
  EF2_0();
  {
    flttime = itime();
  }
  {
    cpu.set_time(dtime()+ext_delta);
    cpu.set_col(1,_CVT_2[home->U26.CPU_Pct]);
    cpu.set_col(2,_CVT_1(home->U28.Disk));
    cpu.set_col(3,_CVT_4(home->U28.TDrift));
  }
}

static void BF16_0(void) {
  DSt0 = home->U26.DSt0;
  V0 &= ~0x1;
  EF8_0();
}

static void BF16_1(void) {
  fcZer_NOy = home->U16.fcZer_NOy;
  fcNO_NOy_SP = home->U26.fcNO_NOy_SP;
  fcNO_NOy = home->U16.fcNO_NOy;
  fcNO_NOx_SP = home->U24.fcNO_NOx_SP;
  fcNO_NOx = home->U12.fcNO_NOx;
  fcNO2_NOx_SP = home->U14.fcNO2_NOx_SP;
  fcNO2_NOx = home->U12.fcNO2_NOx;
  fcEff_NOy_SP = home->U16.fcEff_NOy_SP;
  fcEff_NOy = home->U10.fcEff_NOy; {
    V9 &= ~0x4;
    V2 &= ~0x4;
  }
  EF1_0();
}

static void BF16_2(void) {
  FlCO = home->U22.FlCO;
  fc_CO2e_SP = home->U24.fc_CO2e_SP;
  fc_CO2e = home->U18.fc_CO2e;
  fcZer_NOy_SP = home->U26.fcZer_NOy_SP; {
    V9 &= ~0x8;
    V2 &= ~0x8;
  }
  EF2_0();
}

static void BF16_3(void) {
  FlNOx_SP = home->U24.FlNOx_SP;
  FlNOx = home->U14.FlNOx;
  FlCO_SP = home->U26.FlCO_SP;
  FlCO2p_SP = home->U20.FlCO2p_SP;
  FlCO2p = home->U10.FlCO2p;
  FlCO2e3_SP = home->U16.FlCO2e3_SP;
  FlCO2e3 = home->U14.FlCO2e3;
  FlCO2e2 = home->U12.FlCO2e2;
  FlCO2e1 = home->U14.FlCO2e1; {
    V9 &= ~0x2;
    V2 &= ~0x1;
  }
  EF1_0();
}

static void BF16_4(void) {
  FlO3_NOy = home->U18.FlO3_NOy;
  FlO3_NOx = home->U16.FlO3_NOx;
  FlNOy_SP = home->U24.FlNOy_SP;
  FlNOy = home->U10.FlNOy; {
    V9 &= ~0x10;
    V2 &= ~0x2;
  }
  EF2_0();
}

static void BF16_5(void) {
  PPFD_ref = home->U14.PPFD_ref;
  PPFD_mid = home->U12.PPFD_mid;
  PPFD_gnd = home->U12.PPFD_gnd;
  PPFD_d = home->U16.PPFD_d;
  PPFD_cal = home->U8.PPFD_cal;
  Pman_SP = home->U12.Pman_SP;
  Pman = home->U10.Pman;
  Pamb = home->U10.Pamb; {
    V9 &= ~0x1;
    V3 &= ~0x2;
    V1 &= ~0x1;
  }
  EF1_0();
  if (!(V2)) {
    {
      flows.set_time(dtime()+ext_delta);
      flows.set_col(1,(_CVT_12(home->U8.FlowT)*1E-4));
      flows.set_col(2,(_CVT_12(FlCO2p)*1E-4));
      flows.set_col(3,(_CVT_12(FlNOx)*1E-4));
      flows.set_col(4,(_CVT_12(FlO3_NOx)*1E-4));
      flows.set_col(5,(_CVT_12(fcNO_NOx)*1E-4));
      flows.set_col(6,(_CVT_12(fcNO2_NOx)*1E-4));
      flows.set_col(7,(_CVT_12(FlNOy)*1E-4));
      flows.set_col(8,(_CVT_12(fcNO_NOy)*1E-4));
      flows.set_col(9,(_CVT_12(fcEff_NOy)*1E-4));
      flows.set_col(10,(_CVT_12(fcZer_NOy)*1E-4));
      flows.set_col(11,(_CVT_12(FlO3_NOy)*1E-4));
      flows.set_col(12,(_CVT_12(FlCO2e1)*1E-4));
      flows.set_col(13,(_CVT_12(FlCO2e2)*1E-4));
      flows.set_col(14,(_CVT_9(FlCO2e3)*1E-3));
      flows.set_col(15,(_CVT_12(fc_CO2e)*1E-4));
      flows.set_col(16,(_CVT_12(FlCO)*1E-4));
    }
  }
}

static void BF16_6(void) {
  PrCO2e1 = home->U20.PrCO2e1;
  PrCO = home->U20.PrCO;
  PPFD_top = home->U10.PPFD_top;
  PPFD_t = home->U14.PPFD_t; {
    V3 &= ~0x1;
    V1 &= ~0x2;
  }
  EF2_0();
}

static void BF16_7(void) {
  RH1 = home->U10.RH1;
  V4 &= ~0x1;
  EF1_0();
  if (!(V1)) {
    {
      pressures.set_time(dtime()+ext_delta);
      pressures.set_col(1,US_6_3_f_c(_CVT_9(Pamb)));
      pressures.set_col(2,US_6_3_f_c(_CVT_9(Pman)));
      pressures.set_col(3,US_6_3_f_c(_CVT_9(home->U10.PrCO2p)));
      pressures.set_col(4,US_6_3_f_c(_CVT_9(home->U14.PrNOx)));
      pressures.set_col(5,US_6_3_f_c(_CVT_9(home->U18.PrNOy)));
      pressures.set_col(6,US_6_3_f_c(_CVT_9(PrCO2e1)));
      pressures.set_col(7,US_6_3_f_c(_CVT_9(home->U14.PrCO2e2)));
      pressures.set_col(8,US_6_3_f_c(_CVT_9(PrCO)));
    }
  }
  if (!(V9)) {
    {
      setpt.set_time(dtime()+ext_delta);
      setpt.set_col(1,_CVT_7(Pman_SP));
      setpt.set_col(2,_CVT_7(home->U16.PrCO2p_SP));
      setpt.set_col(3,_CVT_7(FlCO2p_SP));
      setpt.set_col(4,_CVT_7(home->U16.PrCO2e1_SP));
      setpt.set_col(5,_CVT_7(home->U16.PrCO2e2_SP));
      setpt.set_col(6,_CVT_7(home->U22.PrCO_SP));
      setpt.set_col(7,_CVT_7(fcNO_NOx_SP));
      setpt.set_col(8,_CVT_7(fcNO2_NOx_SP));
      setpt.set_col(9,_CVT_7(fc_CO2e_SP));
      setpt.set_col(10,_CVT_7(fcNO_NOy_SP));
      setpt.set_col(11,_CVT_7(fcEff_NOy_SP));
      setpt.set_col(12,_CVT_7(fcZer_NOy_SP));
      setpt.set_col(13,_CVT_7(FlNOx_SP));
      setpt.set_col(14,_CVT_7(FlNOy_SP));
      setpt.set_col(15,_CVT_7(FlCO2e3_SP));
      setpt.set_col(16,_CVT_7(FlCO_SP));
    }
  }
}

static void BF16_8(void) {
  DSt1 = home->U28.DSt1;
  V0 &= ~0x2;
  EF8_0();
}

static void BF16_9(void) {
  EF1_0();
  if (!(V4)) {
    {
      RH.set_time(dtime()+ext_delta);
      RH.set_col(1,US_6_1_f_c(_CVT_8(RH1)));
      RH.set_col(2,US_6_1_f_c(_CVT_8(home->U8.RH2)));
      RH.set_col(3,US_6_1_f_c(_CVT_8(home->U8.RH3)));
      RH.set_col(4,US_6_1_f_c(_CVT_8(home->U8.RH4)));
      RH.set_col(5,US_6_1_f_c(_CVT_8(home->U6.RH5)));
      RH.set_col(6,US_6_1_f_c(_CVT_8(home->U6.RH6)));
      RH.set_col(7,US_6_1_f_c(_CVT_8(home->U6.RH7)));
      RH.set_col(8,US_6_1_f_c(_CVT_8(home->U10.RH8)));
      RH.set_col(9,US_6_1_f_c(_CVT_8(home->U12.RH9)));
      RH.set_col(10,US_6_1_f_c(_CVT_8(home->U6.RH10)));
    }
  }
}

static void BF16_10(void) {
  Ta10 = home->U0.Ta10;
  Ta1 = home->U2.Ta1;
  V5 &= ~0x1;
  EF2_0();
  if (!(V3)) {
    {
      radiation.set_time(dtime()+ext_delta);
      radiation.set_col(1,(_CVT_13(home->U8.Rnet)*1E-4));
      radiation.set_col(2,(_CVT_11(PPFD_top)*1E-3));
      radiation.set_col(3,(_CVT_11(PPFD_mid)*1E-3));
      radiation.set_col(4,(_CVT_11(PPFD_gnd)*1E-3));
      radiation.set_col(5,(_CVT_11(PPFD_ref)*1E-3));
      radiation.set_col(6,(_CVT_11(PPFD_t)*1E-3));
      radiation.set_col(7,(_CVT_11(PPFD_d)*1E-3));
      radiation.set_col(8,(_CVT_13(home->U8.Rnet_cal)*1E-4));
      radiation.set_col(9,(_CVT_11(PPFD_cal)*1E-3));
    }
  }
}

static void BF16_11(void) {
  EF1_0();
  if (!(V5)) {
    {
      tair.set_time(dtime()+ext_delta);
      tair.set_col(1,(_CVT_11(Ta1)*1E-3));
      tair.set_col(2,(_CVT_11(home->U2.Ta2)*1E-3));
      tair.set_col(3,(_CVT_11(home->U4.Ta3)*1E-3));
      tair.set_col(4,(_CVT_11(home->U4.Ta4)*1E-3));
      tair.set_col(5,(_CVT_11(home->U4.Ta5)*1E-3));
      tair.set_col(6,(_CVT_11(home->U2.Ta6)*1E-3));
      tair.set_col(7,(_CVT_11(home->U0.Ta7)*1E-3));
      tair.set_col(8,(_CVT_11(home->U0.Ta8)*1E-3));
      tair.set_col(9,(_CVT_11(home->U4.Ta9)*1E-3));
      tair.set_col(10,(_CVT_11(Ta10)*1E-3));
      tair.set_col(11,(_CVT_11(home->U2.Tcal)*1E-3));
    }
  }
}

static void BF16_12(void) {
  Tr1 = home->U4.Tr1;
  TCO2p = home->U22.TCO2p;
  TCO2e2 = home->U20.TCO2e2;
  TCO2e1 = home->U12.TCO2e1; {
    V8 &= ~0x1;
    V6 &= ~0x1;
  }
  EF2_0();
}

static void BF16_13(void) {
  Ts5 = home->U6.Ts5;
  Ts4 = home->U6.Ts4;
  TS3 = home->U2.TS3;
  Ts2 = home->U2.Ts2;
  TS11 = home->U4.TS11;
  Ts10 = home->U6.Ts10;
  Ts1 = home->U6.Ts1;
  V7 &= ~0x1;
  EF1_0();
  if (!(V6)) {
    {
      troom.set_time(dtime()+ext_delta);
      troom.set_col(1,(_CVT_11(Tr1)*1E-3));
      troom.set_col(2,(_CVT_11(home->U4.Tr2)*1E-3));
      troom.set_col(3,(_CVT_11(home->U6.Tr3)*1E-3));
    }
  }
}

static void BF16_14(void) {
  EF2_0();
  if (!(V7)) {
    {
      tsoil.set_time(dtime()+ext_delta);
      tsoil.set_col(1,(_CVT_11(Ts1)*1E-3));
      tsoil.set_col(2,(_CVT_11(Ts2)*1E-3));
      tsoil.set_col(3,(_CVT_11(TS3)*1E-3));
      tsoil.set_col(4,(_CVT_11(Ts4)*1E-3));
      tsoil.set_col(5,(_CVT_11(Ts5)*1E-3));
      tsoil.set_col(6,(_CVT_11(home->U4.Ts6)*1E-3));
      tsoil.set_col(7,(_CVT_11(home->U4.Ts7)*1E-3));
      tsoil.set_col(8,(_CVT_11(home->U8.TS8)*1E-3));
      tsoil.set_col(9,(_CVT_11(home->U8.TS9)*1E-3));
      tsoil.set_col(10,(_CVT_11(Ts10)*1E-3));
      tsoil.set_col(11,(_CVT_11(TS11)*1E-3));
    }
  }
}

static void BF16_15(void) {
  EF1_0();
  if (!(V0)) {
    {
      status.set_time(dtime()+ext_delta);
      status.set_col(1,DSt0);
      status.set_col(2,DSt1);
      status.set_col(3,home->U18.DSt4);
      status.set_col(4,home->U18.DSt5);
      status.set_col(5,home->U22.DSt6);
      status.set_col(6,_CVT_5[home->U0.SolSt]);
    }
  }
  {
    profile.set_time(dtime()+ext_delta);
    profile.set_col(1,(_CVT_13(home->U2.vCO2prf)*1E-4));
    profile.set_col(2,(_CVT_13(home->U2.vO3prf)*1E-4));
    profile.set_col(3,(_CVT_13(home->U2.vCO)*1E-4));
  }
  if (!(V8)) {
    {
      tcells.set_time(dtime()+ext_delta);
      tcells.set_col(1,US_6_3_f_c(_CVT_11(home->U12.T_MB)));
      tcells.set_col(2,US_6_3_f_c(_CVT_10(TCO2e1)));
      tcells.set_col(3,US_6_3_f_c(_CVT_10(TCO2e2)));
      tcells.set_col(4,US_6_3_f_c(_CVT_10(TCO2p)));
    }
  }
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

static void IVF16_0(void) {
  V0 |= 0x1;
}
static void IVF16_1(void) { {
    V9 |= 0x4;
    V2 |= 0x4;
  }
}
static void IVF16_2(void) { {
    V9 |= 0x8;
    V2 |= 0x8;
  }
}
static void IVF16_3(void) { {
    V9 |= 0x2;
    V2 |= 0x1;
  }
}
static void IVF16_4(void) { {
    V9 |= 0x10;
    V2 |= 0x2;
  }
}
static void IVF16_5(void) { {
    V9 |= 0x1;
    V3 |= 0x2;
    V1 |= 0x1;
  }
}
static void IVF16_6(void) { {
    V3 |= 0x1;
    V1 |= 0x2;
  }
}
static void IVF16_7(void) {
  V4 |= 0x1;
}
static void IVF16_8(void) {
  V0 |= 0x2;
}
static void IVF16_10(void) {
  V5 |= 0x1;
}
static void IVF16_12(void) { {
    V8 |= 0x1;
    V6 |= 0x1;
  }
}
static void IVF16_13(void) {
  V7 |= 0x1;
}
#define IVFUNCS
static void (*ivfuncs[16])() = {
  IVF16_0,
  IVF16_1,
  IVF16_2,
  IVF16_3,
  IVF16_4,
  IVF16_5,
  IVF16_6,
  IVF16_7,
  IVF16_8,
  nullfunc,
  IVF16_10,
  nullfunc,
  IVF16_12,
  IVF16_13,
  nullfunc,
  nullfunc
};

static void nullfunc(void){}
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
