# Makefile Generated Wed Oct 12 12:07:10 EDT 2011
MNC=HFEMS
HOMEDIR=/home/hfems/src
SPECFILE=HFEMS.spec
SRC=a2b.c a2bnew.c a2b HFEMSo.fld sonic.h a2b10hz.c timeout.c
SRC+=timeoutoui.c devwatch.c devwatch.h devwatch.oui types.tmc
SRC+=HFEMS.tmc HFEMSgrp.tmc HFEMScol.tmc HFEMS.doit sonic.c
SRC+=HFEMSmux.tmc HFEMS.tbl HFEMS.sol HFEMS.tma temps_2.edf
SRC+=temps_2.tmc temps_2b.edf eddy.edf e_ted.edf ext_4.edf ext_5.edf
SRC+=ext_rh.edf noxc.edf quick.edf HFEMS.cyc HFEMScycle.tmc HFEMS.cmd
TOOL=HFEMS.spec Makefile
SCRIPT=HFEMStmc.prt HFEMS.ag interact *.xnp temps.edf o3_adj
SCRIPT+=tempsext.tmc tempsext *.edf hf_interact hf_saverun hf_clean
SCRIPT+=HFEMS.dccc Experiment.config HFEMS.cfg readme.changes
SCRIPT+=clear_all standards.record
OBJ=HFEMScol.cc HFEMS.pcm tm.dac HFEMScoloui.c HFEMScoloui.o
OBJ+=HFEMScol.o HFEMSdoit.dep sonicoui.c sonic.o sonicoui.o
OBJ+=HFEMStbl.tmc HFEMSdisp.cc HFEMSdispoui.c HFEMSdispoui.o
OBJ+=HFEMSdisp.o HFEMStblnc.tmc HFEMSdispnc.cc HFEMSdispncoui.c
OBJ+=HFEMSdispncoui.o HFEMSdispnc.o HFEMSalgoa.tmc HFEMSalgo.cc
OBJ+=HFEMSalgooui.c HFEMSalgooui.o HFEMSalgo.o temps_2extedf.oui
OBJ+=temps_2ext.tmc temps_2ext.cc temps_2extoui.c temps_2extoui.o
OBJ+=temps_2ext.o temps_2bextedf.oui temps_2bext.tmc temps_2bext.cc
OBJ+=temps_2bextoui.c temps_2bextoui.o temps_2bext.o eddyextedf.oui
OBJ+=eddyext.tmc eddyext.cc eddyextoui.c eddyextoui.o eddyext.o
OBJ+=e_tedextedf.oui e_tedext.tmc e_tedext.cc e_tedextoui.c
OBJ+=e_tedextoui.o e_tedext.o ext_4extedf.oui ext_4ext.tmc
OBJ+=ext_4ext.cc ext_4extoui.c ext_4extoui.o ext_4ext.o
OBJ+=ext_5extedf.oui ext_5ext.tmc ext_5ext.cc ext_5extoui.c
OBJ+=ext_5extoui.o ext_5ext.o ext_rhextedf.oui ext_rhext.tmc
OBJ+=ext_rhext.cc ext_rhextoui.c ext_rhextoui.o ext_rhext.o
OBJ+=noxcextedf.oui noxcext.tmc noxcext.cc noxcextoui.c noxcextoui.o
OBJ+=noxcext.o quickextedf.oui quickext.tmc quickext.cc quickextoui.c
OBJ+=quickextoui.o quickext.o HFEMScyc.tmc cycleext.cc cycleextoui.c
OBJ+=cycleextoui.o cycleext.o HFEMScmd.cc HFEMScmd.dat HFEMSclt.o
OBJ+=HFEMScltoui.c HFEMScltoui.o HFEMScltnc.o HFEMScltncoui.c
OBJ+=HFEMScltncoui.o HFEMSsrvr.o HFEMSsrvroui.c HFEMSsrvroui.o
TGT=HFEMScol HFEMSdoit sonic HFEMSdisp HFEMSdispnc HFEMS.sft
TGT+=HFEMSalgo temps_2ext temps_2bext eddyext e_tedext ext_4ext
TGT+=ext_5ext ext_rhext noxcext quickext cycleext HFEMSclt HFEMScltnc
TGT+=HFEMSsrvr
DISTRIB=HFEMS.pcm tm.dac
IDISTRIB=Experiment.config VERSION HFEMSdoit
SRCDIST=HFEMS.tbl HFEMS.sol HFEMS.tma types.tmc HFEMS.tmc
SRCDIST+=HFEMSgrp.tmc
NONRCS=
TMCBASE=types.tmc HFEMS.tmc HFEMSgrp.tmc
CMDBASE=HFEMS.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= /home/HFEMS
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : HFEMS.spec
	appgen HFEMS.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
HFEMScol : HFEMScol.o HFEMScoloui.o
	$(LINK.privCXX) HFEMScol.o HFEMScoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScoloui.c
	$(PROMOTE) HFEMScol
HFEMSdoit : HFEMS.doit
	mkdoit3 -o HFEMSdoit  HFEMS.doit
sonic : sonic.o sonicoui.o
	$(LINK.norm) sonic.o sonicoui.o -ltm -lnort
	$(OUIUSE) sonicoui.c
HFEMSdisp : HFEMSdisp.o HFEMSdispoui.o
	$(LINK.normCXX) HFEMSdisp.o HFEMSdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSdispoui.c
HFEMSdispnc : HFEMSdispnc.o HFEMSdispncoui.o
	$(LINK.normCXX) HFEMSdispnc.o HFEMSdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSdispncoui.c
HFEMS.sft : HFEMS.sol
	solfmt -oHFEMS.sft  HFEMS.sol
HFEMSalgo : HFEMSalgo.o HFEMSalgooui.o
	$(LINK.normCXX) HFEMSalgo.o HFEMSalgooui.o -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSalgooui.c
temps_2ext : temps_2ext.o temps_2extoui.o
	$(LINK.normCXX) temps_2ext.o temps_2extoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) temps_2extoui.c
temps_2bext : temps_2bext.o temps_2bextoui.o
	$(LINK.normCXX) temps_2bext.o temps_2bextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) temps_2bextoui.c
eddyext : eddyext.o eddyextoui.o
	$(LINK.normCXX) eddyext.o eddyextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) eddyextoui.c
e_tedext : e_tedext.o e_tedextoui.o
	$(LINK.normCXX) e_tedext.o e_tedextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) e_tedextoui.c
ext_4ext : ext_4ext.o ext_4extoui.o
	$(LINK.normCXX) ext_4ext.o ext_4extoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) ext_4extoui.c
ext_5ext : ext_5ext.o ext_5extoui.o
	$(LINK.normCXX) ext_5ext.o ext_5extoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) ext_5extoui.c
ext_rhext : ext_rhext.o ext_rhextoui.o
	$(LINK.normCXX) ext_rhext.o ext_rhextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) ext_rhextoui.c
noxcext : noxcext.o noxcextoui.o
	$(LINK.normCXX) noxcext.o noxcextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) noxcextoui.c
quickext : quickext.o quickextoui.o
	$(LINK.normCXX) quickext.o quickextoui.o -ltmpp -ltm -lssp -lmem -lm -lnort
	$(OUIUSE) quickextoui.c
cycleext : cycleext.o cycleextoui.o
	$(LINK.normCXX) cycleext.o cycleextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) cycleextoui.c
HFEMSclt : HFEMSclt.o HFEMScltoui.o
	$(LINK.normCXX) HFEMSclt.o HFEMScltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScltoui.c
HFEMScltnc : HFEMScltnc.o HFEMScltncoui.o
	$(LINK.normCXX) HFEMScltnc.o HFEMScltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScltncoui.c
HFEMSsrvr : HFEMSsrvr.o HFEMSsrvroui.o
	$(LINK.privCXX) HFEMSsrvr.o HFEMSsrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSsrvroui.c
	$(PROMOTE) HFEMSsrvr
HFEMScol.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMScol.tmc
	$(TMC.col) types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMScol.tmc
HFEMScoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
HFEMScoloui.o : HFEMScoloui.c
HFEMScol.o : HFEMScol.cc
HFEMSdoit.dep : HFEMS.doit
	mkdoit3 -M -o HFEMSdoit  HFEMS.doit
-include HFEMSdoit.dep
sonicoui.c : $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/msg.oui
sonic.o : sonic.c
sonicoui.o : sonicoui.c
HFEMStbl.tmc : HFEMS.tbl
	$(TABLE) HFEMS.tbl
HFEMSdisp.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc HFEMStbl.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc HFEMStbl.tmc
HFEMSdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispoui.o : HFEMSdispoui.c
HFEMSdisp.o : HFEMSdisp.cc
HFEMStblnc.tmc : HFEMS.tbl
	$(NCTABLE) HFEMS.tbl
HFEMSdispnc.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc HFEMStblnc.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc HFEMStblnc.tmc
HFEMSdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispncoui.o : HFEMSdispncoui.c
HFEMSdispnc.o : HFEMSdispnc.cc
HFEMSalgoa.tmc : HFEMS.tma HFEMSsrvr
	$(SERVER) ./HFEMSsrvr
	$(TMCALGO) -V "`./HFEMSsrvr -R`" HFEMS.tma
HFEMSalgo.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSalgoa.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSalgoa.tmc
HFEMSalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSalgooui.o : HFEMSalgooui.c
HFEMSalgo.o : HFEMSalgo.cc
temps_2extedf.oui : temps_2.edf
	$(EDF2OUI) temps_2.edf
temps_2ext.tmc : temps_2.edf
	$(EDF2EXT) temps_2.edf
temps_2ext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc temps_2ext.tmc temps_2.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc HFEMSmux.tmc temps_2ext.tmc temps_2.tmc
temps_2extoui.c : temps_2extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) temps_2extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
temps_2extoui.o : temps_2extoui.c
temps_2ext.o : temps_2ext.cc
temps_2bextedf.oui : temps_2b.edf
	$(EDF2OUI) temps_2b.edf
temps_2bext.tmc : temps_2b.edf
	$(EDF2EXT) temps_2b.edf
temps_2bext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc temps_2bext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc temps_2bext.tmc
temps_2bextoui.c : temps_2bextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) temps_2bextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
temps_2bextoui.o : temps_2bextoui.c
temps_2bext.o : temps_2bext.cc
eddyextedf.oui : eddy.edf
	$(EDF2OUI) eddy.edf
eddyext.tmc : eddy.edf
	$(EDF2EXT) eddy.edf
eddyext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc eddyext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc eddyext.tmc
eddyextoui.c : eddyextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) eddyextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
eddyextoui.o : eddyextoui.c
eddyext.o : eddyext.cc
e_tedextedf.oui : e_ted.edf
	$(EDF2OUI) e_ted.edf
e_tedext.tmc : e_ted.edf
	$(EDF2EXT) e_ted.edf
e_tedext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc e_tedext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc e_tedext.tmc
e_tedextoui.c : e_tedextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) e_tedextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
e_tedextoui.o : e_tedextoui.c
e_tedext.o : e_tedext.cc
ext_4extedf.oui : ext_4.edf
	$(EDF2OUI) ext_4.edf
ext_4ext.tmc : ext_4.edf
	$(EDF2EXT) ext_4.edf
ext_4ext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc ext_4ext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc ext_4ext.tmc
ext_4extoui.c : ext_4extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ext_4extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ext_4extoui.o : ext_4extoui.c
ext_4ext.o : ext_4ext.cc
ext_5extedf.oui : ext_5.edf
	$(EDF2OUI) ext_5.edf
ext_5ext.tmc : ext_5.edf
	$(EDF2EXT) ext_5.edf
ext_5ext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc ext_5ext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc ext_5ext.tmc
ext_5extoui.c : ext_5extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ext_5extedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ext_5extoui.o : ext_5extoui.c
ext_5ext.o : ext_5ext.cc
ext_rhextedf.oui : ext_rh.edf
	$(EDF2OUI) ext_rh.edf
ext_rhext.tmc : ext_rh.edf
	$(EDF2EXT) ext_rh.edf
ext_rhext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc ext_rhext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc ext_rhext.tmc
ext_rhextoui.c : ext_rhextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) ext_rhextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
ext_rhextoui.o : ext_rhextoui.c
ext_rhext.o : ext_rhext.cc
noxcextedf.oui : noxc.edf
	$(EDF2OUI) noxc.edf
noxcext.tmc : noxc.edf
	$(EDF2EXT) noxc.edf
noxcext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc noxcext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc noxcext.tmc
noxcextoui.c : noxcextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) noxcextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
noxcextoui.o : noxcextoui.c
noxcext.o : noxcext.cc
quickextedf.oui : quick.edf
	$(EDF2OUI) quick.edf
quickext.tmc : quick.edf
	$(EDF2EXT) quick.edf
quickext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc quickext.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc quickext.tmc
quickextoui.c : quickextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) quickextedf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
quickextoui.o : quickextoui.c
quickext.o : quickext.cc
HFEMScyc.tmc : HFEMS.cyc
	$(CYCLE) HFEMS.cyc
cycleext.cc : types.tmc HFEMS.tmc HFEMSgrp.tmc /usr/local/lib/src/flttime.tmc HFEMScyc.tmc HFEMScycle.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMSgrp.tmc /usr/local/lib/src/flttime.tmc HFEMScyc.tmc HFEMScycle.tmc
cycleextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
cycleextoui.o : cycleextoui.c
cycleext.o : cycleext.cc
HFEMScmd.cc : HFEMS.cmd
	$(CMDGEN) -d HFEMScmd.dat HFEMS.cmd
HFEMSclt.o : HFEMScmd.cc
	$(COMPILE.clt) HFEMScmd.cc
HFEMScltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
HFEMScltoui.o : HFEMScltoui.c
HFEMScltnc.o : HFEMScmd.cc
	$(COMPILE.cltnc) HFEMScmd.cc
HFEMScltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
HFEMScltncoui.o : HFEMScltncoui.c
HFEMSsrvr.o : HFEMScmd.cc
	$(COMPILE.srvr) HFEMScmd.cc
HFEMSsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
HFEMSsrvroui.o : HFEMSsrvroui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
HFEMSdoit : HFEMS.fld
CYCLE=cycle > $@
