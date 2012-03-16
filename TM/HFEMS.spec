tmcbase = types.tmc HFEMS.tmc

cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = HFEMS.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd

SCRIPT = interact
SCRIPT = HFEMS.dccc
DISTRIB = HFEMS.sft ../sonic/Sonic

SRC = a2b.c a2bnew.c a2b HFEMS.fld sonic.h a2b10hz.c 
#SRC = timeout.c timeoutoui.c devwatch.c devwatch.h devwatch.oui
#SCRIPT = start_job prfjobs runeddy end_job fix_set VERSION get_data
#SCRIPT = core.set.env core.set.env.bak
#SCRIPT = interact *.xnp temps.edf o3_adj tempsext.tmc tempsext *.edf 
#SCRIPT = hf_interact hf_saverun hf_clean
#SCRIPT = HFEMS.dccc Experiment.config HFEMS.cfg readme.changes
#SCRIPT = clear_all standards.record
TGTDIR = $(TGTNODE)/home/hfems
OBJ = address.h

HFEMScol : HFEMScol.tmc -lsubbus
HFEMSsrvr : -lsubbus
HFEMSdoit : HFEMS.doit
#sonic : sonic.c
HFEMSdisp : HFEMS.tbl
HFEMS.sft : HFEMS.sol
HFEMSalgo : HFEMS.tma
#cycleext : /usr/local/share/huarp/flttime.tmc HFEMS.cyc HFEMScycle.tmc 

HFEMSeddyext : HFEMSeddy.edf
# HFEMSext2ext : HFEMSext2.edf

%%
CPPFLAGS+=-I../sonic
COLFLAGS=-Haddress.h
address.h : HFEMScol.cc
HFEMSsrvr.o : address.h
CYCLE=cycle > $@
