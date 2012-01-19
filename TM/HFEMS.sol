     ;-----------------------------------------------------------------------
     ;	 			SOLENOID CYCLE FORMAT
     ;
     ; This is a solenoid cycle format file.  It can be interpreted by the
     ; solfmt program to produce a numeric representation of the solenoid
     ; cycle information.  This numerical version can then be interpreted
     ; by the soldrv program which drives the solenoids during instrument
     ; operation.
     ;       This file was created on Oct. 3 2011 by Bill Munger as the 
     ; 		initial version of control files for the new system 
     ;-----------------------------------------------------------------------
     ; Hardware definitions of the solenoids:
     ; and Analog outputs
     ;-----------------------------------------------------------------------


	Solenoid Lvl1 0 1 0
	Solenoid Lvl2 2 3 0
	Solenoid Lvl3 4 5 0
	Solenoid Lvl4 6 7 0
	Solenoid Lvl5 8 9 0
	Solenoid Lvl6 10 11 0
	Solenoid Lvl7 12 13 0
	Solenoid Lvl8 14 15 0
	Solenoid eCO2cal 16 17 0
	Solenoid CO2add1 18 19 0
	Solenoid CO2add2 20 21 0
	Solenoid CO_smpl 22 23 0
	Solenoid CO_cal1 24 25 0
	Solenoid CO_cal2 26 27 0
	Solenoid CO_zer 28 29 0
	Solenoid eff_Hg 30 31 0
	Solenoid zNOy_Hg 64 65 0
	Solenoid NO_NOy_on 66 67 0
	Solenoid NPN_on 68 69 0
	Solenoid NO_NOy_add 70 71 0
	Solenoid NPN_add 72 73 0
	Solenoid NOy_eff_add 74 75 0
	Solenoid zNOy_add 76 77 0
	Solenoid zNOx_Hg 78 79 0
	Solenoid NO_NOx_on 80 81 0
	Solenoid NO2_on 82 83 0
	Solenoid zNOx_add 84 85 0
	Solenoid NO_NOx_add 86 87 0
	Solenoid NO2_add 88 89 0
	Solenoid Shutter 90 91 0
	Solenoid pCO2_smpl 92 93 0
	Solenoid pCO2_cal1 94 95 0
	Solenoid pCO2_cal2 96 97 0
	Solenoid pCO2_cal3 98 99 0
	Solenoid pCO2_cala 100 101 0
	Solenoid pCO2_calR 102 103 0
	Solenoid Hub_sp1 104 105 0
	Solenoid Hub_sp2 106 107 0
	Solenoid Shk_sp1 108 109 0
	Solenoid Shk_sp2 110 111 0
	Solenoid SpCmd_17 32 33 0
	Solenoid SpCmd_18 34 35 0
	Solenoid SpCmd_19 36 37 0
	Solenoid SpCmd_20 38 39 0
	Solenoid SpCmd_21 40 41 0
	Solenoid SpCmd_22 42 43 0
	Solenoid SpCmd_23 44 45 0
	Solenoid SpCmd_24 46 47 0
	Solenoid SpCmd_25 48 49 0
	Solenoid SpCmd_26 50 51 0
	Solenoid SpCmd_27 52 53 0
	Solenoid SpCmd_28 54 55 0
	Solenoid SpCmd_29 56 57 0
	Solenoid SpCmd_30 58 59 0
	Solenoid SpCmd_31 60 61 0
	Solenoid SpCmd_32 62 63 0
	Solenoid Sol_41 112 113 0
	Solenoid Sol_42 114 115 0
	Solenoid Sol_43 116 117 0
	Solenoid Sol_44 118 119 0
	Solenoid Sol_45 120 121 0
	Solenoid Sol_46 122 123 0
	Solenoid Sol_47 124 125 0
	Solenoid Sol_48 126 127 0

; Define some DtoA values here
; only defining the ones associated with calibration gas flows that vary
; during the calibration cycle
; system pressure and flows will be set by commands in the algorithm
;jwm - Oct 5 2011
;DtoA Pman 0xC60H   
;DtoA PrCO2p 0xC62H   
;DtoA FlCO2p 0xC64H   
;DtoA PrCO2e1 0xC66H   
;DtoA PrCO2e2 0xC68H  
;DtoA PrCO 0xC6AH  
; adjust these initial default flow rates as needed when calibrations
; are being defined
DtoA fcNO_NOx 0xC6C   {_:0 L:0x2000 M:0x4000 H:0x8000}
DtoA fcNO2_NOx 0xC6E   {_:0 L:0x2000 M:0x4000 H:0x8000}
DtoA fc_CO2e 0xCE0  {_:0 L:0x2000 M:0x4000 H:0x8000}
DtoA fcNO_NOy 0xCE2  {_:0 L:0x2000 M:0x4000 H:0x8000}
DtoA fcEff_NOy 0xCE4  {_:0 L:0x2000 M:0x4000 H:0x8000}
DtoA fcZer_NOy 0xCE6  {_:0 L:0x2000 M:0x4000 H:0x8000}
;DtoA FlNOx 0xCE8H  
;DtoA FlNOy 0xCEAH  
;DtoA PrO3e 0xCECH  
;DtoA FlCO 0xCEEH  

; last 4 setpoints are auxilliary and are manual control

; redefine SolSt values if we need them
DtoA SolSt 0 { 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7 8:8
	   C:10 N:20 E:30 F:40 Z:50 S:60
	   a:51 b:11 c:21 d:22 e:2 f:13 g:33 h:34 i:4 j:5
	   k:25 l:36 m:16 n:17 o:27 p:28 q:8 }

     Resolution = 60/1	; One minute resolution


routine Sample {
  SolSt:  aaaa:bb:cc:dd:ee:ff:gg:hh:ii:jj:kk:ll:mm:nn:oo:pp:qq:^
  Lvl1:  OOOO:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  Lvl2:  ____:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
  Lvl3:  ____:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:^
  Lvl4:  ____:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:^
  Lvl5:  ____:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:^
  Lvl6:  ____:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:^
  Lvl7:  ____:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:^
  Lvl8:  ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
  eCO2cal: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO2add1: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO2add2: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO_smpl: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO_cal1: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO_cal2: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  CO_zer: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  eff_Hg: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  zNOy_Hg: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO_NOy_on: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NPN_on: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO_NOy_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NPN_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NOy_eff_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  zNOy_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  zNOx_Hg: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO_NOx_on: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO2_on: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  zNOx_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO_NOx_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  NO2_add: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  Shutter: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_smpl: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_cal1: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_cal2: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_cal3: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_cala: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  pCO2_calR: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
  fcNO_NOx: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
  fcNO2_NOx: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
  fc_CO2e: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
  fcNO_NOy: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
  fcEff_NOy: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
  fcZer_NOy: ____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}


Mode 0 { ; Stop mode
  Lvl1:  O 
  Lvl2:  _
  Lvl3:  _
  Lvl4:  _
  Lvl5:  _
  Lvl6:  _
  Lvl7:  _
  Lvl8:  _
  eCO2cal: _
  CO2add1: _
  CO2add2: _
  CO_smpl: _
  CO_cal1: _
  CO_cal2: _
  CO_zer: _
  eff_Hg: _
  zNOy_Hg: _
  NO_NOy_on: _
  NPN_on: _
  NO_NOy_add: _
  NPN_add: _
  NOy_eff_add: _
  zNOy_add: _
  zNOx_Hg: _
  NO_NOx_on: _
  NO2_on: _
  zNOx_add: _
  NO_NOx_add: _
  NO2_add: _
  Shutter: _
  pCO2_smpl: _
  pCO2_cal1: _
  pCO2_cal2: _
  pCO2_cal3: _
  pCO2_cala: _ 
  pCO2_calR: _
  fcNO_NOx: _
  fcNO2_NOx: _
  fc_CO2e: _
  fcNO_NOy: _
  fcEff_NOy: _
  fcZer_NOy: _
}

Mode 1 { ; Test mode
  Lvl1:  _ 
  Lvl2:  _
  Lvl3:  _
  Lvl4:  _
  Lvl5:  _
  Lvl6:  _
  Lvl7:  _
  Lvl8:  _
  eCO2cal: _
  CO2add1: _
  CO2add2: _
  CO_smpl: _
  CO_cal1: _
  CO_cal2: _
  CO_zer: _
  eff_Hg: _
  zNOy_Hg: _
  NO_NOy_on: _
  NPN_on: _
  NO_NOy_add: _
  NPN_add: _
  NOy_eff_add: _
  zNOy_add: _
  zNOx_Hg: _
  NO_NOx_on: _
  NO2_on: _
  zNOx_add: _
  NO_NOx_add: _
  NO2_add: _
  Shutter: _
  pCO2_smpl: O
  pCO2_cal1: _
  pCO2_cal2: _
  pCO2_cal3: O
  pCO2_cala: _ 
  pCO2_calR: _
  fcNO_NOx: _
  fcNO2_NOx: _
  fc_CO2e: _
  fcNO_NOy: _
  fcEff_NOy: _
  fcZer_NOy: _
}
