#
# This is an example GNUmakefile for my packages
#

# specific names for this package
DICT  = IOVDBDict
SHLIB = libIOVDB.so

SOURCES = $(filter-out $(DICT).cxx, $(wildcard *.cxx))
FMWK_HEADERS = LinkDef.h $(DICT).h
HEADERS = $(filter-out $(FMWK_HEADERS), $(wildcard *.h))
OBJECTS = $(SOURCES:.cxx=.o)

# include options for this package
INCFLAGS  = -I.

# platform-specific options
OSNAME          = $(shell uname -s)
HOST            = $(shell uname -n)
OSNAMEMODE      = $(OSNAME)

include $(CALIBDB_DIR)/Makefile/Makefile.${OSNAME}

# set compiler options for ROOT
CXXFLAGS +=  `root-config --cflags` 
CXXFLAGS +="-Dcpp_variable CALIBDB_LOCAL_BUILD"
# call the common GNUmakefile
include $(CALIBDB_DIR)/Makefile/GNUmakefile.CORE



