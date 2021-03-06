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


	Solenoid Lvl1 0 1 0;	Lvl1 is a normally open 3/14/13
	Solenoid Lvl2 2 3 0;	profile level 2
	Solenoid Lvl3 4 5 0;	profile level 3
	Solenoid Lvl4 6 7 0;	profile level 4
	Solenoid Lvl5 8 9 0;	profile level 5
	Solenoid Lvl6 10 11 0;	profile level 6
	Solenoid Lvl7 12 13 0;	profile level 7
	Solenoid Lvl8 14 15 0;	profile level 8
	Solenoid eCO2cal 16 17 0;	CO2 std addition flow on
	Solenoid CO2add1 18 19 0;	CO2 std addition to Eddy1
	Solenoid CO2add2 20 21 0;	CO2 std addition to Eddy2 - connector finished 12/4/14
	Solenoid CO_smpl 22 23 0;	CO cal/sample select - on for cal
	Solenoid CO_cal1 24 25 0;	CO calibration hi standard
	Solenoid CO_cal2 26 27 0;	CO calibration lo standard
	Solenoid CO_zer 28 29 0;	CO zeroing
	Solenoid eff_Hg 30 31 0;	NOy efficiency lamp on
	Solenoid zNOy_Hg 64 65 0;	NOy zeroing lamp on
	Solenoid NO_NOy_on 66 67 0;	NOy NO standard on not working, use NPN
	Solenoid NPN_on 68 69 0;	NOy nPN standard on
	Solenoid NO_NOy_add 70 71 0;	NOy NO standard addition on
	Solenoid NPN_add 72 73 0;	NOy nPN standard addition on
	Solenoid NOy_eff_add 74 75 0; 	NOy efficiency addition on
	Solenoid zNOy_add 76 77 0;	NOy zero on
	Solenoid zNOx_Hg 78 79 0;	NOx zeroing lamp on
	Solenoid NO_NOx_on 80 81 0;	NOx NO standard on
	Solenoid NO2_on 82 83 0;	NOx NO2 standard on
	Solenoid zNOx_add 84 85 0;	NOx zero on
	Solenoid NO_NOx_add 86 87 0;	NOx NO standard addition on
	Solenoid NO2_add 88 89 0;	NOx NO2 standard addition on - used for CO2add2 10/17/14 until 12/4/14
	Solenoid Shutter 90 91 0;	NO2 photolysis LED on
	Solenoid pCO2_smpl 92 93 0;	profile CO2 sample/cal  - on for cal
	Solenoid pCO2_cal1 94 95 0;	profile CO2 lo standard
	Solenoid pCO2_cal2 96 97 0;	profile CO2 med standard
	Solenoid pCO2_cal3 98 99 0;	profile CO2 hi standard, 
	Solenoid pCO2_cala 100 101 0;	profile CO2 surveilance standard 
	Solenoid pCO2_calR 102 103 0;	profile CO2 reference/zero standard
	Solenoid Hub_sp1 104 105 0;	relay for LI7200 power
	Solenoid Hub_sp2 106 107 0;	relay for sonic heater power
	Solenoid Shk_sp1 108 109 0;	7/9/18, configured to shut off NOy zero air
	Solenoid Shk_sp2 110 111 0
	Solenoid SpCMD17 32 33 0
	Solenoid SpCmd18 34 35 0
	Solenoid SpCmd19 36 37 0
	Solenoid SpCmd20 38 39 0
	Solenoid SpCmd21 40 41 0
	Solenoid SpCmd22 42 43 0
	Solenoid SpCmd23 44 45 0
	Solenoid SpCmd24 46 47 0
	Solenoid SpCmd25 48 49 0
	Solenoid SpCmd26 50 51 0
	Solenoid SpCmd27 52 53 0
	Solenoid SpCmd28 54 55 0
	Solenoid SpCmd29 56 57 0
	Solenoid SpCmd30 58 59 0
	Solenoid SpCmd31 60 61 0
	Solenoid SpCmd32 62 63 0
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
;set points defined based on 0-4096 range 10V = 4096
; 2/4/15, put in fc_CO2e settings that are too low in order to get the faulty MFC
; to provide variation
; 4/15/15, jwm, adjusted fc_CO2 setpoints based on manual tests to get desired flows
; jwm switched the assignments for fc_CO2e and fcNO_NOx
; implemented use of set point for NOyzero 7/19/18
DtoA fc_CO2e 0xC6C   {_:0 L:100 H:200 Z:1840}
DtoA fcNO2_NOx 0xC6E   {_:0 L:1000 M:1750 H:1950}
DtoA fcNO_NOx 0xCE0  {_:0 L:800  M:1250	H:1950}
DtoA fcNO_NOy 0xCE2  {_:0 L:1000 M:1400 H:1950}
DtoA fcEff_NOy 0xCE4  {_:0 L:1000 M:1400 H:1950} ; this controls the NPN flow
DtoA fcZer_NOy 0xCE6  {_:0 L:512 M:1230 H:2048}

; redefine SolSt values if we need them
DtoA SolSt 0 { 0:0 1:1 2:2 3:3 4:4 5:5 6:6 7:7 8:8
	   A:80 C:10 N:20 E:30 P:40 Z:50 S:60 L:70 
	   a:51 b:11 c:21 d:22 e:2 f:13 g:33 h:34 i:4 j:5
	   l: 81 k:25 l:36 m:16 n:17 o:27 p:28 q:8 }

     Resolution = 60/1	; One minute resolution
routine Sample {
SolSt:	        aaaa:bb:cc:dd:ee:ff:gg:hh:ii:jj:kk:ll:mm:nn:oo:pp:qq:^
Lvl1:           ____:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
Lvl2:           ____:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl3:           ____:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:^
Lvl4:		____:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:^
Lvl5:		____:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:^
Lvl6:		____:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:^
Lvl7:		____:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:^
Lvl8:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
eCO2cal:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_smpl:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal2:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_zer:	        OOOO:OO:__:__:__:OO:OO:OO:__:__:__:OO:OO:OO:__:__:__:^
;CO_zer:	OOOO:__:__:_O:OO:O_:__:__:OO:OO:__:__:_O:OO:O_:__:__:^
eff_Hg:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_Hg:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_on:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_on:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NOy_eff_add:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_Hg: 	OOOO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_add: 	__OO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_add:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shutter: 	_O__:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:^
pCO2_smpl: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal1: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal3: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cala: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_calR: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shk_sp1: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Hub_sp2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
fcNO_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO2_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fc_CO2e: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcEff_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcZer_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}

routine Sample_melt { ; same as Sample but turns on Sonic heater for an 12 minute period
SolSt:	        aaaa:bb:cc:dd:ee:ff:gg:hh:ii:jj:kk:ll:mm:nn:oo:pp:qq:^
Lvl1:           ____:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
Lvl2:           ____:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl3:           ____:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:^
Lvl4:		____:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:^
Lvl5:		____:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:^
Lvl6:		____:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:^
Lvl7:		____:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:^
Lvl8:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
eCO2cal:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_smpl:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal2:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_zer:	        OOOO:OO:__:__:__:OO:OO:OO:__:__:__:OO:OO:OO:__:__:__:^
;CO_zer:	OOOO:__:__:_O:OO:O_:__:__:OO:OO:__:__:_O:OO:O_:__:__:^
eff_Hg:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_Hg:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_on:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_on:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NOy_eff_add:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_Hg: 	OOOO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_add: 	__OO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_add:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shutter: 	_O__:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:^
pCO2_smpl: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal1: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal3: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cala: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_calR: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shk_sp1: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Hub_sp2:	OOOO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
fcNO_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO2_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fc_CO2e: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcEff_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcZer_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}

routine SampleZ { ; profile with NOy zero air zeroing
SolSt:	        aaaa:bb:cc:dd:ee:ff:gg:hh:ii:jj:kk:ll:mm:nn:oo:pp:qq:^
Lvl1:           ____:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
Lvl2:           ____:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl3:           ____:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:__:__:^
Lvl4:		____:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:__:__:^
Lvl5:		____:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:__:__:^
Lvl6:		____:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:__:__:^
Lvl7:		____:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:__:__:^
Lvl8:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
eCO2cal:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO2add2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_smpl:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal1:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal2:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_zer:	        OOOO:OO:__:__:__:OO:OO:OO:__:__:__:OO:OO:OO:__:__:__:^
;CO_zer:	OOOO:__:__:_O:OO:O_:__:__:OO:OO:__:__:_O:OO:O_:__:__:^
eff_Hg:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_Hg:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_on:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_on:		____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NPN_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NOy_eff_add:	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_Hg: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_on: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO2_add: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shutter: 	_O_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:_O:^
;Shutter: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_smpl: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal1: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal3: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cala: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_calR: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shk_sp1: 	OOO_:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
Hub_sp2: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO2_NOx: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fc_CO2e: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcNO_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcEff_NOy: 	____:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcZer_NOy: 	MMM_:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}

routine Ecal{
SolSt:       EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:EE:^
Lvl1:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl2:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl3:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl4:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl5:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl6:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl7:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl8:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
eCO2cal:     OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:__:^
CO2add1:     __:__:__:OO:OO:OO:__:__:__:__:__:__:__:__:__:^
CO2add2:     _O:OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_smpl:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal1:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_cal2:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
CO_zer:      OO:OO:OO:OO:__:__:__:__:OO:OO:OO:OO:__:__:__:^
eff_Hg:      __:__:__:__:__:__:__:__:__:__:__:__:OO:OO:OO:^
zNOy_Hg:     OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:__:^
;NO_NOy_on:   __:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:__:__:__:^
;NPN_on:      __:__:__:__:__:__:__:__:__:OO:OO:OO:OO:OO:OO:^
NPN_on:      __:__:__:__:__:__:__:__:_O:OO:OO:OO:OO:OO:OO:^
NO_NOy_on:   __:__:__:__:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
NO_NOy_add:  __:__:__:__:__:__:__:__:__:OO:OO:OO:__:__:__:^
NPN_add:     __:__:__:__:__:__:__:__:__:__:__:__:OO:OO:OO:^
NOy_eff_add: __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_add:    __:__:__:OO:OO:OO:__:__:__:__:__:__:__:__:__:^
zNOx_Hg:     OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_add:    __:OO:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_on:   __:__:__:__:__:__:__:__:__:OO:OO:OO:OO:OO:OO:^
NO_NOx_add:  __:__:__:__:__:__:__:__:__:__:__:__:OO:OO:OO:^
NO2_on:      __:__:__:__:__:__:OO:OO:OO:OO:OO:OO:__:__:__:^
NO2_add:     __:__:__:__:__:__:__:__:__:OO:OO:OO:__:__:__:^
Shutter:     _O:__:__:__:__:_O:__:__:__:_O:_O:_O:__:__:__:^
pCO2_smpl:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal1:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal2:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal3:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cala:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_calR:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shk_sp1:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Hub_sp2:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
fcNO_NOx:    __:__:__:__:__:__:HH:HH:HH:MM:MM:MM:__:__:__:^
fcNO2_NOx:   HH:HH:HM:MM:MM:MM:__:__:__:__:__:__:__:__:__:^ 
fcNO_NOy:    __:__:__:__:__:__:HH:HH:HM:MM:MM:MM:LL:LL:LL:^ 
fc_CO2e:     ZZ:LL:HH:HH:HL:LL:__:__:__:__:__:__:__:__:__:^ 
fcEff_NOy:   __:__:__:__:__:__:__:__:_H:HH:HH:ML:LL:LL:LL:^ 
;fcEff_NOy:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcZer_NOy:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}

routine ECcal{ ; same as Ecal, but with CO calibration includes CO2zero
SolSt:       CC:CC:CC:CC:CC:CC:CC:CC;CC:CC:CC:CC:CC:CC:CC:CC:^
Lvl1:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl2:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl3:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl4:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl5:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl6:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl7:	     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Lvl8:        __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
eCO2cal:     __:__:OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:^
CO2add1:     __:__:__:__:__:OO:OO:OO:__:__:__:__:__:__:__:__:^
CO2add2:     __:__:_O:OO:OO:__:__:__:__:__:__:__:__:__:__:__:^
CO_smpl:     __:__:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
CO_cal1:     __:__:__:__:__:__:__:__:__:__:OO:OO:OO:OO:OO:OO:^
CO_cal2:     __:__:__:__:OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:^
CO_zer:      __:OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:OO:OO:OO:^
eff_Hg:      __:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:OO:^
zNOy_Hg:     OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:__:__:^
NPN_on:      __:__:__:__:__:__:__:OO:OO:OO:OO:OO:OO:__:__:__:^
NO_NOy_on:   __:__:__:__:__:__:__:__:__:_O:OO:OO:OO:OO:OO:OO:^
NO_NOy_add:  __:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:OO:^
NPN_add:     __:__:__:__:__:__:__:__:__:__:OO:OO:OO:__:__:__:^
NOy_eff_add: __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOy_add:    __:__:__:OO:OO:OO:__:__:__:__:__:__:__:__:__:__:^
zNOx_Hg:     OO:OO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
zNOx_add:    __:OO:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
NO_NOx_on:   __:OO:OO:OO:OO:OO:OO:__:__:__:__:__:__:__:__:__:^
NO_NOx_add:  __:__:__:__:OO:OO:OO:__:__:__:__:__:__:OO:OO:OO:^
NO2_on:      __:__:__:__:__:__:__:OO:OO:OO:OO:OO:OO:OO:OO:OO:^
NO2_add:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Shutter:     __:__:__:__:__:__:__:_O:_O:_O:_O:_O:_O:_O:_O:_O:^
pCO2_smpl:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
pCO2_cal1:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal2:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cal3:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_cala:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
pCO2_calR:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:OO:OO:^
Shk_sp1:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
Hub_Sp2:     __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^
fcNO_NOx:    __:HH:HH:HM:ML:LL:LL:__:__:__:__:__:__:__:__:__:^
fcNO2_NOx:   __:__:__:__:__:__:__:HH:HH:HH:HH:HH:HH:MM:MM:MM:^ 
fcNO_NOy:    __:__:__:__:__:__:__:__:__:_H:HH:HH:HM:LL:LL:LL:^ 
fc_CO2e:     __:__:ZZ:LL:HH:HH:HL:LL:__:__:__:__:__:__:__:__:^ 
fcEff_NOy:  __:__:__:__:__:__:__:HH:HH:HM:MM:MM:MM:__:__:__:^ 
;fcEff_NOy:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
fcZer_NOy:   __:__:__:__:__:__:__:__:__:__:__:__:__:__:__:__:^ 
}

routine prf_eff { ; finishes the NOy eff, and profile CO2 cal (H,M,L) adds 2 min pause after cal
SolSt:       PP:PP:PP:PP:PP:PP:PP:^
Lvl1:	     __:__:__:__:__:__:__:^
Lvl2: 	     __:__:__:__:__:__:__:^
Lvl3:        __:__:__:__:__:__:__:^
Lvl4:        __:__:__:__:__:__:__:^
Lvl5:	     __:__:__:__:__:__:__:^
Lvl6:	     __:__:__:__:__:__:__:^
Lvl7:	     __:__:__:__:__:__:__:^
Lvl8:        __:__:__:__:__:__:__:^
eCO2cal:     __:__:__:__:__:__:__:^
CO2add1:     __:__:__:__:__:__:__:^
CO2add2:     __:__:__:__:__:__:__:^
CO_smpl:     __:__:__:__:__:__:__:^
CO_cal1:     __:__:__:__:__:__:__:^
CO_cal2:     __:__:__:__:__:__:__:^
CO_zer:      OO:OO:OO:__:__:__:__:^
eff_Hg:      OO:OO:OO:__:__:__:__:^
zNOy_Hg:     __:__:__:__:__:__:__:^
NPN_on:      __:__:__:__:__:__:__:^
NO_NOy_on:   OO:OO:OO:__:__:__:__:^
NO_NOy_add:  OO:OO:OO:__:__:__:__:^
NPN_add:     __:__:__:__:__:__:__:^
NOy_eff_add: OO:OO:OO:__:__:__:__:^
zNOy_add:    __:__:__:__:__:__:__:^
zNOx_Hg:     __:__:__:__:__:__:__:^
NO_NOx_on:   __:__:__:__:__:__:__:^
NO2_on:      __:__:__:__:__:__:__:^
zNOx_add:    __:__:__:__:__:__:__:^
NO_NOx_add:  __:__:__:__:__:__:__:^
NO2_add:     __:__:__:__:__:__:__:^
;NO2_add:     __:__:__:__:__:__:__:^
Shutter:     __:__:__:__:__:__:__:^
pCO2_smpl:   OO:OO:OO:OO:OO:OO:__:^
pCO2_cal1:   __:__:__:__:OO:OO:__:^
pCO2_cal2:   __:__:OO:OO:__:__:__:^
pCO2_cal3:   OO:OO:__:__:__:__:__:^
pCO2_cala:   __:__:__:__:__:__:__:^
pCO2_calR:   __:__:__:__:__:__:__:^
Shk_sp1:     __:__:__:__:__:_O:OO:^
Hub_sp2:     __:__:__:__:__:__:__:^ 
fcNO_NOx:    __:__:__:__:__:__:__:^ 
fcNO2_NOx:   __:__:__:__:__:__:__:^ 
fc_CO2e:     __:__:__:__:__:__:__:^ 
fcNO_NOy:    LL:LL:LL:__:__:__:__:^ 
fcEff_NOy:   __:__:__:__:__:__:__:^ 
fcZer_NOy:   __:__:__:__:__:_M:MM:^ 
}

routine Cal { ; does the NOx/NOy calibrations
SolSt:     LL:LL:LL:LL:LL:LL:LL:LL:LL:^
Lvl1:	     __:__:__:__:__:__:__:__:__:^
Lvl2:	     __:__:__:__:__:__:__:__:__:^
Lvl3:        __:__:__:__:__:__:__:__:__:^
Lvl4:        __:__:__:__:__:__:__:__:__:^
Lvl5:	     __:__:__:__:__:__:__:__:__:^
Lvl6:	     __:__:__:__:__:__:__:__:__:^
Lvl7:	     __:__:__:__:__:__:__:__:__:^
Lvl8:       __:__:__:__:__:__:__:__:__:^
eCO2cal:     __:__:__:__:__:__:__:__:__:^
CO2add1:     __:__:__:__:__:__:__:__:__:^
CO2add2:     __:__:__:__:__:__:__:__:__:^
CO_smpl:     __:__:__:__:__:__:__:__:__:^
CO_cal1:     __:__:__:__:__:__:__:__:__:^
CO_cal2:     __:__:__:__:__:__:__:__:__:^
CO_zer:      OO:OO:__:__:_O:OO:O_:__:__:^
eff_Hg:      __:__:__:__:__:__:__:__:__:^
zNOy_Hg:     OO:OO:OO:OO:__:__:__:__:__:^
;NO_NOy_on:   __:__:__:__:OO:OO:OO:OO:OO:^
;NPN_on:      __:__:__:__:__:__:__:__:__:^
NPN_on:      __:__:__:__:OO:OO:OO:OO:OO:^
NO_NOy_on:   __:__:__:__:__:__:__:__:__:^
NO_NOy_add:  __:__:__:__:__:__:OO:OO:OO:^
NPN_add:     __:__:__:__:__:__:__:__:__:^
NOy_eff_add: __:__:__:__:__:__:__:__:__:^
zNOy_add:    __:__:OO:OO:__:__:__:__:__:^
zNOx_Hg:     __:__:__:__:__:OO:OO:OO:OO:^
NO_NOx_on:   __:__:__:__:__:__:__:__:__:^
NO2_on:      __:__:__:__:__:__:__:__:__:^
zNOx_add:    __:__:__:__:__:__:__:OO:OO:^
NO_NOx_add:  __:__:__:__:__:__:__:__:__:^
;NO2_add:     __:__:__:__:__:__:__:__:__:^
NO2_add:     __:__:__:__:__:__:__:__:__:^
Shutter:     __:__:__:__:__:__:__:__:__:^
pCO2_smpl:   __:__:__:__:__:__:__:__:__:^
pCO2_cal1:   __:__:__:__:__:__:__:__:__:^
pCO2_cal2:   __:__:__:__:__:__:__:__:__:^
pCO2_cal3:   __:__:__:__:__:__:__:__:__:^
pCO2_cala:   __:__:__:__:__:__:__:__:__:^
pCO2_calR:   __:__:__:__:__:__:__:__:__:^
Shk_sp1:     __:__:__:__:__:__:__:__:__:^
Hub_sp2:     __:__:__:__:__:__:__:__:__:^
fcNO_NOx:    __:__:__:__:__:__:__:__:__:^ 
fcNO2_NOx:   __:__:__:__:__:__:__:__:__:^ 
fc_CO2e:     __:__:__:__:__:__:__:__:__:^ 
fcNO_NOy:    __:__:__:__:HH:HH:MM:MM:MM:^ 
fcEff_NOy:   __:__:__:__:__:__:__:__:__:^ 
fcZer_NOy:   __:__:__:__:__:__:__:__:__:^ 
}

routine Archive_cal { ; does the CO2 archive calibration and checks if Hub has leaks
SolSt:       AA:AA:AA:l^
Lvl1:	     __:__:__:O^
Lvl2:	     __:__:__:_^
Lvl3:        __:__:__:_^
Lvl4:        __:__:__:_^
Lvl5:	     __:__:__:_^
Lvl6:	     __:__:__:_^
Lvl7:	     __:__:__:_^
Lvl8:        __:__:__:_^
eCO2cal:     __:__:__:_^
CO2add1:     __:__:__:_^
CO2add2:     __:__:__:_^
CO_smpl:     __:__:__:_^
CO_cal1:     __:__:__:_^
CO_cal2:     __:__:__:_^
CO_zer:      __:__:__:_^
eff_Hg:      __:__:__:_^
zNOy_Hg:     __:__:__:_^
NO_NOy_on:   __:__:__:_^
NPN_on:      __:__:__:_^
NO_NOy_add:  __:__:__:_^
NPN_add:     __:__:__:_^
NOy_eff_add: __:__:__:_^
zNOy_add:    __:__:__:_^
zNOx_Hg:     __:__:__:_^
NO_NOx_on:   __:__:__:_^
NO2_on:      __:__:__:_^
zNOx_add:    __:__:__:_^
NO_NOx_add:  __:__:__:_^
;NO2_add:     __:__:__:_^
NO2_add:     __:__:__:_^
Shutter:     __:__:__:_^
pCO2_smpl:   OO:OO:__:_^
pCO2_cal1:   __:__:__:_^
pCO2_cal2:   __:__:__:_^
pCO2_cal3:   __:__:__:_^
pCO2_cala:   OO:OO:__:_^
pCO2_calR:   __:__:__:_^
Shk_sp1:     __:__:__:_^
Hub_sp2:     __:__:__:_^
fcNO_NOx:    __:__:^__:_ 
fcNO2_NOx:   __:__:^__:_ 
fc_CO2e:     __:__:^__:_ 
fcNO_NOy:    __:__:^__:_ 
fcEff_NOy:   __:__:^__:_ 
fcZer_NOy:   __:__:^__:_ 
}

routine closeout { ; end with CO and CO2 zeros
SolSt:	        SSSS:^
Lvl1:		____:^
Lvl2:		____:^
Lvl3:		____:^
Lvl4:		____:^
Lvl5:		____:^
Lvl6:		____:^
Lvl7:		____:^
Lvl8:		____:^
eCO2cal:	____:^
CO2add1:	____:^
CO2add2:	____:^
CO_smpl:	____:^
CO_cal1:	____:^
CO_cal2:	____:^
CO_zer:		OOOO:^
eff_Hg:		____:^
zNOy_Hg:	____:^
NO_NOy_on:	____:^
NPN_on:		____:^
NO_NOy_add: 	____:^
NPN_add: 	____:^
NOy_eff_add:	____:^
zNOy_add: 	____:^
zNOx_Hg: 	____:^
NO_NOx_on: 	____:^
NO2_on: 	____:^
zNOx_add: 	____:^
NO_NOx_add: 	____:^
;NO2_add: 	____:^
NO2_add: 	____:^
Shutter: 	____:^
pCO2_smpl: 	OOOO:^
pCO2_cal1: 	____:^
pCO2_cal2: 	____:^
pCO2_cal3: 	____:^
pCO2_cala: 	____:^
pCO2_calR: 	OOOO:^
Shk_sp1: 	____:^ 
Hub_sp2: 	____:^ 
fcNO_NOx: 	____:^ 
fcNO2_NOx: 	____:^ 
fc_CO2e: 	____:^ 
fcNO_NOy: 	____:^ 
fcEff_NOy: 	____:^ 
fcZer_NOy: 	____:^ 
}

Mode 0 { ; Stop mode
SolSt: 1
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
  pCO2_smpl: _
  pCO2_cal1: _
  pCO2_cal2: _
  pCO2_cal3: _
  pCO2_cala: _
  pCO2_calR: _
  Shk_sp1:   _
  Hub_sp2:   _
fcNO_NOx: _
fcNO2_NOx: _
fc_CO2e: _
fcNO_NOy: _
fcEff_NOy: _
fcZer_NOy: _
}

Mode 2 {	; operation cycle with sonic heater on
Sample_melt		;36 min - 36
Sample_melt		;36 min - 72
Sample_melt		;36 min - 108
Sample_melt		;36 min
;Cal		;18 min - 126 cumulative
SampleZ		;36 min - 162
Sample		;36 min	- 198
Sample		;36 min - 234
Sample		;36 min
;Ecal		;30 min - 264
Sample		;36 min - 300
Sample		;36 min - 336
Sample		;36 min - 372
Sample		;36 min - 408
;Cal		;18 min - 426
SampleZ		;36 min - 462
Sample		;36 min - 498
Sample		;36 min - 534
Select 3
}

Mode 3 {	; Routine startup mode
Sample		; 36 min
ECcal		; 30 min
prf_eff		; 12 min
Select 4	; go to operation cycle 534/612
}

Mode 4 {	; operation cycle
Sample		;36 min - 36
Sample		;36 min - 72
Sample		;36 min - 108
Sample		;36 min
;Cal		;18 min - 126 cumulative
SampleZ		;36 min - 162
Sample		;36 min	- 198
Sample		;36 min - 234
Sample		;36 min
;Ecal		;30 min - 264
Sample		;36 min - 300
Sample		;36 min - 336
Sample		;36 min - 372
Sample		;36 min - 408

;Cal		;18 min - 426
SampleZ		;36 min - 462
Sample		;36 min - 498
Sample		;36 min - 534
Select 3
}

Mode 5 {   ; Termination Mode
  ECcal
  Select 0 ; Goto Stop Mode
}

Mode 7 { ; abbreviated termination mode
     closeout
     Select 0 ; stopping mode
}

Mode 8 { ; shutdown mode including a CO2 archive calibration
	Archive_cal
	Select 7
}
