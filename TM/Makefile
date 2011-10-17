# Makefile Generated Mon Oct 17 08:49:46 EDT 2011
MNC=HFEMS
HOMEDIR=/home/hfems/src/TM
SPECFILE=HFEMS.spec
SRC=a2b.c a2bnew.c a2b HFEMS.fld sonic.h a2b10hz.c types.tmc
SRC+=HFEMS.tmc HFEMScol.tmc HFEMS.tbl HFEMS.sol HFEMS.cyc
SRC+=HFEMScycle.tmc HFEMS.cmd
TOOL=HFEMS.spec Makefile
SCRIPT=interact *.xnp temps.edf o3_adj tempsext.tmc tempsext *.edf
SCRIPT+=hf_interact hf_saverun hf_clean HFEMS.dccc Experiment.config
SCRIPT+=HFEMS.cfg readme.changes clear_all standards.record
OBJ=HFEMScol.cc HFEMS.pcm tm.dac HFEMScoloui.c HFEMScoloui.o
OBJ+=HFEMScol.o HFEMStbl.tmc HFEMSdisp.cc HFEMSdispoui.c
OBJ+=HFEMSdispoui.o HFEMSdisp.o HFEMStblnc.tmc HFEMSdispnc.cc
OBJ+=HFEMSdispncoui.c HFEMSdispncoui.o HFEMSdispnc.o HFEMScyc.tmc
OBJ+=cycleext.cc cycleextoui.c cycleextoui.o cycleext.o HFEMScmd.cc
OBJ+=HFEMScmd.dat HFEMSclt.o HFEMScltoui.c HFEMScltoui.o HFEMScltnc.o
OBJ+=HFEMScltncoui.c HFEMScltncoui.o HFEMSsrvr.o HFEMSsrvroui.c
OBJ+=HFEMSsrvroui.o
TGT=HFEMScol HFEMSdisp HFEMSdispnc HFEMS.sft cycleext HFEMSclt
TGT+=HFEMScltnc HFEMSsrvr
DISTRIB=HFEMS.pcm tm.dac
IDISTRIB=Experiment.config VERSION
SRCDIST=HFEMS.tbl HFEMS.sol types.tmc HFEMS.tmc
NONRCS=
TMCBASE=types.tmc HFEMS.tmc
CMDBASE=/usr/local/share/huarp/root.cmd HFEMS.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/hfems
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
	$(LINK.privCXX) HFEMScol.o HFEMScoloui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScoloui.c
	$(PROMOTE) HFEMScol
HFEMSdisp : HFEMSdisp.o HFEMSdispoui.o
	$(LINK.normCXX) HFEMSdisp.o HFEMSdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSdispoui.c
HFEMSdispnc : HFEMSdispnc.o HFEMSdispncoui.o
	$(LINK.normCXX) HFEMSdispnc.o HFEMSdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSdispncoui.c
HFEMS.sft : HFEMS.sol
	solfmt -oHFEMS.sft  HFEMS.sol
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
HFEMScol.cc : types.tmc HFEMS.tmc HFEMScol.tmc
	$(TMC.col) types.tmc HFEMS.tmc HFEMScol.tmc
HFEMScoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HFEMScoloui.o : HFEMScoloui.c
HFEMScol.o : HFEMScol.cc
HFEMStbl.tmc : HFEMS.tbl
	$(TABLE) HFEMS.tbl
HFEMSdisp.cc : types.tmc HFEMS.tmc HFEMStbl.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMStbl.tmc
HFEMSdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispoui.o : HFEMSdispoui.c
HFEMSdisp.o : HFEMSdisp.cc
HFEMStblnc.tmc : HFEMS.tbl
	$(NCTABLE) HFEMS.tbl
HFEMSdispnc.cc : types.tmc HFEMS.tmc HFEMStblnc.tmc
	$(TMC) types.tmc HFEMS.tmc HFEMStblnc.tmc
HFEMSdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispncoui.o : HFEMSdispncoui.c
HFEMSdispnc.o : HFEMSdispnc.cc
HFEMScyc.tmc : HFEMS.cyc
	$(CYCLE) HFEMS.cyc
cycleext.cc : types.tmc HFEMS.tmc /usr/local/lib/src/flttime.tmc HFEMScyc.tmc HFEMScycle.tmc
	$(TMC) types.tmc HFEMS.tmc /usr/local/lib/src/flttime.tmc HFEMScyc.tmc HFEMScycle.tmc
cycleextoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
cycleextoui.o : cycleextoui.c
cycleext.o : cycleext.cc
HFEMScmd.cc : /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd
	$(CMDGEN) -d HFEMScmd.dat /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd
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
