GEN=wda_version.h
#LIB=libwda.a
SHLIB=libwda.so
HDR=wda.h
OBJ=wda.o
SRC=wda.c
#
MAJOR=2
MINOR=21
RELEASE=0
VERSION=$(MAJOR).$(MINOR)

OSNAME          = $(shell uname -s)
HOST            = $(shell uname -n)
OSNAMEMODE      = $(OSNAME)

include $(CALIBDB_DIR)/Makefile/Makefile.${OSNAME}

all: .depend lib/$(SHLIB)  $(CALIBDB_LIBDIR)/$(SHLIB)

clean:
	@echo "<<cleaning all>>"
	@rm -f *.o *.a lib/$(SHLIB) $(CALIBDB_DIR)/lib/$(SHLIB)

$(CALIBDB_LIBDIR)/$(SHLIB): lib/$(SHLIB)
	@echo '<< installing $(SHLIB) >>'
	@ln -sf $(PWD)/lib/$(SHLIB) $(CALIBDB_LIBDIR)

lib/$(SHLIB): $(OBJ)
	@echo "<<linking " $(SHLIB) ">>"
	@$(SOMAKER) $(SOFLAGS) -o lib/$(SHLIB) $(OBJ)

%.o: %.c
	@echo "<<compiling "$@">>"
	@$(CC) -c -o $@ $(CXXFLAGS) $<

.depend: $(SRC) $(HDR)
	@rm -f .depend
	@echo '<< checking dependencies >>'
	@$(CC) -M $(CXXFLAGS) $(INCFLAGS) $(SRC) > .depend

-include .depend
