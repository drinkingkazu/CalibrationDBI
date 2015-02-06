#!/bin/bash

# clean up previously set env
me="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"
`python $me/python/clean_env.py LD_LIBRARY_PATH`
`python $me/python/clean_env.py DYLD_LIBRARY_PATH`
`python $me/python/clean_env.py PYTHONPATH`
`python $me/python/clean_env.py PATH`

if [[ -z $FORCE_CALIBDB_DIR ]]; then
    # If CALIBDB_DIR not set, try to guess
    # Find the location of this script:
    me="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    # Find the directory one above.
    export CALIBDB_DIR="$( cd "$( dirname "$me" )" && pwd )"
else
    export CALIBDB_DIR=$FORCE_CALIBDB_DIR
fi
unset me;

if [[ -z $LIBWDA_FQ_DIR ]]; then
    echo \$LIBWDA_FQ_DIR not set!
    echo You need to set libwda ups product first.
    return;
fi

echo "CALIBDB_DIR = $CALIBDB_DIR"
if [[ -z $CALIBDB_DIR ]]; then
    echo \$CALIBDB_DIR not set! 
    return;
fi

if [[ -z $LIBWDA_SERVER ]]; then
    echo \$LIBWDA_SERVER not set!
    return;
fi
if [[ -z $LIBWDA_PORT ]]; then
    echo \$LIBWDA_PORT not set!
    return;
fi
if [[ -z $LIBWDA_DBNAME ]]; then
    echo \$LIBWDA_DBNAME not set!
    return;
fi

if [[ -z `command -v rootcint` ]]; then
    echo
    echo Looks like you do not have ROOT installed.
    echo You cannot use LArLite w/o ROOT!
    echo Aborting.
    echo
    return;
fi

CALIBDB_OS=`uname -s`
export CALIBDB_LIBDIR=$CALIBDB_DIR/lib
if [[ -z $USER_MODULE ]]; then
    export USER_MODULE=""
fi
CALIBDB_CXX=clang++
if [ `command -v $CALIBDB_CXX` ]; then
    export CALIBDB_CXX="clang++ -std=c++11";
else
    CALIBDB_CXX=g++
    if [[ -z `command -v $CALIBDB_CXX` ]]; then
	echo
	echo Looks like you do not have neither clang or g++!
	echo You need one of those to compile LArLite... Abort config...
	echo
	return;
    fi
    export CALIBDB_CXX;
    if [ $CALIBDB_OS = 'Darwin' ]; then
	echo $CALIBDB_OS
	echo
	echo "***************** COMPILER WARNING *******************"
	echo "*                                                    *"
	echo "* You are using g++ on Darwin to compile LArLite.    *"
	echo "* Currently LArLite assumes you do not have C++11    *"
	echo "* in this combination. Contact the author if this is *"
	echo "* not the case. At this rate you have no ability to  *"
	echo "* compile packages using C++11 in LArLite.           *"
	echo "*                                                    *"
	echo "* Help to install clang? See manual/contact author!  *"
	echo "*                                                    *"
	echo "******************************************************"
	echo 
    fi
    if [[ -z $ROOTSYS ]]; then
	case `uname -n` in
	    (houston.nevis.columbia.edu)
	    if [[ -z ${ROOTSYS} ]]; then
		source /usr/nevis/adm/nevis-init.sh
		setup root
		export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH;
	    fi
	    ;;
	    (*)
	    echo
	    echo "****************** PyROOT WARNING ********************"
	    echo "*                                                    *"
	    echo "* Did not find your \$ROOTSYS. To use PyROOT feature, *"
	    echo "* Make sure ROOT.py is installed (comes with ROOT).  *"
	    echo "* You need to export \$PYTHONPATH to include the dir  *"
	    echo "* where ROOT.py exists.                              *"
	    echo "*                                                    *"
	    echo "* Help to install PyROOT? See manual/contact author! *"
	    echo "*                                                    *"
	    echo "******************************************************"
	    echo
	    ;;
	esac
    else
	export PYTHONPATH=$ROOTSYS/lib:$PYTHONPATH;
    fi
    
    export LD_LIBRARY_PATH=$CALIBDB_LIBDIR:$LD_LIBRARY_PATH
    export PYTHONPATH=$CALIBDB_DIR/python:$PYTHONPATH
    if [ $CALIBDB_OS = 'Darwin' ]; then
	export DYLD_LIBRARY_PATH=$CALIBDB_LIBDIR:$DYLD_LIBRARY_PATH
    fi
    export PATH=$CALIBDB_DIR/bin:$PATH
    export PYTHONPATH=$CALIBDB_DIR/python:$PYTHONPATH
    alias cdbmake="make --directory=$CALIBDB_DIR"
    alias cdbgen_class="python $CALIBDB_DIR/bin/gen_class_empty"
    alias cdbtop="cd $CALIBDB_DIR"
    echo
    echo "Finish configuration. To build, type:"
    echo "> cd \$CALIBDB_DIR"
    echo "> make"
    echo
fi
