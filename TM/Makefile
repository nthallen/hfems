# Makefile Generated Mon Apr 09 20:38:16 UTC 2012
MNC=HFEMS
HOMEDIR=/home/hfems/src/TM
SPECFILE=HFEMS.spec
SRC=a2b.c a2bnew.c a2b HFEMS.fld sonic.h a2b10hz.c types.tmc
SRC+=HFEMS.tmc HFEMScol.tmc HFEMS.cmd HFEMS.doit HFEMS.tbl HFEMS.sol
SRC+=HFEMS.tma HFEMSall.cdf
TOOL=HFEMS.spec Makefile
SCRIPT=interact HFEMS.dccc
OBJ=address.h HFEMScol.cc HFEMS.pcm tm.dac HFEMScoloui.c
OBJ+=HFEMScoloui.o HFEMScol.o HFEMScmd.cc HFEMScmd.dat HFEMSsrvr.o
OBJ+=HFEMSsrvroui.c HFEMSsrvroui.o HFEMSdoit.dep HFEMStbl.tmc
OBJ+=HFEMSdisp.cc HFEMSdispoui.c HFEMSdispoui.o HFEMSdisp.o
OBJ+=HFEMStblnc.tmc HFEMSdispnc.cc HFEMSdispncoui.c HFEMSdispncoui.o
OBJ+=HFEMSdispnc.o HFEMSalgoa.tmc HFEMSalgo.cc HFEMSalgooui.c
OBJ+=HFEMSalgooui.o HFEMSalgo.o HFEMSallextcdf.oui HFEMSallext.tmc
OBJ+=HFEMSallext.cc HFEMSallextoui.c HFEMSallextoui.o HFEMSallext.o
OBJ+=HFEMSclt.o HFEMScltoui.c HFEMScltoui.o HFEMScltnc.o
OBJ+=HFEMScltncoui.c HFEMScltncoui.o
TGT=HFEMScol HFEMSsrvr HFEMSdoit HFEMSdisp HFEMSdispnc HFEMS.sft
TGT+=HFEMSalgo HFEMSallext HFEMSclt HFEMScltnc
DISTRIB=HFEMS.sft ../sonic/Sonic HFEMS.pcm tm.dac
IDISTRIB=Experiment.config VERSION HFEMS_autorun HFEMSdoit
SRCDIST=HFEMS.tbl HFEMS.sol HFEMS.tma types.tmc HFEMS.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
NONRCS=
TMCBASE=types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
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
HFEMSsrvr : HFEMSsrvr.o HFEMSsrvroui.o
	$(LINK.privCXX) HFEMSsrvr.o HFEMSsrvroui.o -lsubbus -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSsrvroui.c
	$(PROMOTE) HFEMSsrvr
HFEMSdoit : HFEMS.doit
	mkdoit3 -o HFEMSdoit  HFEMS.doit
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
HFEMSallext : HFEMSallext.o HFEMSallextoui.o
	$(LINK.normCXX) HFEMSallext.o HFEMSallextoui.o -ltmpp -ltm -lnort
	$(OUIUSE) HFEMSallextoui.c
HFEMSclt : HFEMSclt.o HFEMScltoui.o
	$(LINK.normCXX) HFEMSclt.o HFEMScltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScltoui.c
HFEMScltnc : HFEMScltnc.o HFEMScltncoui.o
	$(LINK.normCXX) HFEMScltnc.o HFEMScltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) HFEMScltncoui.c
HFEMScol.cc : types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMScol.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
	$(TMC.col) types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMScol.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
HFEMScoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HFEMScoloui.o : HFEMScoloui.c
HFEMScol.o : HFEMScol.cc
HFEMScmd.cc : /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd
	$(CMDGEN) -d HFEMScmd.dat /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd
HFEMSsrvr.o : HFEMScmd.cc
	$(COMPILE.srvr) HFEMScmd.cc
HFEMSsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HFEMSsrvroui.o : HFEMSsrvroui.c
HFEMSdoit.dep : HFEMS.doit
	mkdoit3 -M -o HFEMSdoit  HFEMS.doit
-include HFEMSdoit.dep
HFEMStbl.tmc : HFEMS.tbl
	$(TABLE) HFEMS.tbl
HFEMSdisp.cc : types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMStbl.tmc
	$(TMC) types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMStbl.tmc
HFEMSdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispoui.o : HFEMSdispoui.c
HFEMSdisp.o : HFEMSdisp.cc
HFEMStblnc.tmc : HFEMS.tbl
	$(NCTABLE) HFEMS.tbl
HFEMSdispnc.cc : types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMStblnc.tmc
	$(TMC) types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMStblnc.tmc
HFEMSdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispncoui.o : HFEMSdispncoui.c
HFEMSdispnc.o : HFEMSdispnc.cc
HFEMSalgoa.tmc : HFEMS.tma HFEMSsrvr
	$(SERVER) ./HFEMSsrvr
	$(TMCALGO) -V "`./HFEMSsrvr -R`" HFEMS.tma
HFEMSalgo.cc : types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMSalgoa.tmc
	$(TMC) types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMSalgoa.tmc
HFEMSalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSalgooui.o : HFEMSalgooui.c
HFEMSalgo.o : HFEMSalgo.cc
HFEMSallextcdf.oui : HFEMSall.cdf
	$(EDF2OUI) HFEMSall.cdf
HFEMSallext.tmc : HFEMSall.cdf
	$(EDF2EXT) HFEMSall.cdf
HFEMSallext.cc : types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMSallext.tmc
	$(TMC) types.tmc HFEMS.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc HFEMSallext.tmc
HFEMSallextoui.c : HFEMSallextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) HFEMSallextcdf.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSallextoui.o : HFEMSallextoui.c
HFEMSallext.o : HFEMSallext.cc
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

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
CPPFLAGS+=-I../sonic
COLFLAGS=-Haddress.h
address.h : HFEMScol.cc
HFEMSsrvr.o : address.h
CYCLE=cycle > $@
