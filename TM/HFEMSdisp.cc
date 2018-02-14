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
/* phtable output */
#include "tablelib.h"
PtWidget_t *HFEMS_tbl_fld[115];
void HFEMS_init( void ) {
  PtWidget_t *w;
  w = tbl_window( "HFEMS", 753, 580 );
  tbl_label( w, "Sonic", 61, 0 ); /* Attr 4 */
  tbl_label( w, "ueddy1:", 9, 19 ); /* Attr 4 */
  HFEMS_tbl_fld[0] = tbl_field( w, "X", 82, 19, 48, 15 );
  tbl_label( w, "veddy1:", 9, 38 ); /* Attr 4 */
  HFEMS_tbl_fld[1] = tbl_field( w, "X", 82, 38, 48, 15 );
  tbl_label( w, "weddy1:", 9, 57 ); /* Attr 4 */
  HFEMS_tbl_fld[2] = tbl_field( w, "X", 82, 57, 48, 15 );
  tbl_label( w, "Teddy1:", 9, 76 ); /* Attr 4 */
  HFEMS_tbl_fld[3] = tbl_field( w, "X", 82, 76, 48, 15 );
  tbl_label( w, "ueddy2:", 9, 95 ); /* Attr 4 */
  HFEMS_tbl_fld[4] = tbl_field( w, "X", 82, 95, 48, 15 );
  tbl_label( w, "veddy2:", 9, 114 ); /* Attr 4 */
  HFEMS_tbl_fld[5] = tbl_field( w, "X", 82, 114, 48, 15 );
  tbl_label( w, "weddy2:", 9, 133 ); /* Attr 4 */
  HFEMS_tbl_fld[6] = tbl_field( w, "X", 82, 133, 48, 15 );
  tbl_label( w, "Teddy2:", 9, 152 ); /* Attr 4 */
  HFEMS_tbl_fld[7] = tbl_field( w, "X", 82, 152, 48, 15 );
  tbl_label( w, "Sonic", 658, 209 ); /* Attr 4 */
  tbl_label( w, "Sdev1:", 613, 228 ); /* Attr 4 */
  HFEMS_tbl_fld[103] = tbl_field( w, "X", 673, 228, 32, 15 );
  tbl_label( w, "Sdrv1:", 613, 247 ); /* Attr 4 */
  HFEMS_tbl_fld[104] = tbl_field( w, "X", 681, 247, 24, 15 );
  tbl_label( w, "Sdev2:", 613, 266 ); /* Attr 4 */
  HFEMS_tbl_fld[105] = tbl_field( w, "X", 673, 266, 32, 15 );
  tbl_label( w, "Sdrv2:", 613, 285 ); /* Attr 4 */
  HFEMS_tbl_fld[106] = tbl_field( w, "X", 681, 285, 24, 15 );
  tbl_label( w, "Eddy", 63, 171 ); /* Attr 4 */
  tbl_label( w, "vCO2e1:", 9, 190 ); /* Attr 4 */
  HFEMS_tbl_fld[8] = tbl_field( w, "X", 82, 190, 48, 15 );
  tbl_label( w, "vH2Oe1:", 9, 209 ); /* Attr 4 */
  HFEMS_tbl_fld[9] = tbl_field( w, "X", 82, 209, 48, 15 );
  tbl_label( w, "vCO2e2:", 9, 228 ); /* Attr 4 */
  HFEMS_tbl_fld[10] = tbl_field( w, "X", 82, 228, 48, 15 );
  tbl_label( w, "vH2Oe2:", 9, 247 ); /* Attr 4 */
  HFEMS_tbl_fld[11] = tbl_field( w, "X", 82, 247, 48, 15 );
  tbl_label( w, "vO3ed:", 9, 266 ); /* Attr 4 */
  HFEMS_tbl_fld[12] = tbl_field( w, "X", 82, 266, 48, 15 );
  tbl_label( w, "Profile", 58, 285 ); /* Attr 4 */
  tbl_label( w, "vCO2prf:", 9, 304 ); /* Attr 4 */
  HFEMS_tbl_fld[13] = tbl_field( w, "X", 83, 304, 48, 15 );
  tbl_label( w, "vO3prf:", 9, 323 ); /* Attr 4 */
  HFEMS_tbl_fld[14] = tbl_field( w, "X", 83, 323, 48, 15 );
  tbl_label( w, "vCO:", 9, 342 ); /* Attr 4 */
  HFEMS_tbl_fld[15] = tbl_field( w, "X", 83, 342, 48, 15 );
  tbl_label( w, "Counts", 653, 304 ); /* Attr 4 */
  tbl_label( w, "NOx:", 613, 323 ); /* Attr 4 */
  HFEMS_tbl_fld[107] = tbl_field( w, "X", 660, 323, 40, 15 );
  tbl_label( w, "NOy:", 613, 342 ); /* Attr 4 */
  HFEMS_tbl_fld[108] = tbl_field( w, "X", 660, 342, 40, 15 );
  tbl_label( w, "Status", 439, 456 ); /* Attr 4 */
  tbl_label( w, "DSt0:", 318, 475 ); /* Attr 4 */
  HFEMS_tbl_fld[88] = tbl_field( w, "X", 367, 475, 64, 15 );
  tbl_label( w, "DSt1:", 318, 494 ); /* Attr 4 */
  HFEMS_tbl_fld[89] = tbl_field( w, "X", 367, 494, 64, 15 );
  tbl_label( w, "DSt4:", 318, 513 ); /* Attr 4 */
  HFEMS_tbl_fld[90] = tbl_field( w, "X", 367, 513, 64, 15 );
  tbl_label( w, "DSt5:", 318, 532 ); /* Attr 4 */
  HFEMS_tbl_fld[91] = tbl_field( w, "X", 367, 532, 64, 15 );
  tbl_label( w, "DSt6:", 318, 551 ); /* Attr 4 */
  HFEMS_tbl_fld[92] = tbl_field( w, "X", 367, 551, 64, 15 );
  tbl_label( w, "PrFl", 366, 323 ); /* Attr 4 */
  tbl_label( w, "Pman:", 318, 342 ); /* Attr 4 */
  HFEMS_tbl_fld[78] = tbl_field( w, "X", 393, 342, 48, 15 );
  tbl_label( w, "PrCO2p:", 318, 361 ); /* Attr 4 */
  HFEMS_tbl_fld[79] = tbl_field( w, "X", 393, 361, 48, 15 );
  tbl_label( w, "FlCO2p:", 318, 380 ); /* Attr 4 */
  HFEMS_tbl_fld[80] = tbl_field( w, "X", 393, 380, 48, 15 );
  tbl_label( w, "FlCO2e3:", 318, 399 ); /* Attr 4 */
  HFEMS_tbl_fld[81] = tbl_field( w, "X", 393, 399, 48, 15 );
  tbl_label( w, "PrCO:", 318, 418 ); /* Attr 4 */
  HFEMS_tbl_fld[82] = tbl_field( w, "X", 393, 418, 48, 15 );
  tbl_label( w, "FlCO:", 318, 437 ); /* Attr 4 */
  HFEMS_tbl_fld[83] = tbl_field( w, "X", 393, 437, 48, 15 );
  tbl_label( w, "cal_fc", 506, 323 ); /* Attr 4 */
  tbl_label( w, "fc_CO2e:", 450, 342 ); /* Attr 4 */
  HFEMS_tbl_fld[84] = tbl_field( w, "X", 556, 342, 48, 15 );
  tbl_label( w, "fc_NO_NOx:", 450, 361 ); /* Attr 4 */
  HFEMS_tbl_fld[85] = tbl_field( w, "X", 556, 361, 48, 15 );
  tbl_label( w, "fc_NO2_NOx:", 450, 380 ); /* Attr 4 */
  HFEMS_tbl_fld[86] = tbl_field( w, "X", 556, 380, 48, 15 );
  tbl_label( w, "fc_NO_NOy:", 450, 399 ); /* Attr 4 */
  HFEMS_tbl_fld[87] = tbl_field( w, "X", 556, 399, 48, 15 );
  tbl_label( w, "Radiation", 47, 361 ); /* Attr 4 */
  tbl_label( w, "Rnet:", 9, 380 ); /* Attr 4 */
  HFEMS_tbl_fld[16] = tbl_field( w, "X", 97, 380, 56, 15 );
  tbl_label( w, "Rnet_cal:", 9, 399 ); /* Attr 4 */
  HFEMS_tbl_fld[17] = tbl_field( w, "X", 97, 399, 56, 15 );
  tbl_label( w, "PPFD_top:", 9, 418 ); /* Attr 4 */
  HFEMS_tbl_fld[18] = tbl_field( w, "X", 97, 418, 56, 15 );
  tbl_label( w, "PPFD_mid:", 9, 437 ); /* Attr 4 */
  HFEMS_tbl_fld[19] = tbl_field( w, "X", 97, 437, 56, 15 );
  tbl_label( w, "PPFD_ref:", 9, 456 ); /* Attr 4 */
  HFEMS_tbl_fld[20] = tbl_field( w, "X", 97, 456, 56, 15 );
  tbl_label( w, "PPFD_cal:", 9, 475 ); /* Attr 4 */
  HFEMS_tbl_fld[21] = tbl_field( w, "X", 97, 475, 56, 15 );
  tbl_label( w, "PPFD_gnd:", 9, 494 ); /* Attr 4 */
  HFEMS_tbl_fld[22] = tbl_field( w, "X", 97, 494, 56, 15 );
  tbl_label( w, "PPFD_t:", 9, 513 ); /* Attr 4 */
  HFEMS_tbl_fld[23] = tbl_field( w, "X", 97, 513, 56, 15 );
  tbl_label( w, "PPFD_d:", 9, 532 ); /* Attr 4 */
  HFEMS_tbl_fld[24] = tbl_field( w, "X", 97, 532, 56, 15 );
  tbl_label( w, "Pressure", 203, 0 ); /* Attr 4 */
  tbl_label( w, "Pamb:", 162, 19 ); /* Attr 4 */
  HFEMS_tbl_fld[25] = tbl_field( w, "X", 241, 19, 48, 15 );
  tbl_label( w, "Pman:", 162, 38 ); /* Attr 4 */
  HFEMS_tbl_fld[26] = tbl_field( w, "X", 241, 38, 48, 15 );
  tbl_label( w, "PrCO2p:", 162, 57 ); /* Attr 4 */
  HFEMS_tbl_fld[27] = tbl_field( w, "X", 241, 57, 48, 15 );
  tbl_label( w, "PrCO2e1:", 162, 76 ); /* Attr 4 */
  HFEMS_tbl_fld[28] = tbl_field( w, "X", 241, 76, 48, 15 );
  tbl_label( w, "PrCO2e2:", 162, 95 ); /* Attr 4 */
  HFEMS_tbl_fld[29] = tbl_field( w, "X", 241, 95, 48, 15 );
  tbl_label( w, "PrCO:", 162, 114 ); /* Attr 4 */
  HFEMS_tbl_fld[30] = tbl_field( w, "X", 241, 114, 48, 15 );
  tbl_label( w, "PrNOx:", 162, 133 ); /* Attr 4 */
  HFEMS_tbl_fld[31] = tbl_field( w, "X", 241, 133, 48, 15 );
  tbl_label( w, "PrNOy:", 162, 152 ); /* Attr 4 */
  HFEMS_tbl_fld[32] = tbl_field( w, "X", 241, 152, 48, 15 );
  tbl_label( w, "Flow", 219, 171 ); /* Attr 4 */
  tbl_label( w, "FlowT:", 162, 190 ); /* Attr 4 */
  HFEMS_tbl_fld[33] = tbl_field( w, "X", 261, 190, 48, 15 );
  tbl_label( w, "FlCO2p:", 162, 209 ); /* Attr 4 */
  HFEMS_tbl_fld[34] = tbl_field( w, "X", 261, 209, 48, 15 );
  tbl_label( w, "FlCO2e1:", 162, 228 ); /* Attr 4 */
  HFEMS_tbl_fld[35] = tbl_field( w, "X", 261, 228, 48, 15 );
  tbl_label( w, "FlCO2e2:", 162, 247 ); /* Attr 4 */
  HFEMS_tbl_fld[36] = tbl_field( w, "X", 261, 247, 48, 15 );
  tbl_label( w, "FlCO2e3:", 162, 266 ); /* Attr 4 */
  HFEMS_tbl_fld[37] = tbl_field( w, "X", 261, 266, 48, 15 );
  tbl_label( w, "FlCO:", 162, 285 ); /* Attr 4 */
  HFEMS_tbl_fld[38] = tbl_field( w, "X", 261, 285, 48, 15 );
  tbl_label( w, "FlNOx:", 162, 304 ); /* Attr 4 */
  HFEMS_tbl_fld[39] = tbl_field( w, "X", 261, 304, 48, 15 );
  tbl_label( w, "FlO3_NOx:", 162, 323 ); /* Attr 4 */
  HFEMS_tbl_fld[40] = tbl_field( w, "X", 261, 323, 48, 15 );
  tbl_label( w, "FlNOy:", 162, 342 ); /* Attr 4 */
  HFEMS_tbl_fld[41] = tbl_field( w, "X", 261, 342, 48, 15 );
  tbl_label( w, "FlO3_NOy:", 162, 361 ); /* Attr 4 */
  HFEMS_tbl_fld[42] = tbl_field( w, "X", 261, 361, 48, 15 );
  tbl_label( w, "fcNO_NOx:", 162, 380 ); /* Attr 4 */
  HFEMS_tbl_fld[43] = tbl_field( w, "X", 261, 380, 48, 15 );
  tbl_label( w, "fcNO2_NOx:", 162, 399 ); /* Attr 4 */
  HFEMS_tbl_fld[44] = tbl_field( w, "X", 261, 399, 48, 15 );
  tbl_label( w, "fcNO_NOy:", 162, 418 ); /* Attr 4 */
  HFEMS_tbl_fld[45] = tbl_field( w, "X", 261, 418, 48, 15 );
  tbl_label( w, "fcEff_NOy:", 162, 437 ); /* Attr 4 */
  HFEMS_tbl_fld[46] = tbl_field( w, "X", 261, 437, 48, 15 );
  tbl_label( w, "fcZer_NOy:", 162, 456 ); /* Attr 4 */
  HFEMS_tbl_fld[47] = tbl_field( w, "X", 261, 456, 48, 15 );
  tbl_label( w, "fc_CO2e:", 162, 475 ); /* Attr 4 */
  HFEMS_tbl_fld[48] = tbl_field( w, "X", 261, 475, 48, 15 );
  tbl_label( w, "RH", 668, 0 ); /* Attr 5 */
  tbl_label( w, "RH1:", 613, 19 ); /* Attr 4 */
  HFEMS_tbl_fld[93] = tbl_field( w, "X", 667, 19, 48, 15 );
  tbl_label( w, "RH2:", 613, 38 ); /* Attr 4 */
  HFEMS_tbl_fld[94] = tbl_field( w, "X", 667, 38, 48, 15 );
  tbl_label( w, "RH3:", 613, 57 ); /* Attr 4 */
  HFEMS_tbl_fld[95] = tbl_field( w, "X", 667, 57, 48, 15 );
  tbl_label( w, "RH4:", 613, 76 ); /* Attr 4 */
  HFEMS_tbl_fld[96] = tbl_field( w, "X", 667, 76, 48, 15 );
  tbl_label( w, "RH5:", 613, 95 ); /* Attr 4 */
  HFEMS_tbl_fld[97] = tbl_field( w, "X", 667, 95, 48, 15 );
  tbl_label( w, "RH6:", 613, 114 ); /* Attr 4 */
  HFEMS_tbl_fld[98] = tbl_field( w, "X", 667, 114, 48, 15 );
  tbl_label( w, "RH7:", 613, 133 ); /* Attr 4 */
  HFEMS_tbl_fld[99] = tbl_field( w, "X", 667, 133, 48, 15 );
  tbl_label( w, "RH8:", 613, 152 ); /* Attr 4 */
  HFEMS_tbl_fld[100] = tbl_field( w, "X", 667, 152, 48, 15 );
  tbl_label( w, "RH9:", 613, 171 ); /* Attr 4 */
  HFEMS_tbl_fld[101] = tbl_field( w, "X", 667, 171, 48, 15 );
  tbl_label( w, "RH10:", 613, 190 ); /* Attr 4 */
  HFEMS_tbl_fld[102] = tbl_field( w, "X", 667, 190, 48, 15 );
  tbl_label( w, "Ts", 385, 0 ); /* Attr 4 */
  tbl_label( w, "Ts1:", 318, 19 ); /* Attr 4 */
  HFEMS_tbl_fld[49] = tbl_field( w, "X", 389, 19, 48, 15 );
  tbl_label( w, "Ts2:", 318, 38 ); /* Attr 4 */
  HFEMS_tbl_fld[50] = tbl_field( w, "X", 389, 38, 48, 15 );
  tbl_label( w, "Ts3:", 318, 57 ); /* Attr 4 */
  HFEMS_tbl_fld[51] = tbl_field( w, "X", 389, 57, 48, 15 );
  tbl_label( w, "Ts4:", 318, 76 ); /* Attr 4 */
  HFEMS_tbl_fld[52] = tbl_field( w, "X", 389, 76, 48, 15 );
  tbl_label( w, "Ts5:", 318, 95 ); /* Attr 4 */
  HFEMS_tbl_fld[53] = tbl_field( w, "X", 389, 95, 48, 15 );
  tbl_label( w, "Ts6:", 318, 114 ); /* Attr 4 */
  HFEMS_tbl_fld[54] = tbl_field( w, "X", 389, 114, 48, 15 );
  tbl_label( w, "Ts7:", 318, 133 ); /* Attr 4 */
  HFEMS_tbl_fld[55] = tbl_field( w, "X", 389, 133, 48, 15 );
  tbl_label( w, "Ts8:", 318, 152 ); /* Attr 4 */
  HFEMS_tbl_fld[56] = tbl_field( w, "X", 389, 152, 48, 15 );
  tbl_label( w, "Ts9:", 318, 171 ); /* Attr 4 */
  HFEMS_tbl_fld[57] = tbl_field( w, "X", 389, 171, 48, 15 );
  tbl_label( w, "Ts10:", 318, 190 ); /* Attr 4 */
  HFEMS_tbl_fld[58] = tbl_field( w, "X", 389, 190, 48, 15 );
  tbl_label( w, "Ts11:", 318, 209 ); /* Attr 4 */
  HFEMS_tbl_fld[59] = tbl_field( w, "X", 389, 209, 48, 15 );
  tbl_label( w, "TCells", 371, 228 ); /* Attr 4 */
  tbl_label( w, "T_MB:", 318, 247 ); /* Attr 4 */
  HFEMS_tbl_fld[60] = tbl_field( w, "X", 389, 247, 48, 15 );
  tbl_label( w, "TCO2e1:", 318, 266 ); /* Attr 4 */
  HFEMS_tbl_fld[61] = tbl_field( w, "X", 389, 266, 48, 15 );
  tbl_label( w, "TCO2e2:", 318, 285 ); /* Attr 4 */
  HFEMS_tbl_fld[62] = tbl_field( w, "X", 389, 285, 48, 15 );
  tbl_label( w, "TCO2p:", 318, 304 ); /* Attr 4 */
  HFEMS_tbl_fld[63] = tbl_field( w, "X", 389, 304, 48, 15 );
  tbl_label( w, "Ta", 532, 0 ); /* Attr 4 */
  tbl_label( w, "Ta1:", 476, 19 ); /* Attr 4 */
  HFEMS_tbl_fld[64] = tbl_field( w, "X", 526, 19, 48, 15 );
  tbl_label( w, "Ta2:", 476, 38 ); /* Attr 4 */
  HFEMS_tbl_fld[65] = tbl_field( w, "X", 526, 38, 48, 15 );
  tbl_label( w, "Ta3:", 476, 57 ); /* Attr 4 */
  HFEMS_tbl_fld[66] = tbl_field( w, "X", 526, 57, 48, 15 );
  tbl_label( w, "Ta4:", 476, 76 ); /* Attr 4 */
  HFEMS_tbl_fld[67] = tbl_field( w, "X", 526, 76, 48, 15 );
  tbl_label( w, "Ta5:", 476, 95 ); /* Attr 4 */
  HFEMS_tbl_fld[68] = tbl_field( w, "X", 526, 95, 48, 15 );
  tbl_label( w, "Ta6:", 476, 114 ); /* Attr 4 */
  HFEMS_tbl_fld[69] = tbl_field( w, "X", 526, 114, 48, 15 );
  tbl_label( w, "Ta7:", 476, 133 ); /* Attr 4 */
  HFEMS_tbl_fld[70] = tbl_field( w, "X", 526, 133, 48, 15 );
  tbl_label( w, "Ta8:", 476, 152 ); /* Attr 4 */
  HFEMS_tbl_fld[71] = tbl_field( w, "X", 526, 152, 48, 15 );
  tbl_label( w, "Ta9:", 476, 171 ); /* Attr 4 */
  HFEMS_tbl_fld[72] = tbl_field( w, "X", 526, 171, 48, 15 );
  tbl_label( w, "Ta10:", 476, 190 ); /* Attr 4 */
  HFEMS_tbl_fld[73] = tbl_field( w, "X", 526, 190, 48, 15 );
  tbl_label( w, "Tcal:", 476, 209 ); /* Attr 4 */
  HFEMS_tbl_fld[74] = tbl_field( w, "X", 526, 209, 48, 15 );
  tbl_label( w, "Tr1:", 476, 228 ); /* Attr 4 */
  HFEMS_tbl_fld[75] = tbl_field( w, "X", 526, 228, 48, 15 );
  tbl_label( w, "Tr2:", 476, 247 ); /* Attr 4 */
  HFEMS_tbl_fld[76] = tbl_field( w, "X", 526, 247, 48, 15 );
  tbl_label( w, "Tr3:", 476, 266 ); /* Attr 4 */
  HFEMS_tbl_fld[77] = tbl_field( w, "X", 526, 266, 48, 15 );
  tbl_label( w, "SolSt:", 613, 460 ); /* Attr 4 */
  HFEMS_tbl_fld[109] = tbl_field( w, "X", 696, 460, 24, 15 );
  tbl_label( w, "Drift:", 613, 479 ); /* Attr 4 */
  HFEMS_tbl_fld[110] = tbl_field( w, "X", 664, 479, 56, 15 );
  tbl_label( w, "CPU:", 613, 498 ); /* Attr 4 */
  HFEMS_tbl_fld[111] = tbl_field( w, "X", 696, 498, 24, 15 );
  tbl_label( w, "%", 730, 498 ); /* Attr 4 */
  tbl_label( w, "Disk:", 613, 517 ); /* Attr 4 */
  HFEMS_tbl_fld[112] = tbl_field( w, "X", 680, 517, 40, 15 );
  tbl_label( w, "%", 730, 517 ); /* Attr 4 */
  HFEMS_tbl_fld[113] = tbl_field( w, "X", 671, 536, 72, 15 );
  tbl_label( w, "MFCtr:", 613, 551 ); /* Attr 4 */
  HFEMS_tbl_fld[114] = tbl_field( w, "X", 670, 551, 40, 15 );
  tbl_horiz_sep( w, 4, 574, 744, 0 );
  tbl_vert_sep( w, 747, 9, 565, 0 );
  tbl_vert_sep( w, 608, 9, 565, 0 );
  tbl_vert_sep( w, 313, 9, 565, 0 );
  tbl_vert_sep( w, 157, 9, 565, 0 );
  tbl_vert_sep( w, 4, 9, 565, 0 );
  tbl_horiz_sep( w, 101, 9, 56, 0 );
  tbl_horiz_sep( w, 5, 9, 56, 0 );
  tbl_horiz_sep( w, 698, 218, 49, 0 );
  tbl_horiz_sep( w, 609, 218, 49, 0 );
  tbl_horiz_sep( w, 99, 180, 58, 0 );
  tbl_horiz_sep( w, 5, 180, 58, 0 );
  tbl_horiz_sep( w, 105, 294, 52, 0 );
  tbl_horiz_sep( w, 5, 294, 53, 0 );
  tbl_horiz_sep( w, 703, 313, 44, 0 );
  tbl_horiz_sep( w, 609, 313, 44, 0 );
  tbl_horiz_sep( w, 484, 465, 124, 0 );
  tbl_horiz_sep( w, 314, 465, 125, 0 );
  tbl_horiz_sep( w, 394, 332, 51, 0 );
  tbl_horiz_sep( w, 314, 332, 52, 0 );
  tbl_horiz_sep( w, 549, 332, 59, 0 );
  tbl_horiz_sep( w, 446, 332, 60, 0 );
  tbl_horiz_sep( w, 115, 370, 42, 0 );
  tbl_horiz_sep( w, 5, 370, 42, 0 );
  tbl_horiz_sep( w, 268, 9, 45, 0 );
  tbl_horiz_sep( w, 158, 9, 45, 0 );
  tbl_horiz_sep( w, 253, 180, 60, 0 );
  tbl_horiz_sep( w, 158, 180, 61, 0 );
  tbl_horiz_sep( w, 689, 9, 58, 0 );
  tbl_horiz_sep( w, 609, 9, 59, 0 );
  tbl_horiz_sep( w, 414, 237, 53, 0 );
  tbl_horiz_sep( w, 318, 237, 53, 0 );
  tbl_horiz_sep( w, 401, 9, 70, 0 );
  tbl_horiz_sep( w, 314, 9, 71, 0 );
  tbl_horiz_sep( w, 549, 9, 59, 0 );
  tbl_horiz_sep( w, 472, 9, 60, 0 );
  tbl_vert_sep( w, 471, 9, 323, 0 );
  tbl_vert_sep( w, 445, 332, 124, 0 );
  tbl_horiz_sep( w, 609, 365, 138, 0 );
  PtRealizeWidget(w);
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
  phdisplay( HFEMS_tbl_fld[0],_CVT_6(home->U0.ueddy1));
  phdisplay( HFEMS_tbl_fld[1],_CVT_6(home->U0.veddy1));
  phdisplay( HFEMS_tbl_fld[2],_CVT_6(home->U0.weddy1));
  phdisplay( HFEMS_tbl_fld[3],_CVT_6(home->U0.teddy1));
  phdisplay( HFEMS_tbl_fld[4],_CVT_6(home->U0.ueddy2));
  phdisplay( HFEMS_tbl_fld[5],_CVT_6(home->U0.veddy2));
  phdisplay( HFEMS_tbl_fld[6],_CVT_6(home->U0.weddy2));
  phdisplay( HFEMS_tbl_fld[7],_CVT_6(home->U0.teddy2));
  phdisplay( HFEMS_tbl_fld[103],_CVT_17[home->U0.sdev_stale1]);
  phdisplay( HFEMS_tbl_fld[104],_CVT_18[home->U0.sdrv_stale1]);
  phdisplay( HFEMS_tbl_fld[105],_CVT_17[home->U0.sdev_stale2]);
  phdisplay( HFEMS_tbl_fld[106],_CVT_18[home->U0.sdrv_stale2]);
  phdisplay( HFEMS_tbl_fld[107],US_5_11_u_0(home->U0.NOx));
  phdisplay( HFEMS_tbl_fld[108],US_5_11_u_0(home->U0.NOy));
  phdisplay( HFEMS_tbl_fld[114],US_5_11_u_0(MFCtr));
}

static void BF2_0(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[8],_CVT_14(home->U0.vCO2e1));
  phdisplay( HFEMS_tbl_fld[9],_CVT_14(home->U0.vH2Oe1));
  phdisplay( HFEMS_tbl_fld[10],_CVT_14(home->U0.vCO2e2));
  phdisplay( HFEMS_tbl_fld[11],_CVT_14(home->U0.vH2Oe2));
  phdisplay( HFEMS_tbl_fld[12],US_6_3_f_c(_CVT_12(home->U0.vO3ed)));
}

static void BF8_0(void) {
  BF2_0();
  {
    flttime = itime(); {
    phdisplay( HFEMS_tbl_fld[113],timetext(flttime));
  }
  }
  phdisplay( HFEMS_tbl_fld[110],_CVT_4(home->U28.TDrift));
  phdisplay( HFEMS_tbl_fld[111],_CVT_2[home->U26.CPU_Pct]);
  phdisplay( HFEMS_tbl_fld[112],_CVT_1(home->U28.Disk));
}

static void BF16_0(void) {
  BF8_0();
  phdisplay( HFEMS_tbl_fld[88],_CVT_7[home->U26.DSt0]);
}

static void BF16_1(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[85],_CVT_8(home->U24.fcNO_NOx_SP));
  phdisplay( HFEMS_tbl_fld[86],_CVT_8(home->U14.fcNO2_NOx_SP));
  phdisplay( HFEMS_tbl_fld[87],_CVT_8(home->U26.fcNO_NOy_SP));
  phdisplay( HFEMS_tbl_fld[43],_CVT_14(home->U12.fcNO_NOx));
  phdisplay( HFEMS_tbl_fld[44],_CVT_14(home->U12.fcNO2_NOx));
  phdisplay( HFEMS_tbl_fld[45],_CVT_14(home->U16.fcNO_NOy));
  phdisplay( HFEMS_tbl_fld[46],_CVT_14(home->U10.fcEff_NOy));
  phdisplay( HFEMS_tbl_fld[47],_CVT_14(home->U16.fcZer_NOy));
}

static void BF16_2(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[84],_CVT_8(home->U24.fc_CO2e_SP));
  phdisplay( HFEMS_tbl_fld[38],_CVT_14(home->U22.FlCO));
  phdisplay( HFEMS_tbl_fld[48],_CVT_14(home->U18.fc_CO2e));
}

static void BF16_3(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[80],_CVT_8(home->U20.FlCO2p_SP));
  phdisplay( HFEMS_tbl_fld[81],_CVT_8(home->U16.FlCO2e3_SP));
  phdisplay( HFEMS_tbl_fld[83],_CVT_8(home->U26.FlCO_SP));
  phdisplay( HFEMS_tbl_fld[34],_CVT_14(home->U10.FlCO2p));
  phdisplay( HFEMS_tbl_fld[35],_CVT_14(home->U14.FlCO2e1));
  phdisplay( HFEMS_tbl_fld[36],_CVT_14(home->U12.FlCO2e2));
  phdisplay( HFEMS_tbl_fld[37],US_6_3_f_c(_CVT_10(home->U14.FlCO2e3)));
  phdisplay( HFEMS_tbl_fld[39],_CVT_14(home->U14.FlNOx));
}

static void BF16_4(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[40],_CVT_14(home->U16.FlO3_NOx));
  phdisplay( HFEMS_tbl_fld[41],_CVT_14(home->U10.FlNOy));
  phdisplay( HFEMS_tbl_fld[42],_CVT_14(home->U18.FlO3_NOy));
}

static void BF16_5(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[78],_CVT_8(home->U12.Pman_SP));
  phdisplay( HFEMS_tbl_fld[19],US_6_3_f_c(_CVT_12(home->U12.PPFD_mid)));
  phdisplay( HFEMS_tbl_fld[20],US_6_3_f_c(_CVT_12(home->U14.PPFD_ref)));
  phdisplay( HFEMS_tbl_fld[21],US_6_3_f_c(_CVT_12(home->U8.PPFD_cal)));
  phdisplay( HFEMS_tbl_fld[22],US_6_3_f_c(_CVT_12(home->U12.PPFD_gnd)));
  phdisplay( HFEMS_tbl_fld[24],US_6_3_f_c(_CVT_12(home->U16.PPFD_d)));
  phdisplay( HFEMS_tbl_fld[25],US_6_3_f_c(_CVT_10(home->U10.Pamb)));
  phdisplay( HFEMS_tbl_fld[26],US_6_3_f_c(_CVT_10(home->U10.Pman)));
  phdisplay( HFEMS_tbl_fld[33],_CVT_14(home->U8.FlowT));
}

static void BF16_6(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[18],US_6_3_f_c(_CVT_12(home->U10.PPFD_top)));
  phdisplay( HFEMS_tbl_fld[23],US_6_3_f_c(_CVT_12(home->U14.PPFD_t)));
  phdisplay( HFEMS_tbl_fld[28],US_6_3_f_c(_CVT_10(home->U20.PrCO2e1)));
  phdisplay( HFEMS_tbl_fld[30],US_6_3_f_c(_CVT_10(home->U20.PrCO)));
}

static void BF16_7(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[79],_CVT_8(home->U16.PrCO2p_SP));
  phdisplay( HFEMS_tbl_fld[82],_CVT_8(home->U22.PrCO_SP));
  phdisplay( HFEMS_tbl_fld[27],US_6_3_f_c(_CVT_10(home->U10.PrCO2p)));
  phdisplay( HFEMS_tbl_fld[29],US_6_3_f_c(_CVT_10(home->U14.PrCO2e2)));
  phdisplay( HFEMS_tbl_fld[31],US_6_3_f_c(_CVT_10(home->U14.PrNOx)));
  phdisplay( HFEMS_tbl_fld[32],US_6_3_f_c(_CVT_10(home->U18.PrNOy)));
  phdisplay( HFEMS_tbl_fld[93],US_6_1_f_c(_CVT_9(home->U10.RH1)));
}

static void BF16_8(void) {
  BF8_0();
  phdisplay( HFEMS_tbl_fld[89],_CVT_7[home->U28.DSt1]);
}

static void BF16_9(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[94],US_6_1_f_c(_CVT_9(home->U8.RH2)));
  phdisplay( HFEMS_tbl_fld[95],US_6_1_f_c(_CVT_9(home->U8.RH3)));
  phdisplay( HFEMS_tbl_fld[96],US_6_1_f_c(_CVT_9(home->U8.RH4)));
  phdisplay( HFEMS_tbl_fld[97],US_6_1_f_c(_CVT_9(home->U6.RH5)));
  phdisplay( HFEMS_tbl_fld[98],US_6_1_f_c(_CVT_9(home->U6.RH6)));
  phdisplay( HFEMS_tbl_fld[99],US_6_1_f_c(_CVT_9(home->U6.RH7)));
  phdisplay( HFEMS_tbl_fld[100],US_6_1_f_c(_CVT_9(home->U10.RH8)));
  phdisplay( HFEMS_tbl_fld[101],US_6_1_f_c(_CVT_9(home->U12.RH9)));
  phdisplay( HFEMS_tbl_fld[102],US_6_1_f_c(_CVT_9(home->U6.RH10)));
}

static void BF16_10(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[16],_CVT_16(home->U8.Rnet));
  phdisplay( HFEMS_tbl_fld[17],_CVT_16(home->U8.Rnet_cal));
  phdisplay( HFEMS_tbl_fld[64],US_6_3_f_c(_CVT_12(home->U2.Ta1)));
  phdisplay( HFEMS_tbl_fld[73],US_6_3_f_c(_CVT_12(home->U0.Ta10)));
}

static void BF16_11(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[65],US_6_3_f_c(_CVT_12(home->U2.Ta2)));
  phdisplay( HFEMS_tbl_fld[66],US_6_3_f_c(_CVT_12(home->U4.Ta3)));
  phdisplay( HFEMS_tbl_fld[67],US_6_3_f_c(_CVT_12(home->U4.Ta4)));
  phdisplay( HFEMS_tbl_fld[68],US_6_3_f_c(_CVT_12(home->U4.Ta5)));
  phdisplay( HFEMS_tbl_fld[69],US_6_3_f_c(_CVT_12(home->U2.Ta6)));
  phdisplay( HFEMS_tbl_fld[70],US_6_3_f_c(_CVT_12(home->U0.Ta7)));
  phdisplay( HFEMS_tbl_fld[71],US_6_3_f_c(_CVT_12(home->U0.Ta8)));
  phdisplay( HFEMS_tbl_fld[72],US_6_3_f_c(_CVT_12(home->U4.Ta9)));
  phdisplay( HFEMS_tbl_fld[74],US_6_3_f_c(_CVT_12(home->U2.Tcal)));
}

static void BF16_12(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[61],US_6_3_f_c(_CVT_11(home->U12.TCO2e1)));
  phdisplay( HFEMS_tbl_fld[62],US_6_3_f_c(_CVT_11(home->U20.TCO2e2)));
  phdisplay( HFEMS_tbl_fld[63],US_6_3_f_c(_CVT_11(home->U22.TCO2p)));
  phdisplay( HFEMS_tbl_fld[75],US_6_3_f_c(_CVT_12(home->U4.Tr1)));
}

static void BF16_13(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[49],US_6_3_f_c(_CVT_12(home->U6.Ts1)));
  phdisplay( HFEMS_tbl_fld[50],US_6_3_f_c(_CVT_12(home->U2.Ts2)));
  phdisplay( HFEMS_tbl_fld[51],US_6_3_f_c(_CVT_12(home->U2.TS3)));
  phdisplay( HFEMS_tbl_fld[52],US_6_3_f_c(_CVT_12(home->U6.Ts4)));
  phdisplay( HFEMS_tbl_fld[53],US_6_3_f_c(_CVT_12(home->U6.Ts5)));
  phdisplay( HFEMS_tbl_fld[58],US_6_3_f_c(_CVT_12(home->U6.Ts10)));
  phdisplay( HFEMS_tbl_fld[59],US_6_3_f_c(_CVT_12(home->U4.TS11)));
  phdisplay( HFEMS_tbl_fld[76],US_6_3_f_c(_CVT_12(home->U4.Tr2)));
  phdisplay( HFEMS_tbl_fld[77],US_6_3_f_c(_CVT_12(home->U6.Tr3)));
}

static void BF16_14(void) {
  BF2_0();
  phdisplay( HFEMS_tbl_fld[54],US_6_3_f_c(_CVT_12(home->U4.Ts6)));
  phdisplay( HFEMS_tbl_fld[55],US_6_3_f_c(_CVT_12(home->U4.Ts7)));
  phdisplay( HFEMS_tbl_fld[56],US_6_3_f_c(_CVT_12(home->U8.TS8)));
  phdisplay( HFEMS_tbl_fld[57],US_6_3_f_c(_CVT_12(home->U8.TS9)));
}

static void BF16_15(void) {
  BF1_0();
  phdisplay( HFEMS_tbl_fld[13],_CVT_16(home->U2.vCO2prf));
  phdisplay( HFEMS_tbl_fld[14],_CVT_16(home->U2.vO3prf));
  phdisplay( HFEMS_tbl_fld[15],_CVT_16(home->U2.vCO));
  phdisplay( HFEMS_tbl_fld[90],_CVT_7[home->U18.DSt4]);
  phdisplay( HFEMS_tbl_fld[91],_CVT_7[home->U18.DSt5]);
  phdisplay( HFEMS_tbl_fld[92],_CVT_7[home->U22.DSt6]);
  phdisplay( HFEMS_tbl_fld[60],US_6_3_f_c(_CVT_12(home->U12.T_MB)));
  phdisplay( HFEMS_tbl_fld[109],_CVT_5[home->U0.SolSt]);
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
