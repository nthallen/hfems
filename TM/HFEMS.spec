tmcbase = types.tmc
tmcbase = HFEMS.tmc
tmcbase = tdrift.tmc
tmcbase = /usr/local/share/huarp/cpu_usage.tmc
tmcbase = /usr/local/share/huarp/tmdf.tmc
tmcbase = /usr/local/share/huarp/flttime.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = HFEMS.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd

SCRIPT = interact 
SCRIPT = HFEMS.dccc
DISTRIB = HFEMS.sft ../sonic/Sonic 
IDISTRIB = HFEMS_autorun

TGTDIR = $(TGTNODE)/home/hfems
OBJ = address.h

HFEMScol : HFEMScol.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc -lsubbus
HFEMSsrvr : -lsubbus
HFEMSdoit : HFEMS.doit
#sonic : sonic.c
HFEMSdisp : HFEMS.tbl
HFEMS.sft : HFEMS.sol
HFEMSalgo : HFEMS.tma
#cycleext : /usr/local/share/huarp/flttime.tmc HFEMS.cyc HFEMScycle.tmc 

HFEMSallext : HFEMSall.cdf

%%
CPPFLAGS+=-I../sonic
COLFLAGS=-Haddress.h
address.h : HFEMScol.cc
HFEMSsrvr.o : address.h
CYCLE=cycle > $@
