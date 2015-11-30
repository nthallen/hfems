%{
  /* HFEMS.cmd */
  #ifdef SERVER
    #include "address.h"
    #include "subbus.h"
  
    void write_savelog( char *s ) {
      FILE *fp;
      fp = fopen( "saverun.log", "a" );
      if ( fp == 0 ) nl_error( 2, "Unable to write to saverun.log" );
      else {
        fprintf( fp, "%s\n", s );
        fclose( fp );
      }
    }
    
    void write_restart() {
      FILE *fp;
      fp = fopen("restart.txt", "a");
      if (fp == 0) nl_error(2, "Unable to create restart.txt");
      else {
        fclose(fp);
      }
    }

  #endif
%}

%INTERFACE <dccc:dccc>
%INTERFACE <SoldrvA>

&command
  : Savelog %s (Enter Log Message) * { write_savelog($2); }
  : Request Restart * { write_restart(); }
  : &HFEMScmdset { if_dccc.Turf( "D%d\n", $1 ); }
  : Soldrv select mode %d (Enter Mode Number) *
    { if_SoldrvA.Turf("S%d\n", $4 ); }
  : Set &daspt_cmd %lf (Enter Setpoint Value in Volts) * {
      double N = $3 * 409.6;
      unsigned short bits;
      if ( N > 4095. ) bits = 4095;
      else if ( N < 0 ) bits = 0;
      else bits = (unsigned short)N;
      sbwr($2,bits);
    }
  ;
&daspt_cmd <unsigned short>
  : Pman setpoint { $0 = Pman_SP_Address; }
  : PrCO2p setpoint { $0 = PrCO2p_SP_Address; }
  : FlCO2p setpoint { $0 = FlCO2p_SP_Address; }
  : PrCO2e1 setpoint { $0 = PrCO2e1_SP_Address; }
  : PrCO2e2 setpoint { $0 = PrCO2e2_SP_Address; }
  : PrCO setpoint { $0 = PrCO_SP_Address; }
  : fcNO_NOx setpoint { $0 = fcNO_NOx_SP_Address; }
  : fcNO2_NOx setpoint { $0 = fcNO2_NOx_SP_Address; }
  : fc_CO2e setpoint { $0 = fc_CO2e_SP_Address; }
  : fcNO_NOy setpoint { $0 = fcNO_NOy_SP_Address; }
  : fcEff_NOy setpoint { $0 = fcEff_NOy_SP_Address; }
  : fcZer_NOy setpoint { $0 = fcZer_NOy_SP_Address; }
  : FlNOx setpoint { $0 = FlNOx_SP_Address; }
  : FlNOy setpoint { $0 = FlNOy_SP_Address; }
  : FlCO2e3 setpoint { $0 = FlCO2e3_SP_Address; }
  : FlCO setpoint { $0 = FlCO_SP_Address; }
;
#

&HFEMScmdset <int>
  : Solenoid Lvl1 ON * { $0 = 0; } 
  : Solenoid Lvl1 OFF  * { $0 = 1 ; } 
  : Solenoid Lvl2 ON  * { $0 = 2 ; } 
  : Solenoid Lvl2 OFF  * { $0 = 3 ; } 
  : Solenoid Lvl3 ON  * { $0 = 4 ; } 
  : Solenoid Lvl3 OFF  * { $0 = 5 ; } 
  : Solenoid Lvl4 ON  * { $0 = 6 ; } 
  : Solenoid Lvl4 OFF  * { $0 = 7 ; } 
  : Solenoid Lvl5 ON  * { $0 = 8 ; } 
  : Solenoid Lvl5 OFF  * { $0 = 9 ; } 
  : Solenoid Lvl6 ON   * { $0 = 10 ; } 
  : Solenoid Lvl6 OFF  * { $0 = 11 ; } 
  : Solenoid Lvl7 ON   * { $0 = 12 ; } 
  : Solenoid Lvl7 OFF  * { $0 = 13 ; } 
  : Solenoid Lvl8 ON   * { $0 = 14 ; } 
  : Solenoid Lvl8 OFF  * { $0 = 15 ; } 
  : Solenoid eCO2cal_on ON  * { $0 = 16 ; } 
  : Solenoid eCO2cal_on OFF  * { $0 = 17 ; } 
  : Solenoid CO2add1 ON  * { $0 = 18 ; } 
  : Solenoid CO2add1 OFF  * { $0 = 19 ; } 
  : Solenoid CO2add2 ON  * { $0 = 20 ; } 
  : Solenoid CO2add2 OFF  * { $0 = 21 ; } 
  : Solenoid CO_smpl ON  * { $0 = 22 ; } 
  : Solenoid CO_smpl OFF  * { $0 = 23 ; } 
  : Solenoid CO_cal1 ON  * { $0 = 24 ; } 
  : Solenoid CO_cal1 OFF  * { $0 = 25 ; } 
  : Solenoid CO_cal2 ON  * { $0 = 26 ; } 
  : Solenoid CO_cal2 OFF  * { $0 = 27 ; } 
  : Solenoid CO_zer ON  * { $0 = 28 ; } 
  : Solenoid CO_zer OFF  * { $0 = 29 ; } 
  : Solenoid eff_Hg ON  * { $0 = 30 ; } 
  : Solenoid eff_Hg OFF  * { $0 = 31 ; } 
  : Solenoid SpCmd_17 ON  * { $0 = 32 ; } 
  : Solenoid SpCmd_17 OFF  * { $0 = 33 ; } 
  : Solenoid SpCmd_18 ON  * { $0 = 34 ; } 
  : Solenoid SpCmd_18 OFF  * { $0 = 35 ; } 
  : Solenoid SpCmd_19 ON  * { $0 = 36 ; } 
  : Solenoid SpCmd_19 OFF  * { $0 = 37 ; } 
  : Solenoid SpCmd_20 ON  * { $0 = 38 ; } 
  : Solenoid SpCmd_20 OFF  * { $0 = 39 ; } 
  : Solenoid SpCmd_21 ON  * { $0 = 40 ; } 
  : Solenoid SpCmd_21 OFF  * { $0 = 41 ; } 
  : Solenoid SpCmd_22 ON  * { $0 = 42 ; } 
  : Solenoid SpCmd_22 OFF  * { $0 = 43 ; } 
  : Solenoid SpCmd_23 ON  * { $0 = 44 ; } 
  : Solenoid SpCmd_23 OFF  * { $0 = 45 ; } 
  : Solenoid SpCmd_24 ON  * { $0 = 46 ; } 
  : Solenoid SpCmd_24 OFF  * { $0 = 47 ; } 
  : Solenoid SpCmd_25 ON  * { $0 = 48 ; } 
  : Solenoid SpCmd_25 OFF  * { $0 = 49 ; } 
  : Solenoid SpCmd_26 ON  * { $0 = 50 ; } 
  : Solenoid SpCmd_26 OFF  * { $0 = 51 ; } 
  : Solenoid SpCmd_27 ON  * { $0 = 52 ; } 
  : Solenoid SpCmd_27 OFF  * { $0 = 53 ; } 
  : Solenoid SpCmd_28 ON  * { $0 = 54 ; } 
  : Solenoid SpCmd_28 OFF  * { $0 = 55 ; } 
  : Solenoid SpCmd_29 ON  * { $0 = 56 ; } 
  : Solenoid SpCmd_29 OFF  * { $0 = 57 ; } 
  : Solenoid SpCmd_30 ON  * { $0 = 58 ; } 
  : Solenoid SpCmd_30 OFF  * { $0 = 59 ; } 
  : Solenoid SpCmd_31 ON  * { $0 = 60 ; } 
  : Solenoid SpCmd_31 OFF  * { $0 = 61 ; } 
  : Solenoid SpCmd_32 ON  * { $0 = 62 ; } 
  : Solenoid SpCmd_32 OFF  * { $0 = 63 ; } 
  : Solenoid zNOy_Hg ON  * { $0 = 64 ; }
  : Solenoid zNOy_Hg OFF  * { $0 = 65 ; }
  : Solenoid NO_NOy_on ON  * { $0 = 66 ; }
  : Solenoid NO_NOy_on OFF  * { $0 = 67 ; }
  : Solenoid NPN_on ON  * { $0 = 68 ; }
  : Solenoid NPN_on OFF  * { $0 = 69 ; }
  : Solenoid NO_NOy_add ON  * { $0 = 70 ; }
  : Solenoid NO_NOy_add OFF  * { $0 = 71 ; }
  : Solenoid NPN_add ON  * { $0 = 72 ; }
  : Solenoid NPN_add OFF  * { $0 = 73 ; }
  : Solenoid NOy_eff_add ON  * { $0 = 74 ; }
  : Solenoid NOy_eff_add OFF  * { $0 = 75 ; }
  : Solenoid zNOy_add ON  * { $0 = 76 ; }
  : Solenoid zNOy_add OFF  * { $0 = 77 ; }
  : Solenoid zNOx_Hg ON  * { $0 = 78 ; }
  : Solenoid zNOx_Hg OFF  * { $0 = 79 ; }
  : Solenoid NO_NOx_on ON  * { $0 = 80 ; }
  : Solenoid NO_NOx OFF  * { $0 = 81 ; }
  : Solenoid NO2_on ON  * { $0 = 82 ; }
  : Solenoid NO2_on OFF  * { $0 = 83 ; }
  : Solenoid zNOx_add ON  * { $0 = 84 ; }
  : Solenoid zNOx_add OFF  * { $0 = 85 ; }
  : Solenoid NO_NOx_add ON  * { $0 = 86 ; }
  : Solenoid NO_NOx_add OFF  * { $0 = 87 ; }
  : Solenoid NO2_add ON  * { $0 = 88 ; }
  : Solenoid NO2_add OFF  * { $0 = 89 ; }
  : Solenoid Shutter ON  * { $0 = 90 ; }
  : Solenoid Shutter OFF  * { $0 = 91 ; }
  : Solenoid pCO2_smpl ON  * { $0 = 92 ; }
  : Solenoid pCO2_smpl OFF  * { $0 = 93 ; }
  : Solenoid pCO2_cal1 ON  * { $0 = 94 ; }
  : Solenoid pCO2_cal1 OFF  * { $0 = 95 ; }
  : Solenoid pCO2_cal2 ON  * { $0 = 96 ; }
  : Solenoid pCO2_cal2 OFF  * { $0 = 97 ; }
  : Solenoid pCO2_cal3 ON  * { $0 = 98 ; }
  : Solenoid pCO2_cal3 OFF  * { $0 = 99 ; }
  : Solenoid pCO2_cala ON  * { $0 = 100 ; }
  : Solenoid pCO2_cala OFF  * { $0 = 101 ; }
  : Solenoid pCO2_calR ON  * { $0 = 102 ; }
  : Solenoid pCO2_calR OFF  * { $0 = 103 ; }
  : Solenoid Hub_sp1 ON  * { $0 = 104 ; }
  : Solenoid Hub_sp1 OFF  * { $0 = 105 ; }
  : Solenoid Hub_sp2 ON  * { $0 = 106 ; }
  : Solenoid Hub_sp2 OFF  * { $0 = 107 ; }
  : Solenoid Shk_sp1 ON  * { $0 = 108 ; }
  : Solenoid Shk_sp1 OFF  * { $0 = 109 ; }
  : Solenoid Shk_sp2 ON  * { $0 = 110 ; }
  : Solenoid Shk_sp2 OFF  * { $0 = 111 ; }
  : Solenoid Sol_41 ON  * { $0 = 112 ; }
  : Solenoid Sol_41 OFF  * { $0 = 113 ; }
  : Solenoid Sol_42 ON  * { $0 = 114 ; }
  : Solenoid Sol_42 OFF  * { $0 = 115 ; }
  : Solenoid Sol_43 ON  * { $0 = 116 ; }
  : Solenoid Sol_43 OFF  * { $0 = 117 ; }
  : Solenoid Sol_44 ON  * { $0 = 118 ; }
  : Solenoid Sol_44 OFF  * { $0 = 119 ; }
  : Solenoid Sol_45 ON  * { $0 = 120 ; }
  : Solenoid Sol_45 OFF  * { $0 = 121 ; }
  : Solenoid Sol_46 ON  * { $0 = 122 ; }
  : Solenoid Sol_46 OFF  * { $0 = 123 ; }
  : Solenoid Sol_47 ON  * { $0 = 124 ; }
  : Solenoid Sol_47 OFF  * { $0 = 125 ; }
  : Solenoid Sol_48 ON  * { $0 = 126 ; }
  : Solenoid Sol_48 OFF  * { $0 = 127 ; }
  ;

####### need to redefine this - if we need it ######################
#  : Reset Digital Outputs * {
#### Copy from HFEMS.dccc
#     sbwr(0x818, 0); /*  Card 0, reset */
#     sbwr(0x806, 0x8989); /*  Card 0, config */
#     sbwr(0x838, 0); /*  Card 1, reset */
#     sbwr(0x826, 0x8989); /*  Card 1, config */
#   }
# ;
#
