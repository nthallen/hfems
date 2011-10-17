tmcbase = types.tmc HFEMS.tmc
cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = HFEMS.cmd
cmdbase = /usr/local/share/huarp/phrtg.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd

SRC = a2b.c a2bnew.c a2b HFEMS.fld sonic.h a2b10hz.c 
#SRC = timeout.c timeoutoui.c devwatch.c devwatch.h devwatch.oui
#SCRIPT = start_job prfjobs runeddy end_job fix_set VERSION get_data
#SCRIPT = core.set.env core.set.env.bak
SCRIPT = interact *.xnp temps.edf o3_adj tempsext.tmc tempsext *.edf 
SCRIPT = hf_interact hf_saverun hf_clean
SCRIPT = HFEMS.dccc Experiment.config HFEMS.cfg readme.changes
SCRIPT = clear_all standards.record
TGTDIR = $(TGTNODE)/home/hfems

HFEMScol : HFEMScol.tmc -lsubbus
#HFEMSdoit : HFEMS.doit
#sonic : sonic.c
HFEMSdisp : HFEMS.tbl
HFEMS.sft : HFEMS.sol
#HFEMSalgo : HFEMS.tma
#eddyext : eddy.edf
#e_tedext : e_ted.edf
#ext_4ext : ext_4.edf
#ext_5ext : ext_5.edf
#ext_rhext : ext_rh.edf
#noxcext : noxc.edf
#quickext : quick.edf
cycleext : /usr/local/lib/src/flttime.tmc HFEMS.cyc HFEMScycle.tmc 
%%
HFEMSdoit : HFEMS.fld
CYCLE=cycle > $@
