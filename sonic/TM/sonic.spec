tmcbase = sonic.tmc
cmdbase = /usr/local/share/huarp/root.cmd
cmdbase = /usr/local/share/huarp/getcon.cmd
TGTDIR = $(TGTNODE)/home/Sonic
DISTRIB = ../Sonic
SCRIPT = interact
soniccol :
sonicdisp : sonic.tbl
doit : sonic.doit
%%
CPPFLAGS+=-I ../