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
  /* nctable output */
  #include "nctable.h"
  static int HFEMS_winnum;

  static unsigned char nct_HFEMS_r38[] = { 9, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r37[] = { 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r36[] = { 9, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r35[] = { 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r34[] = { 9, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r33[] = { 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r32[] = { 9, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r31[] = { 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r30[] = { 9, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r29[] = { 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r28[] = { 9, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r27[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r26[] = { 9, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r25[] = { 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r24[] = { 9, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r23[] = { 36, 36, 39, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r22[] = { 9, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r21[] = { 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r20[] = { 9, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r19[] = { 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r18[] = { 9, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r17[] = { 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r16[] = { 9, 36, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r15[] = { 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r14[] = { 9, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r13[] = { 9, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r12[] = { 9, 36, 36, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r11[] = { 36, 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r10[] = { 9, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r9[] = { 36, 36, 36, 36, 36, 36, 27, 0 };
  static unsigned char nct_HFEMS_r8[] = { 37, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r7[] = { 37, 4, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r6[] = { 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 0 };
  static unsigned char nct_HFEMS_r5[] = { 12, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 39, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 39, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 39, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 36, 30, 0 };
  static unsigned char nct_HFEMS_r4[] = { 28, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 31, 4, 4, 4, 4, 31, 4, 4, 31, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r3[] = { 37, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 13, 4, 4, 4, 4, 13, 31, 4, 13, 4, 4, 4, 4, 31, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r2[] = { 37, 4, 4, 4, 4, 4, 4, 4, 4, 31, 4, 4, 4, 4, 4, 4, 4, 13, 4, 4, 4, 4, 4, 4, 13, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r1[] = { 37, 4, 4, 4, 4, 4, 4, 4, 4, 40, 4, 4, 4, 4, 4, 31, 4, 4, 4, 31, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 };
  static unsigned char nct_HFEMS_r0[] = { 10, 4, 4, 4, 4, 4, 4, 4, 4, 13, 4, 4, 4, 4, 4, 13, 4, 4, 4, 13, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 0 };

  static void HFEMS_redraw(void) {
    nct_clear(HFEMS_winnum);
    nct_string( HFEMS_winnum, 4, 0, 7, "Sonic" );
    nct_string( HFEMS_winnum, 4, 1, 1, "ueddy1:" );
    nct_string( HFEMS_winnum, 2, 1, 9, "      " );
    nct_string( HFEMS_winnum, 4, 2, 1, "veddy1:" );
    nct_string( HFEMS_winnum, 2, 2, 9, "      " );
    nct_string( HFEMS_winnum, 4, 3, 1, "weddy1:" );
    nct_string( HFEMS_winnum, 2, 3, 9, "      " );
    nct_string( HFEMS_winnum, 4, 4, 1, "Teddy1:" );
    nct_string( HFEMS_winnum, 2, 4, 9, "      " );
    nct_string( HFEMS_winnum, 4, 5, 1, "ueddy2:" );
    nct_string( HFEMS_winnum, 2, 5, 9, "      " );
    nct_string( HFEMS_winnum, 4, 6, 1, "veddy2:" );
    nct_string( HFEMS_winnum, 2, 6, 9, "      " );
    nct_string( HFEMS_winnum, 4, 7, 1, "weddy2:" );
    nct_string( HFEMS_winnum, 2, 7, 9, "      " );
    nct_string( HFEMS_winnum, 4, 8, 1, "Teddy2:" );
    nct_string( HFEMS_winnum, 2, 8, 9, "      " );
    nct_string( HFEMS_winnum, 4, 11, 78, "Sonic" );
    nct_string( HFEMS_winnum, 4, 12, 72, "Sdev1:" );
    nct_string( HFEMS_winnum, 2, 12, 79, "    " );
    nct_string( HFEMS_winnum, 4, 13, 72, "Sdrv1:" );
    nct_string( HFEMS_winnum, 2, 13, 80, "   " );
    nct_string( HFEMS_winnum, 4, 14, 72, "Sdev2:" );
    nct_string( HFEMS_winnum, 2, 14, 79, "    " );
    nct_string( HFEMS_winnum, 4, 15, 72, "Sdrv2:" );
    nct_string( HFEMS_winnum, 2, 15, 80, "   " );
    nct_string( HFEMS_winnum, 4, 9, 8, "Eddy" );
    nct_string( HFEMS_winnum, 4, 10, 1, "vCO2e1:" );
    nct_string( HFEMS_winnum, 2, 10, 9, "      " );
    nct_string( HFEMS_winnum, 4, 11, 1, "vH2Oe1:" );
    nct_string( HFEMS_winnum, 2, 11, 9, "      " );
    nct_string( HFEMS_winnum, 4, 12, 1, "vCO2e2:" );
    nct_string( HFEMS_winnum, 2, 12, 9, "      " );
    nct_string( HFEMS_winnum, 4, 13, 1, "vH2Oe2:" );
    nct_string( HFEMS_winnum, 2, 13, 9, "      " );
    nct_string( HFEMS_winnum, 4, 14, 1, "vO3ed:" );
    nct_string( HFEMS_winnum, 2, 14, 9, "      " );
    nct_string( HFEMS_winnum, 4, 15, 6, "Profile" );
    nct_string( HFEMS_winnum, 4, 16, 1, "vCO2prf:" );
    nct_string( HFEMS_winnum, 2, 16, 10, "      " );
    nct_string( HFEMS_winnum, 4, 17, 1, "vO3prf:" );
    nct_string( HFEMS_winnum, 2, 17, 10, "      " );
    nct_string( HFEMS_winnum, 4, 18, 1, "vCO:" );
    nct_string( HFEMS_winnum, 2, 18, 10, "      " );
    nct_string( HFEMS_winnum, 4, 16, 77, "Counts" );
    nct_string( HFEMS_winnum, 4, 17, 72, "NOx:" );
    nct_string( HFEMS_winnum, 2, 17, 77, "     " );
    nct_string( HFEMS_winnum, 4, 18, 72, "NOy:" );
    nct_string( HFEMS_winnum, 2, 18, 77, "     " );
    nct_string( HFEMS_winnum, 4, 24, 51, "Status" );
    nct_string( HFEMS_winnum, 4, 25, 37, "DSt0:" );
    nct_string( HFEMS_winnum, 2, 25, 43, "        " );
    nct_string( HFEMS_winnum, 4, 26, 37, "DSt1:" );
    nct_string( HFEMS_winnum, 2, 26, 43, "        " );
    nct_string( HFEMS_winnum, 4, 27, 37, "DSt4:" );
    nct_string( HFEMS_winnum, 2, 27, 43, "        " );
    nct_string( HFEMS_winnum, 4, 28, 37, "DSt5:" );
    nct_string( HFEMS_winnum, 2, 28, 43, "        " );
    nct_string( HFEMS_winnum, 4, 29, 37, "DSt6:" );
    nct_string( HFEMS_winnum, 2, 29, 43, "        " );
    nct_string( HFEMS_winnum, 4, 17, 43, "PrFl" );
    nct_string( HFEMS_winnum, 4, 18, 37, "Pman:" );
    nct_string( HFEMS_winnum, 2, 18, 46, "      " );
    nct_string( HFEMS_winnum, 4, 19, 37, "PrCO2p:" );
    nct_string( HFEMS_winnum, 2, 19, 46, "      " );
    nct_string( HFEMS_winnum, 4, 20, 37, "FlCO2p:" );
    nct_string( HFEMS_winnum, 2, 20, 46, "      " );
    nct_string( HFEMS_winnum, 4, 21, 37, "FlCO2e3:" );
    nct_string( HFEMS_winnum, 2, 21, 46, "      " );
    nct_string( HFEMS_winnum, 4, 22, 37, "PrCO:" );
    nct_string( HFEMS_winnum, 2, 22, 46, "      " );
    nct_string( HFEMS_winnum, 4, 23, 37, "FlCO:" );
    nct_string( HFEMS_winnum, 2, 23, 46, "      " );
    nct_string( HFEMS_winnum, 4, 17, 59, "cal_fc" );
    nct_string( HFEMS_winnum, 4, 18, 53, "fc_CO2e:" );
    nct_string( HFEMS_winnum, 2, 18, 65, "      " );
    nct_string( HFEMS_winnum, 4, 19, 53, "fc_NO_NOx:" );
    nct_string( HFEMS_winnum, 2, 19, 65, "      " );
    nct_string( HFEMS_winnum, 4, 20, 53, "fc_NO2_NOx:" );
    nct_string( HFEMS_winnum, 2, 20, 65, "      " );
    nct_string( HFEMS_winnum, 4, 21, 53, "fc_NO_NOy:" );
    nct_string( HFEMS_winnum, 2, 21, 65, "      " );
    nct_string( HFEMS_winnum, 4, 19, 5, "Radiation" );
    nct_string( HFEMS_winnum, 4, 20, 1, "Rnet:" );
    nct_string( HFEMS_winnum, 2, 20, 11, "       " );
    nct_string( HFEMS_winnum, 4, 21, 1, "Rnet_cal:" );
    nct_string( HFEMS_winnum, 2, 21, 11, "       " );
    nct_string( HFEMS_winnum, 4, 22, 1, "PPFD_top:" );
    nct_string( HFEMS_winnum, 2, 22, 11, "       " );
    nct_string( HFEMS_winnum, 4, 23, 1, "PPFD_mid:" );
    nct_string( HFEMS_winnum, 2, 23, 11, "       " );
    nct_string( HFEMS_winnum, 4, 24, 1, "PPFD_ref:" );
    nct_string( HFEMS_winnum, 2, 24, 11, "       " );
    nct_string( HFEMS_winnum, 4, 25, 1, "PPFD_cal:" );
    nct_string( HFEMS_winnum, 2, 25, 11, "       " );
    nct_string( HFEMS_winnum, 4, 26, 1, "PPFD_gnd:" );
    nct_string( HFEMS_winnum, 2, 26, 11, "       " );
    nct_string( HFEMS_winnum, 4, 27, 1, "PPFD_t:" );
    nct_string( HFEMS_winnum, 2, 27, 11, "       " );
    nct_string( HFEMS_winnum, 4, 28, 1, "PPFD_d:" );
    nct_string( HFEMS_winnum, 2, 28, 11, "       " );
    nct_string( HFEMS_winnum, 4, 0, 24, "Pressure" );
    nct_string( HFEMS_winnum, 4, 1, 19, "Pamb:" );
    nct_string( HFEMS_winnum, 2, 1, 28, "      " );
    nct_string( HFEMS_winnum, 4, 2, 19, "Pman:" );
    nct_string( HFEMS_winnum, 2, 2, 28, "      " );
    nct_string( HFEMS_winnum, 4, 3, 19, "PrCO2p:" );
    nct_string( HFEMS_winnum, 2, 3, 28, "      " );
    nct_string( HFEMS_winnum, 4, 4, 19, "PrCO2e1:" );
    nct_string( HFEMS_winnum, 2, 4, 28, "      " );
    nct_string( HFEMS_winnum, 4, 5, 19, "PrCO2e2:" );
    nct_string( HFEMS_winnum, 2, 5, 28, "      " );
    nct_string( HFEMS_winnum, 4, 6, 19, "PrCO:" );
    nct_string( HFEMS_winnum, 2, 6, 28, "      " );
    nct_string( HFEMS_winnum, 4, 7, 19, "PrNOx:" );
    nct_string( HFEMS_winnum, 2, 7, 28, "      " );
    nct_string( HFEMS_winnum, 4, 8, 19, "PrNOy:" );
    nct_string( HFEMS_winnum, 2, 8, 28, "      " );
    nct_string( HFEMS_winnum, 4, 9, 26, "Flow" );
    nct_string( HFEMS_winnum, 4, 10, 19, "FlowT:" );
    nct_string( HFEMS_winnum, 2, 10, 30, "      " );
    nct_string( HFEMS_winnum, 4, 11, 19, "FlCO2p:" );
    nct_string( HFEMS_winnum, 2, 11, 30, "      " );
    nct_string( HFEMS_winnum, 4, 12, 19, "FlCO2e1:" );
    nct_string( HFEMS_winnum, 2, 12, 30, "      " );
    nct_string( HFEMS_winnum, 4, 13, 19, "FlCO2e2:" );
    nct_string( HFEMS_winnum, 2, 13, 30, "      " );
    nct_string( HFEMS_winnum, 4, 14, 19, "FlCO2e3:" );
    nct_string( HFEMS_winnum, 2, 14, 30, "      " );
    nct_string( HFEMS_winnum, 4, 15, 19, "FlCO:" );
    nct_string( HFEMS_winnum, 2, 15, 30, "      " );
    nct_string( HFEMS_winnum, 4, 16, 19, "FlNOx:" );
    nct_string( HFEMS_winnum, 2, 16, 30, "      " );
    nct_string( HFEMS_winnum, 4, 17, 19, "FlO3_NOx:" );
    nct_string( HFEMS_winnum, 2, 17, 30, "      " );
    nct_string( HFEMS_winnum, 4, 18, 19, "FlNOy:" );
    nct_string( HFEMS_winnum, 2, 18, 30, "      " );
    nct_string( HFEMS_winnum, 4, 19, 19, "FlO3_NOy:" );
    nct_string( HFEMS_winnum, 2, 19, 30, "      " );
    nct_string( HFEMS_winnum, 4, 20, 19, "fcNO_NOx:" );
    nct_string( HFEMS_winnum, 2, 20, 30, "      " );
    nct_string( HFEMS_winnum, 4, 21, 19, "fcNO2_NOx:" );
    nct_string( HFEMS_winnum, 2, 21, 30, "      " );
    nct_string( HFEMS_winnum, 4, 22, 19, "fcNO_NOy:" );
    nct_string( HFEMS_winnum, 2, 22, 30, "      " );
    nct_string( HFEMS_winnum, 4, 23, 19, "fcEff_NOy:" );
    nct_string( HFEMS_winnum, 2, 23, 30, "      " );
    nct_string( HFEMS_winnum, 4, 24, 19, "fcZer_NOy:" );
    nct_string( HFEMS_winnum, 2, 24, 30, "      " );
    nct_string( HFEMS_winnum, 4, 25, 19, "fc_CO2e:" );
    nct_string( HFEMS_winnum, 2, 25, 30, "      " );
    nct_string( HFEMS_winnum, 5, 0, 79, "RH" );
    nct_string( HFEMS_winnum, 4, 1, 72, "RH1:" );
    nct_string( HFEMS_winnum, 2, 1, 78, "      " );
    nct_string( HFEMS_winnum, 4, 2, 72, "RH2:" );
    nct_string( HFEMS_winnum, 2, 2, 78, "      " );
    nct_string( HFEMS_winnum, 4, 3, 72, "RH3:" );
    nct_string( HFEMS_winnum, 2, 3, 78, "      " );
    nct_string( HFEMS_winnum, 4, 4, 72, "RH4:" );
    nct_string( HFEMS_winnum, 2, 4, 78, "      " );
    nct_string( HFEMS_winnum, 4, 5, 72, "RH5:" );
    nct_string( HFEMS_winnum, 2, 5, 78, "      " );
    nct_string( HFEMS_winnum, 4, 6, 72, "RH6:" );
    nct_string( HFEMS_winnum, 2, 6, 78, "      " );
    nct_string( HFEMS_winnum, 4, 7, 72, "RH7:" );
    nct_string( HFEMS_winnum, 2, 7, 78, "      " );
    nct_string( HFEMS_winnum, 4, 8, 72, "RH8:" );
    nct_string( HFEMS_winnum, 2, 8, 78, "      " );
    nct_string( HFEMS_winnum, 4, 9, 72, "RH9:" );
    nct_string( HFEMS_winnum, 2, 9, 78, "      " );
    nct_string( HFEMS_winnum, 4, 10, 72, "RH10:" );
    nct_string( HFEMS_winnum, 2, 10, 78, "      " );
    nct_string( HFEMS_winnum, 4, 0, 45, "Ts" );
    nct_string( HFEMS_winnum, 4, 1, 37, "Ts1:" );
    nct_string( HFEMS_winnum, 2, 1, 45, "      " );
    nct_string( HFEMS_winnum, 4, 2, 37, "Ts2:" );
    nct_string( HFEMS_winnum, 2, 2, 45, "      " );
    nct_string( HFEMS_winnum, 4, 3, 37, "Ts3:" );
    nct_string( HFEMS_winnum, 2, 3, 45, "      " );
    nct_string( HFEMS_winnum, 4, 4, 37, "Ts4:" );
    nct_string( HFEMS_winnum, 2, 4, 45, "      " );
    nct_string( HFEMS_winnum, 4, 5, 37, "Ts5:" );
    nct_string( HFEMS_winnum, 2, 5, 45, "      " );
    nct_string( HFEMS_winnum, 4, 6, 37, "Ts6:" );
    nct_string( HFEMS_winnum, 2, 6, 45, "      " );
    nct_string( HFEMS_winnum, 4, 7, 37, "Ts7:" );
    nct_string( HFEMS_winnum, 2, 7, 45, "      " );
    nct_string( HFEMS_winnum, 4, 8, 37, "Ts8:" );
    nct_string( HFEMS_winnum, 2, 8, 45, "      " );
    nct_string( HFEMS_winnum, 4, 9, 37, "Ts9:" );
    nct_string( HFEMS_winnum, 2, 9, 45, "      " );
    nct_string( HFEMS_winnum, 4, 10, 37, "Ts10:" );
    nct_string( HFEMS_winnum, 2, 10, 45, "      " );
    nct_string( HFEMS_winnum, 4, 11, 37, "Ts11:" );
    nct_string( HFEMS_winnum, 2, 11, 45, "      " );
    nct_string( HFEMS_winnum, 4, 12, 43, "TCells" );
    nct_string( HFEMS_winnum, 4, 13, 37, "T_MB:" );
    nct_string( HFEMS_winnum, 2, 13, 45, "      " );
    nct_string( HFEMS_winnum, 4, 14, 37, "TCO2e1:" );
    nct_string( HFEMS_winnum, 2, 14, 45, "      " );
    nct_string( HFEMS_winnum, 4, 15, 37, "TCO2e2:" );
    nct_string( HFEMS_winnum, 2, 15, 45, "      " );
    nct_string( HFEMS_winnum, 4, 16, 37, "TCO2p:" );
    nct_string( HFEMS_winnum, 2, 16, 45, "      " );
    nct_string( HFEMS_winnum, 4, 0, 63, "Ta" );
    nct_string( HFEMS_winnum, 4, 1, 56, "Ta1:" );
    nct_string( HFEMS_winnum, 2, 1, 62, "      " );
    nct_string( HFEMS_winnum, 4, 2, 56, "Ta2:" );
    nct_string( HFEMS_winnum, 2, 2, 62, "      " );
    nct_string( HFEMS_winnum, 4, 3, 56, "Ta3:" );
    nct_string( HFEMS_winnum, 2, 3, 62, "      " );
    nct_string( HFEMS_winnum, 4, 4, 56, "Ta4:" );
    nct_string( HFEMS_winnum, 2, 4, 62, "      " );
    nct_string( HFEMS_winnum, 4, 5, 56, "Ta5:" );
    nct_string( HFEMS_winnum, 2, 5, 62, "      " );
    nct_string( HFEMS_winnum, 4, 6, 56, "Ta6:" );
    nct_string( HFEMS_winnum, 2, 6, 62, "      " );
    nct_string( HFEMS_winnum, 4, 7, 56, "Ta7:" );
    nct_string( HFEMS_winnum, 2, 7, 62, "      " );
    nct_string( HFEMS_winnum, 4, 8, 56, "Ta8:" );
    nct_string( HFEMS_winnum, 2, 8, 62, "      " );
    nct_string( HFEMS_winnum, 4, 9, 56, "Ta9:" );
    nct_string( HFEMS_winnum, 2, 9, 62, "      " );
    nct_string( HFEMS_winnum, 4, 10, 56, "Ta10:" );
    nct_string( HFEMS_winnum, 2, 10, 62, "      " );
    nct_string( HFEMS_winnum, 4, 11, 56, "Tcal:" );
    nct_string( HFEMS_winnum, 2, 11, 62, "      " );
    nct_string( HFEMS_winnum, 4, 12, 56, "Tr1:" );
    nct_string( HFEMS_winnum, 2, 12, 62, "      " );
    nct_string( HFEMS_winnum, 4, 13, 56, "Tr2:" );
    nct_string( HFEMS_winnum, 2, 13, 62, "      " );
    nct_string( HFEMS_winnum, 4, 14, 56, "Tr3:" );
    nct_string( HFEMS_winnum, 2, 14, 62, "      " );
    nct_string( HFEMS_winnum, 4, 24, 72, "SolSt:" );
    nct_string( HFEMS_winnum, 2, 24, 83, "   " );
    nct_string( HFEMS_winnum, 4, 25, 72, "Drift:" );
    nct_string( HFEMS_winnum, 2, 25, 79, "       " );
    nct_string( HFEMS_winnum, 4, 26, 72, "CPU:" );
    nct_string( HFEMS_winnum, 2, 26, 83, "   " );
    nct_string( HFEMS_winnum, 4, 26, 87, "%" );
    nct_string( HFEMS_winnum, 4, 27, 72, "Disk:" );
    nct_string( HFEMS_winnum, 2, 27, 81, "     " );
    nct_string( HFEMS_winnum, 4, 27, 87, "%" );
    nct_string( HFEMS_winnum, 2, 28, 79, "         " );
    nct_string( HFEMS_winnum, 4, 29, 72, "MFCtr:" );
    nct_string( HFEMS_winnum, 2, 29, 79, "     " );
    nct_hrule( HFEMS_winnum, 1, 0, 12, nct_HFEMS_r38 );
    nct_hrule( HFEMS_winnum, 1, 0, 1, nct_HFEMS_r37 );
    nct_hrule( HFEMS_winnum, 1, 11, 83, nct_HFEMS_r36 );
    nct_hrule( HFEMS_winnum, 1, 11, 72, nct_HFEMS_r35 );
    nct_hrule( HFEMS_winnum, 1, 9, 12, nct_HFEMS_r34 );
    nct_hrule( HFEMS_winnum, 1, 9, 1, nct_HFEMS_r33 );
    nct_hrule( HFEMS_winnum, 1, 15, 13, nct_HFEMS_r32 );
    nct_hrule( HFEMS_winnum, 1, 15, 1, nct_HFEMS_r31 );
    nct_hrule( HFEMS_winnum, 1, 16, 83, nct_HFEMS_r30 );
    nct_hrule( HFEMS_winnum, 1, 16, 72, nct_HFEMS_r29 );
    nct_hrule( HFEMS_winnum, 1, 24, 57, nct_HFEMS_r28 );
    nct_hrule( HFEMS_winnum, 1, 24, 37, nct_HFEMS_r27 );
    nct_hrule( HFEMS_winnum, 1, 17, 47, nct_HFEMS_r26 );
    nct_hrule( HFEMS_winnum, 1, 17, 37, nct_HFEMS_r25 );
    nct_hrule( HFEMS_winnum, 1, 17, 65, nct_HFEMS_r24 );
    nct_hrule( HFEMS_winnum, 1, 17, 53, nct_HFEMS_r23 );
    nct_hrule( HFEMS_winnum, 1, 19, 14, nct_HFEMS_r22 );
    nct_hrule( HFEMS_winnum, 1, 19, 1, nct_HFEMS_r21 );
    nct_hrule( HFEMS_winnum, 1, 0, 32, nct_HFEMS_r20 );
    nct_hrule( HFEMS_winnum, 1, 0, 19, nct_HFEMS_r19 );
    nct_hrule( HFEMS_winnum, 1, 9, 30, nct_HFEMS_r18 );
    nct_hrule( HFEMS_winnum, 1, 9, 19, nct_HFEMS_r17 );
    nct_hrule( HFEMS_winnum, 1, 0, 81, nct_HFEMS_r16 );
    nct_hrule( HFEMS_winnum, 1, 0, 72, nct_HFEMS_r15 );
    nct_hrule( HFEMS_winnum, 1, 12, 49, nct_HFEMS_r14 );
    nct_hrule( HFEMS_winnum, 1, 12, 37, nct_HFEMS_r13 );
    nct_hrule( HFEMS_winnum, 1, 0, 47, nct_HFEMS_r12 );
    nct_hrule( HFEMS_winnum, 1, 0, 37, nct_HFEMS_r11 );
    nct_hrule( HFEMS_winnum, 1, 0, 65, nct_HFEMS_r10 );
    nct_hrule( HFEMS_winnum, 1, 0, 56, nct_HFEMS_r9 );
    nct_vrule( HFEMS_winnum, 1, 0, 55, nct_HFEMS_r8 );
    nct_vrule( HFEMS_winnum, 1, 17, 52, nct_HFEMS_r7 );
    nct_hrule( HFEMS_winnum, 1, 19, 72, nct_HFEMS_r6 );
    nct_hrule( HFEMS_winnum, 1, 30, 0, nct_HFEMS_r5 );
    nct_vrule( HFEMS_winnum, 1, 0, 88, nct_HFEMS_r4 );
    nct_vrule( HFEMS_winnum, 1, 0, 71, nct_HFEMS_r3 );
    nct_vrule( HFEMS_winnum, 1, 0, 36, nct_HFEMS_r2 );
    nct_vrule( HFEMS_winnum, 1, 0, 18, nct_HFEMS_r1 );
    nct_vrule( HFEMS_winnum, 1, 0, 0, nct_HFEMS_r0 );
  }

  static void HFEMS_init(void) {
    HFEMS_winnum = nct_init("HFEMS",32,90);
    HFEMS_redraw();
  }

/* Skeleton console_functions section */
#ifdef TABLELIB_H
  #define phdisplay(x,y) tbl_dispfield(x,y)
#endif

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
/* Text array for DStat -> DStat */
static char _CVT_7[256][9] = {
  "00000000", "00000001", "00000010", "00000011", "00000100",
  "00000101", "00000110", "00000111", "00001000", "00001001",
  "00001010", "00001011", "00001100", "00001101", "00001110",
  "00001111", "00010000", "00010001", "00010010", "00010011",
  "00010100", "00010101", "00010110", "00010111", "00011000",
  "00011001", "00011010", "00011011", "00011100", "00011101",
  "00011110", "00011111", "00100000", "00100001", "00100010",
  "00100011", "00100100", "00100101", "00100110", "00100111",
  "00101000", "00101001", "00101010", "00101011", "00101100",
  "00101101", "00101110", "00101111", "00110000", "00110001",
  "00110010", "00110011", "00110100", "00110101", "00110110",
  "00110111", "00111000", "00111001", "00111010", "00111011",
  "00111100", "00111101", "00111110", "00111111", "01000000",
  "01000001", "01000010", "01000011", "01000100", "01000101",
  "01000110", "01000111", "01001000", "01001001", "01001010",
  "01001011", "01001100", "01001101", "01001110", "01001111",
  "01010000", "01010001", "01010010", "01010011", "01010100",
  "01010101", "01010110", "01010111", "01011000", "01011001",
  "01011010", "01011011", "01011100", "01011101", "01011110",
  "01011111", "01100000", "01100001", "01100010", "01100011",
  "01100100", "01100101", "01100110", "01100111", "01101000",
  "01101001", "01101010", "01101011", "01101100", "01101101",
  "01101110", "01101111", "01110000", "01110001", "01110010",
  "01110011", "01110100", "01110101", "01110110", "01110111",
  "01111000", "01111001", "01111010", "01111011", "01111100",
  "01111101", "01111110", "01111111", "10000000", "10000001",
  "10000010", "10000011", "10000100", "10000101", "10000110",
  "10000111", "10001000", "10001001", "10001010", "10001011",
  "10001100", "10001101", "10001110", "10001111", "10010000",
  "10010001", "10010010", "10010011", "10010100", "10010101",
  "10010110", "10010111", "10011000", "10011001", "10011010",
  "10011011", "10011100", "10011101", "10011110", "10011111",
  "10100000", "10100001", "10100010", "10100011", "10100100",
  "10100101", "10100110", "10100111", "10101000", "10101001",
  "10101010", "10101011", "10101100", "10101101", "10101110",
  "10101111", "10110000", "10110001", "10110010", "10110011",
  "10110100", "10110101", "10110110", "10110111", "10111000",
  "10111001", "10111010", "10111011", "10111100", "10111101",
  "10111110", "10111111", "11000000", "11000001", "11000010",
  "11000011", "11000100", "11000101", "11000110", "11000111",
  "11001000", "11001001", "11001010", "11001011", "11001100",
  "11001101", "11001110", "11001111", "11010000", "11010001",
  "11010010", "11010011", "11010100", "11010101", "11010110",
  "11010111", "11011000", "11011001", "11011010", "11011011",
  "11011100", "11011101", "11011110", "11011111", "11100000",
  "11100001", "11100010", "11100011", "11100100", "11100101",
  "11100110", "11100111", "11101000", "11101001", "11101010",
  "11101011", "11101100", "11101101", "11101110", "11101111",
  "11110000", "11110001", "11110010", "11110011", "11110100",
  "11110101", "11110110", "11110111", "11111000", "11111001",
  "11111010", "11111011", "11111100", "11111101", "11111110",
  "11111111"
};
const char *US_4_160_u_0( unsigned short int x) {
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
/* _CVT_8() int tcvt DASPt -> DASPt */
const char *_CVT_8(DASPt x) {
  if ( x > 9999 )
	return "****";
  return US_4_160_u_0( x );
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
static unsigned short int _CVT_9( AD12_2_5_RH x) {
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
static unsigned short int _CVT_10( AD12_2_5x_25 x) {
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
static unsigned short int _CVT_11( AD12_2_5x2 x) {
  unsigned short int ov;

  ov = (x*(625L)+4096)/(8192);
  return ov;
}

/* int icvt for AD12_2_5 -> VOLTS */
static unsigned short int _CVT_12( AD12_2_5 x) {
  unsigned short int ov;

  ov = (x*(625L)+8192)/(16384);
  return ov;
}

/* int icvt for AD12_Biplrx2 -> VOLTS */
static long int _CVT_13( AD12_Biplrx2 x) {
  long int ov;

  ov = (x*(3125L)+102401024)/(2048)-50000;
  return ov;
}
const char *SL_6_4_f_c( long int x) {
  static char obuf[7];
  int neg;
  int iov;

  if (x < -9999 || x > 99999) return("******");
  if (x < 0) { neg = 1; x = -x; }
  else neg = 0;
  obuf[6] = '\0';
  obuf[5] = (x % 10) + '0';
  iov = x/10;
  obuf[4] = (iov % 10) + '0';
  iov /= 10;
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  obuf[2] = (iov % 10) + '0';
  iov /= 10;
  obuf[1] = '.';
  if (neg) obuf[0] = '-'; else
  obuf[0] = (iov % 10) + '0';
  return(obuf);
}
/* _CVT_14() int tcvt AD12_Biplrx2 -> VOLTS */
const char *_CVT_14(AD12_Biplrx2 x) {
  long int iv;

  iv = _CVT_13( x );
  if ( iv < -9999 )
	return "******";
  return SL_6_4_f_c( iv );
}

/* int icvt for AD12_Biplr -> VOLTS */
static long int _CVT_15( AD12_Biplr x) {
  long int ov;

  ov = (x*(3125L)+102400512)/(1024)-100000;
  return ov;
}
const char *SL_7_4_f_c( long int x) {
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
  obuf[3] = (iov % 10) + '0';
  iov /= 10;
  obuf[2] = '.';
  obuf[1] = (iov % 10) + '0';
  iov /= 10;
  if (iov == 0) {
    if (neg) { obuf[0] = '-'; goto nospace; }
    else goto space0;
  }
  obuf[0] = (iov % 10) + '0';
  goto nospace;
  space0: obuf[0] = ' ';
  nospace:
  return(obuf);
}
/* _CVT_16() int tcvt AD12_Biplr -> VOLTS */
const char *_CVT_16(AD12_Biplr x) {
  long int iv;

  iv = _CVT_15( x );
  if ( iv < -99999 )
	return "*******";
  return SL_7_4_f_c( iv );
}
/* Text array for SCHAR -> SCHART */
static char _CVT_17[256][5] = {
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
static char _CVT_18[256][4] = {
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
  HFEMS_init();
  
}

static void nullfunc(void);
static void BF1_0(void) {
  nct_string( HFEMS_winnum, 2, 1, 9,_CVT_6(home->U0.ueddy1) );
  nct_string( HFEMS_winnum, 2, 2, 9,_CVT_6(home->U0.veddy1) );
  nct_string( HFEMS_winnum, 2, 3, 9,_CVT_6(home->U0.weddy1) );
  nct_string( HFEMS_winnum, 2, 4, 9,_CVT_6(home->U0.teddy1) );
  nct_string( HFEMS_winnum, 2, 5, 9,_CVT_6(home->U0.ueddy2) );
  nct_string( HFEMS_winnum, 2, 6, 9,_CVT_6(home->U0.veddy2) );
  nct_string( HFEMS_winnum, 2, 7, 9,_CVT_6(home->U0.weddy2) );
  nct_string( HFEMS_winnum, 2, 8, 9,_CVT_6(home->U0.teddy2) );
  nct_string( HFEMS_winnum, 2, 12, 79,_CVT_17[home->U0.sdev_stale1] );
  nct_string( HFEMS_winnum, 2, 13, 80,_CVT_18[home->U0.sdrv_stale1] );
  nct_string( HFEMS_winnum, 2, 14, 79,_CVT_17[home->U0.sdev_stale2] );
  nct_string( HFEMS_winnum, 2, 15, 80,_CVT_18[home->U0.sdrv_stale2] );
  nct_string( HFEMS_winnum, 2, 17, 77,US_5_11_u_0(home->U0.NOx) );
  nct_string( HFEMS_winnum, 2, 18, 77,US_5_11_u_0(home->U0.NOy) );
  nct_string( HFEMS_winnum, 2, 29, 79,US_5_11_u_0(MFCtr) );
}

static void BF2_0(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 10, 9,_CVT_14(home->U0.vCO2e1) );
  nct_string( HFEMS_winnum, 2, 11, 9,_CVT_14(home->U0.vH2Oe1) );
  nct_string( HFEMS_winnum, 2, 12, 9,_CVT_14(home->U0.vCO2e2) );
  nct_string( HFEMS_winnum, 2, 13, 9,_CVT_14(home->U0.vH2Oe2) );
  nct_string( HFEMS_winnum, 2, 14, 9,US_6_3_f_c(_CVT_12(home->U0.vO3ed)) );
}

static void BF8_0(void) {
  BF2_0();
  {
    flttime = itime(); {
    nct_string( HFEMS_winnum, 2, 28, 79,timetext(flttime) );
  }
  }
  nct_string( HFEMS_winnum, 2, 25, 79,_CVT_4(home->U28.TDrift) );
  nct_string( HFEMS_winnum, 2, 26, 83,_CVT_2[home->U26.CPU_Pct] );
  nct_string( HFEMS_winnum, 2, 27, 81,_CVT_1(home->U28.Disk) );
}

static void BF16_0(void) {
  BF8_0();
  nct_string( HFEMS_winnum, 2, 25, 43,_CVT_7[home->U26.DSt0] );
}

static void BF16_1(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 19, 65,_CVT_8(home->U24.fcNO_NOx_SP) );
  nct_string( HFEMS_winnum, 2, 20, 65,_CVT_8(home->U14.fcNO2_NOx_SP) );
  nct_string( HFEMS_winnum, 2, 21, 65,_CVT_8(home->U26.fcNO_NOy_SP) );
  nct_string( HFEMS_winnum, 2, 20, 30,_CVT_14(home->U12.fcNO_NOx) );
  nct_string( HFEMS_winnum, 2, 21, 30,_CVT_14(home->U12.fcNO2_NOx) );
  nct_string( HFEMS_winnum, 2, 22, 30,_CVT_14(home->U16.fcNO_NOy) );
  nct_string( HFEMS_winnum, 2, 23, 30,_CVT_14(home->U10.fcEff_NOy) );
  nct_string( HFEMS_winnum, 2, 24, 30,_CVT_14(home->U16.fcZer_NOy) );
}

static void BF16_2(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 18, 65,_CVT_8(home->U24.fc_CO2e_SP) );
  nct_string( HFEMS_winnum, 2, 15, 30,_CVT_14(home->U22.FlCO) );
  nct_string( HFEMS_winnum, 2, 25, 30,_CVT_14(home->U18.fc_CO2e) );
}

static void BF16_3(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 20, 46,_CVT_8(home->U20.FlCO2p_SP) );
  nct_string( HFEMS_winnum, 2, 21, 46,_CVT_8(home->U16.FlCO2e3_SP) );
  nct_string( HFEMS_winnum, 2, 23, 46,_CVT_8(home->U26.FlCO_SP) );
  nct_string( HFEMS_winnum, 2, 11, 30,_CVT_14(home->U10.FlCO2p) );
  nct_string( HFEMS_winnum, 2, 12, 30,_CVT_14(home->U14.FlCO2e1) );
  nct_string( HFEMS_winnum, 2, 13, 30,_CVT_14(home->U12.FlCO2e2) );
  nct_string( HFEMS_winnum, 2, 14, 30,US_6_3_f_c(_CVT_10(home->U14.FlCO2e3)) );
  nct_string( HFEMS_winnum, 2, 16, 30,_CVT_14(home->U14.FlNOx) );
}

static void BF16_4(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 17, 30,_CVT_14(home->U16.FlO3_NOx) );
  nct_string( HFEMS_winnum, 2, 18, 30,_CVT_14(home->U10.FlNOy) );
  nct_string( HFEMS_winnum, 2, 19, 30,_CVT_14(home->U18.FlO3_NOy) );
}

static void BF16_5(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 18, 46,_CVT_8(home->U12.Pman_SP) );
  nct_string( HFEMS_winnum, 2, 23, 11,US_6_3_f_c(_CVT_12(home->U12.PPFD_mid)) );
  nct_string( HFEMS_winnum, 2, 24, 11,US_6_3_f_c(_CVT_12(home->U14.PPFD_ref)) );
  nct_string( HFEMS_winnum, 2, 25, 11,US_6_3_f_c(_CVT_12(home->U8.PPFD_cal)) );
  nct_string( HFEMS_winnum, 2, 26, 11,US_6_3_f_c(_CVT_12(home->U12.PPFD_gnd)) );
  nct_string( HFEMS_winnum, 2, 28, 11,US_6_3_f_c(_CVT_12(home->U16.PPFD_d)) );
  nct_string( HFEMS_winnum, 2, 1, 28,US_6_3_f_c(_CVT_10(home->U10.Pamb)) );
  nct_string( HFEMS_winnum, 2, 2, 28,US_6_3_f_c(_CVT_10(home->U10.Pman)) );
  nct_string( HFEMS_winnum, 2, 10, 30,_CVT_14(home->U8.FlowT) );
}

static void BF16_6(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 22, 11,US_6_3_f_c(_CVT_12(home->U10.PPFD_top)) );
  nct_string( HFEMS_winnum, 2, 27, 11,US_6_3_f_c(_CVT_12(home->U14.PPFD_t)) );
  nct_string( HFEMS_winnum, 2, 4, 28,US_6_3_f_c(_CVT_10(home->U20.PrCO2e1)) );
  nct_string( HFEMS_winnum, 2, 6, 28,US_6_3_f_c(_CVT_10(home->U20.PrCO)) );
}

static void BF16_7(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 19, 46,_CVT_8(home->U16.PrCO2p_SP) );
  nct_string( HFEMS_winnum, 2, 22, 46,_CVT_8(home->U22.PrCO_SP) );
  nct_string( HFEMS_winnum, 2, 3, 28,US_6_3_f_c(_CVT_10(home->U10.PrCO2p)) );
  nct_string( HFEMS_winnum, 2, 5, 28,US_6_3_f_c(_CVT_10(home->U14.PrCO2e2)) );
  nct_string( HFEMS_winnum, 2, 7, 28,US_6_3_f_c(_CVT_10(home->U14.PrNOx)) );
  nct_string( HFEMS_winnum, 2, 8, 28,US_6_3_f_c(_CVT_10(home->U18.PrNOy)) );
  nct_string( HFEMS_winnum, 2, 1, 78,US_6_1_f_c(_CVT_9(home->U10.RH1)) );
}

static void BF16_8(void) {
  BF8_0();
  nct_string( HFEMS_winnum, 2, 26, 43,_CVT_7[home->U28.DSt1] );
}

static void BF16_9(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 2, 78,US_6_1_f_c(_CVT_9(home->U8.RH2)) );
  nct_string( HFEMS_winnum, 2, 3, 78,US_6_1_f_c(_CVT_9(home->U8.RH3)) );
  nct_string( HFEMS_winnum, 2, 4, 78,US_6_1_f_c(_CVT_9(home->U8.RH4)) );
  nct_string( HFEMS_winnum, 2, 5, 78,US_6_1_f_c(_CVT_9(home->U6.RH5)) );
  nct_string( HFEMS_winnum, 2, 6, 78,US_6_1_f_c(_CVT_9(home->U6.RH6)) );
  nct_string( HFEMS_winnum, 2, 7, 78,US_6_1_f_c(_CVT_9(home->U6.RH7)) );
  nct_string( HFEMS_winnum, 2, 8, 78,US_6_1_f_c(_CVT_9(home->U10.RH8)) );
  nct_string( HFEMS_winnum, 2, 9, 78,US_6_1_f_c(_CVT_9(home->U12.RH9)) );
  nct_string( HFEMS_winnum, 2, 10, 78,US_6_1_f_c(_CVT_9(home->U6.RH10)) );
}

static void BF16_10(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 20, 11,_CVT_16(home->U8.Rnet) );
  nct_string( HFEMS_winnum, 2, 21, 11,_CVT_16(home->U8.Rnet_cal) );
  nct_string( HFEMS_winnum, 2, 1, 62,US_6_3_f_c(_CVT_12(home->U2.Ta1)) );
  nct_string( HFEMS_winnum, 2, 10, 62,US_6_3_f_c(_CVT_12(home->U0.Ta10)) );
}

static void BF16_11(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 2, 62,US_6_3_f_c(_CVT_12(home->U2.Ta2)) );
  nct_string( HFEMS_winnum, 2, 3, 62,US_6_3_f_c(_CVT_12(home->U4.Ta3)) );
  nct_string( HFEMS_winnum, 2, 4, 62,US_6_3_f_c(_CVT_12(home->U4.Ta4)) );
  nct_string( HFEMS_winnum, 2, 5, 62,US_6_3_f_c(_CVT_12(home->U4.Ta5)) );
  nct_string( HFEMS_winnum, 2, 6, 62,US_6_3_f_c(_CVT_12(home->U2.Ta6)) );
  nct_string( HFEMS_winnum, 2, 7, 62,US_6_3_f_c(_CVT_12(home->U0.Ta7)) );
  nct_string( HFEMS_winnum, 2, 8, 62,US_6_3_f_c(_CVT_12(home->U0.Ta8)) );
  nct_string( HFEMS_winnum, 2, 9, 62,US_6_3_f_c(_CVT_12(home->U4.Ta9)) );
  nct_string( HFEMS_winnum, 2, 11, 62,US_6_3_f_c(_CVT_12(home->U2.Tcal)) );
}

static void BF16_12(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 14, 45,US_6_3_f_c(_CVT_11(home->U12.TCO2e1)) );
  nct_string( HFEMS_winnum, 2, 15, 45,US_6_3_f_c(_CVT_11(home->U20.TCO2e2)) );
  nct_string( HFEMS_winnum, 2, 16, 45,US_6_3_f_c(_CVT_11(home->U22.TCO2p)) );
  nct_string( HFEMS_winnum, 2, 12, 62,US_6_3_f_c(_CVT_12(home->U4.Tr1)) );
}

static void BF16_13(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 1, 45,US_6_3_f_c(_CVT_12(home->U6.Ts1)) );
  nct_string( HFEMS_winnum, 2, 2, 45,US_6_3_f_c(_CVT_12(home->U2.Ts2)) );
  nct_string( HFEMS_winnum, 2, 3, 45,US_6_3_f_c(_CVT_12(home->U2.TS3)) );
  nct_string( HFEMS_winnum, 2, 4, 45,US_6_3_f_c(_CVT_12(home->U6.Ts4)) );
  nct_string( HFEMS_winnum, 2, 5, 45,US_6_3_f_c(_CVT_12(home->U6.Ts5)) );
  nct_string( HFEMS_winnum, 2, 10, 45,US_6_3_f_c(_CVT_12(home->U6.Ts10)) );
  nct_string( HFEMS_winnum, 2, 11, 45,US_6_3_f_c(_CVT_12(home->U4.TS11)) );
  nct_string( HFEMS_winnum, 2, 13, 62,US_6_3_f_c(_CVT_12(home->U4.Tr2)) );
  nct_string( HFEMS_winnum, 2, 14, 62,US_6_3_f_c(_CVT_12(home->U6.Tr3)) );
}

static void BF16_14(void) {
  BF2_0();
  nct_string( HFEMS_winnum, 2, 6, 45,US_6_3_f_c(_CVT_12(home->U4.Ts6)) );
  nct_string( HFEMS_winnum, 2, 7, 45,US_6_3_f_c(_CVT_12(home->U4.Ts7)) );
  nct_string( HFEMS_winnum, 2, 8, 45,US_6_3_f_c(_CVT_12(home->U8.TS8)) );
  nct_string( HFEMS_winnum, 2, 9, 45,US_6_3_f_c(_CVT_12(home->U8.TS9)) );
}

static void BF16_15(void) {
  BF1_0();
  nct_string( HFEMS_winnum, 2, 16, 10,_CVT_16(home->U2.vCO2prf) );
  nct_string( HFEMS_winnum, 2, 17, 10,_CVT_16(home->U2.vO3prf) );
  nct_string( HFEMS_winnum, 2, 18, 10,_CVT_16(home->U2.vCO) );
  nct_string( HFEMS_winnum, 2, 27, 43,_CVT_7[home->U18.DSt4] );
  nct_string( HFEMS_winnum, 2, 28, 43,_CVT_7[home->U18.DSt5] );
  nct_string( HFEMS_winnum, 2, 29, 43,_CVT_7[home->U22.DSt6] );
  nct_string( HFEMS_winnum, 2, 13, 45,US_6_3_f_c(_CVT_12(home->U12.T_MB)) );
  nct_string( HFEMS_winnum, 2, 24, 83,_CVT_5[home->U0.SolSt] );
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
