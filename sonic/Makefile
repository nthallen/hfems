CPPFLAGS= -I /usr/local/include
CXXFLAGS= -Wall -g
LDFLAGS=-Wl,-rpath -Wl,/usr/local/lib -L /usr/local/lib
LIBS=-ltmpp -ltm -lnort

SRC = ${wildcard *.cc} Sonicoui.c
OBJ = ${addsuffix .o, ${basename $(SRC) } }
TGT = Sonic

$(TGT) : $(OBJ)
	$(LINK.cc) -o $(TGT) $(OBJ) $(LIBS)
	usemsg $(TGT) Sonicoui.c
Sonicoui.c : sonic.oui
	oui -o Sonicoui.c sonic.oui
.PHONY : clean
clean :
	rm -f *.o sonic Sonicoui.c

