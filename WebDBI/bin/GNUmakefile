# Include your header file location
CXXFLAGS += -I$(CALIBDB_DIR)
CXXFLAGS += -I$(CALIBDB_DIR)/WebDBI
CXXFLAGS += -I$(LIBWDA_INC)
CXXFLAGS += -I. $(shell root-config --cflags) -g

# Include your shared object lib location
#LDFLAGS += -lcurl
LDFLAGS += -L$(CALIBDB_LIBDIR) -lIOVData -lWebDBI
LDFLAGS += -L$(LIBWDA_LIB) -lwda
LDFLAGS += $(shell root-config --libs) -lPhysics -lMatrix -g

# platform-specific options
OSNAME = $(shell uname -s)
include $(CALIBDB_DIR)/Makefile/Makefile.${OSNAME}

# Add your program below with a space after the previous one.
# This makefile compiles all binaries specified below.
PROGRAMS = test

all:		$(PROGRAMS)

$(PROGRAMS): *.cc
	@echo '<<compiling' $@'>>'
	@$(CALIBDB_CXX) $@.cc -o $@ $(CXXFLAGS) $(LDFLAGS)
	@rm -rf *.dSYM

clean:	
	rm -f $(PROGRAMS)
