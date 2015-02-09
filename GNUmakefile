#####################################################################################
#
# A top Makefile for building my project.
# One needs to define $CALIBDB_DIR environment variable and set it to where this
# makefile exists. 
# One can type "make" and this builds packages that are added in $SUBDIR defined below.
# 
# The original is taken from Glenn A. Smith's example for Double Chooz experiment.
#
#####################################################################################
#
# IMPOSE CONDITION BETWEEN CALIBDB_DIR & PWD =>
#   do not compile if PWD !=$CALIBDB_DIR is set elsewhere
#
ifndef CALIBDB_DIR
ERROR_MESSAGE := $(error CALIBDB_DIR not set...)
endif
#
#####################################################################################
#
# Define directories to be compile upon a global "make"...
#
ifndef USE_LOCAL_LIBWDA
SUBDIRS := IOVData WebDBI
else
SUBDIRS := wda IOVData WebDBI
endif
#####################################################################################
#
# COMPILATION...
#
#.phony: all configure default-config clean
.phony: all clean

all:
	@for i in $(SUBDIRS); do ( echo "" && echo "Compiling $$i..." && cd $(CALIBDB_DIR)/$$i && $(MAKE) ) || exit $$?; done
#####################################################################################
#
# CLEANs...
#
clean:
	@for i in $(SUBDIRS); do ( echo "" && echo "Cleaning $$i..." && cd $(CALIBDB_DIR)/$$i && $(MAKE) clean && rm -f $(LARLITE_LIBDIR)/$$i.* ) || exit $$?; done

#####################################################################################
#
# DOCUMENTATION...
#
doxygen:
	@echo 'dOxygenising your code...'
	@mkdir -p $(CALIBDB_DIR)/doc/dOxygenMyProject
	@doxygen $(CALIBDB_DIR)/doc/doxygenMyProject.script

doxygen+:
	@echo 'dOxygenising MyProject + local-ROOT...'
	@mkdir -p $(CALIBDB_DIR)/doc/dOxygenMyProject+
	@doxygen $(CALIBDB_DIR)/doc/doxygenMyProject+.script
#
#####################################################################################
#EOF
