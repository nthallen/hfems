# Makefile Generated Wed Mar 14 10:21:49 EDT 2012
MNC=sonic
HOMEDIR=/home/ndemusz/HFEMS/sonic/TM
SPECFILE=sonic.spec
SRC=sonic.tmc sonic.tbl sonic.doit
TOOL=sonic.spec Makefile
SCRIPT=interact
OBJ=soniccol.cc sonic.pcm tm.dac soniccoloui.c soniccoloui.o
OBJ+=soniccol.o sonictbl.tmc sonicdisp.cc sonicdispoui.c
OBJ+=sonicdispoui.o sonicdisp.o sonictblnc.tmc sonicdispnc.cc
OBJ+=sonicdispncoui.c sonicdispncoui.o sonicdispnc.o doit.dep
OBJ+=soniccmd.cc soniccmd.dat sonicclt.o soniccltoui.c soniccltoui.o
OBJ+=soniccltnc.o soniccltncoui.c soniccltncoui.o sonicsrvr.o
OBJ+=sonicsrvroui.c sonicsrvroui.o
TGT=soniccol sonicdisp sonicdispnc doit sonicclt soniccltnc
TGT+=sonicsrvr
DISTRIB=../Sonic sonic.pcm tm.dac
IDISTRIB=Experiment.config VERSION doit
SRCDIST=sonic.tbl sonic.tmc
NONRCS=
TMCBASE=sonic.tmc
CMDBASE=/usr/local/share/huarp/root.cmd
CMDBASE+=/usr/local/share/huarp/getcon.cmd
RCS=$(SRC) $(TOOL) $(SCRIPT)
SOURCE=$(RCS) $(NONRCS)
OBJECT=$(OBJ) *.err
TARGET=$(TGT)
DSTRB=$(TGT) $(DISTRIB) $(SCRIPT)
TGTDIR= $(TGTNODE)/home/Sonic
include /usr/local/share/huarp/appgen.mk

all : Makefile $(TGT)
Makefile : sonic.spec
	appgen sonic.spec
VERSION=`cat VERSION`
extdistribution : $(DSTRB) $(SRCDIST)
	@[ -d $(TGTDIR)/bin ] || mkdir $(TGTDIR)/bin
	@[ -d $(TGTDIR)/bin/$(VERSION) ] || mkdir $(TGTDIR)/bin/$(VERSION)
	@[ -d  $(TGTDIR)/bin/$(VERSION)/Base ] || mkdir $(TGTDIR)/bin/$(VERSION)/Base
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION) $(DSTRB)
	@distribute $(FORCE) $(TGTDIR)/bin/$(VERSION)/Base $(SRCDIST)
distribution : extdistribution
	@distribute $(FORCE) $(TGTDIR) $(IDISTRIB)
soniccol : soniccol.o soniccoloui.o
	$(LINK.privCXX) soniccol.o soniccoloui.o -ltmpp -ltm -lnort
	$(OUIUSE) soniccoloui.c
	$(PROMOTE) soniccol
sonicdisp : sonicdisp.o sonicdispoui.o
	$(LINK.normCXX) sonicdisp.o sonicdispoui.o -ldisp -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) sonicdispoui.c
sonicdispnc : sonicdispnc.o sonicdispncoui.o
	$(LINK.normCXX) sonicdispnc.o sonicdispncoui.o -ldispnc -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) sonicdispncoui.c
doit : sonic.doit
	mkdoit3 -o doit  sonic.doit
sonicclt : sonicclt.o soniccltoui.o
	$(LINK.normCXX) sonicclt.o soniccltoui.o -ltmph -lph -ltmpp -ltm -lnort
	$(OUIUSE) soniccltoui.c
soniccltnc : soniccltnc.o soniccltncoui.o
	$(LINK.normCXX) soniccltnc.o soniccltncoui.o -ltmnc -lncurses -ltmpp -ltm -lnort
	$(OUIUSE) soniccltncoui.c
sonicsrvr : sonicsrvr.o sonicsrvroui.o
	$(LINK.privCXX) sonicsrvr.o sonicsrvroui.o -ltmpp -ltm -lnort
	$(OUIUSE) sonicsrvroui.c
	$(PROMOTE) sonicsrvr
soniccol.cc : sonic.tmc
	$(TMC.col) sonic.tmc
soniccoloui.c : $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/collect.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
soniccoloui.o : soniccoloui.c
soniccol.o : soniccol.cc
sonictbl.tmc : sonic.tbl
	$(TABLE) sonic.tbl
sonicdisp.cc : sonic.tmc sonictbl.tmc
	$(TMC) sonic.tmc sonictbl.tmc
sonicdispoui.c : $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
sonicdispoui.o : sonicdispoui.c
sonicdisp.o : sonicdisp.cc
sonictblnc.tmc : sonic.tbl
	$(NCTABLE) sonic.tbl
sonicdispnc.cc : sonic.tmc sonictblnc.tmc
	$(TMC) sonic.tmc sonictblnc.tmc
sonicdispncoui.c : $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/nctable.oui $(OUIDIR)/dc.oui $(OUIDIR)/msg.oui
sonicdispncoui.o : sonicdispncoui.c
sonicdispnc.o : sonicdispnc.cc
doit.dep : sonic.doit
	mkdoit3 -M -o doit  sonic.doit
-include doit.dep
soniccmd.cc : /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd
	$(CMDGEN) -d soniccmd.dat /usr/local/share/huarp/root.cmd /usr/local/share/huarp/getcon.cmd
sonicclt.o : soniccmd.cc
	$(COMPILE.clt) soniccmd.cc
soniccltoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/msg.oui
soniccltoui.o : soniccltoui.c
soniccltnc.o : soniccmd.cc
	$(COMPILE.cltnc) soniccmd.cc
soniccltncoui.c : $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/kbdclt.oui $(OUIDIR)/nctable.oui $(OUIDIR)/msg.oui
soniccltncoui.o : soniccltncoui.c
sonicsrvr.o : soniccmd.cc
	$(COMPILE.srvr) soniccmd.cc
sonicsrvroui.c : $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
	$(OUI) $(OUIDIR)/cis.oui $(OUIDIR)/seteuid.oui $(OUIDIR)/msg.oui
sonicsrvroui.o : sonicsrvroui.c

tidy :
	rm -f $(OBJECT)
clean : tidy
	rm -f $(TARGET)
.cvsignore :
	@for i in Makefile '.B4*' $(OBJECT) $(TARGET); do echo "$$i"; done >.cvsignore
CPPFLAGS+=-I ../