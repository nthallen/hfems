# Makefile Generated Wed Dec 02 11:24:08 EST 2015
MNC=HFEMS
SPECFILE=HFEMS.spec
PCMFILE=HFEMS.pcm
SRC=types.tmc HFEMS.tmc tdrift.tmc HFEMScol.tmc tdrift_col.tmc
SRC+=HFEMS.cmd cmdenbl.cmd HFEMS.doit HFEMS.tbl HFEMS.sol HFEMS.tma
SRC+=HFEMSall.cdf
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
IDISTRIB=Experiment.config VERSION HFEMS_autorun HFEMS_show
IDISTRIB+=HFEMSdoit
SRCDIST=HFEMS.tbl HFEMS.sol HFEMS.tma types.tmc HFEMS.tmc tdrift.tmc
SRCDIST+=/usr/local/share/huarp/cpu_usage.tmc
SRCDIST+=/usr/local/share/huarp/tmdf.tmc
SRCDIST+=/usr/local/share/huarp/flttime.tmc
TMCBASE=types.tmc HFEMS.tmc tdrift.tmc
TMCBASE+=/usr/local/share/huarp/cpu_usage.tmc
TMCBASE+=/usr/local/share/huarp/tmdf.tmc
TMCBASE+=/usr/local/share/huarp/flttime.tmc
CMDBASE=/usr/local/share/huarp/root.cmd HFEMS.cmd
CMDBASE+=/usr/local/share/huarp/phrtg.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd cmdenbl.cmd
COLBASE=
SWSBASE=
QCLIBASE=
PHTGT=HFEMStbl.tmc
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/hfems
include /usr/local/share/huarp/appgen.mk

.PHONY : all extdistribution distribution clean check_photon

all : Makefile check_photon $(TGT) .cvsignore
Makefile : HFEMS.spec
	appgen HFEMS.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST) VERSION
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@[ ! -f $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) ] || \
	  cmp -s $(TGTDIR)/bin/$(VERSION)/$(PCMFILE) $(PCMFILE) || \
	  ( echo "$(PCMFILE) changed without VERSION update"; false )
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
check_photon :
ifeq ($(WPHOTON),YES)
	@for tgt in $(PHTGT); do \
	  cmp -s $$tgt /usr/local/share/huarp/nulltbl.tmc && echo Remaking $$tgt && rm -f $$tgt; \
	done; true
endif
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
HFEMScol.cc : types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMScol.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
	$(TMC.col) types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMScol.tmc tdrift_col.tmc /usr/local/share/huarp/cpu_usage_col.tmc /usr/local/share/huarp/tmdf_col.tmc
HFEMScoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HFEMScoloui.o : HFEMScoloui.c
HFEMScol.o : HFEMScol.cc
HFEMScmd.cc : /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd cmdenbl.cmd
	$(CMDGEN) -d HFEMScmd.dat /usr/local/share/huarp/root.cmd HFEMS.cmd /usr/local/share/huarp/phrtg.cmd /usr/local/share/huarp/getcon.cmd cmdenbl.cmd
HFEMSsrvr.o : HFEMScmd.cc
	$(COMPILE.srvr) HFEMScmd.cc
HFEMSsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/subbus.oui $(OUIDIR)/msg.oui
HFEMSsrvroui.o : HFEMSsrvroui.c
HFEMSdoit.dep : HFEMS.doit
	mkdoit3 -M -o HFEMSdoit  HFEMS.doit
-include HFEMSdoit.dep
HFEMStbl.tmc : HFEMS.tbl
HFEMSdisp.cc : types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMStbl.tmc
	$(TMC) types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMStbl.tmc
HFEMSdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispoui.o : HFEMSdispoui.c
HFEMSdisp.o : HFEMSdisp.cc
HFEMStblnc.tmc : HFEMS.tbl
HFEMSdispnc.cc : types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMStblnc.tmc
	$(TMC) types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMStblnc.tmc
HFEMSdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSdispncoui.o : HFEMSdispncoui.c
HFEMSdispnc.o : HFEMSdispnc.cc
HFEMSalgoa.tmc : HFEMS.tma HFEMSsrvr
	$(SERVER) ./HFEMSsrvr
	$(TMCALGO) -V "`./HFEMSsrvr -R`" HFEMS.tma
HFEMSalgo.cc : types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMSalgoa.tmc
	$(TMC) types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMSalgoa.tmc
HFEMSalgooui.c : $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/tma.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
HFEMSalgooui.o : HFEMSalgooui.c
HFEMSalgo.o : HFEMSalgo.cc
HFEMSallextcdf.oui : HFEMSall.cdf
	$(EDF2OUI) HFEMSall.cdf
HFEMSallext.tmc : HFEMSall.cdf
	$(EDF2EXT) HFEMSall.cdf
HFEMSallext.cc : types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMSallext.tmc
	$(TMC) types.tmc HFEMS.tmc tdrift.tmc /usr/local/share/huarp/cpu_usage.tmc /usr/local/share/huarp/tmdf.tmc /usr/local/share/huarp/flttime.tmc HFEMSallext.tmc
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
.cvsignore : Makefile
	@for i in $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
CPPFLAGS+=-I../sonic
COLFLAGS=-Haddress.h
address.h : HFEMScol.cc
HFEMSsrvr.o : address.h
CYCLE=cycle > $@
