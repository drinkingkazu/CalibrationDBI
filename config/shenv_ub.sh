#!/bin/bash

# Set up env + necessary dependencies for the packages
source /grid/fermiapp/products/uboone/setup_uboone.sh
setup root v5_34_23 -q e6:prof
setup libwda v2_20_1
setup psycopg2 v2_5_4

# For DB access through HTML cache server
export LIBWDA_SERVER=dbdata0.fnal.gov
export LIBWDA_PORT=8086
export LIBWDA_DBNAME=uboonecon_dev

