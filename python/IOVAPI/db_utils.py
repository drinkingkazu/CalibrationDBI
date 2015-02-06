from colored_msg import warning, error
from IOVAPI import IOVDB
from db_exception import ConnError
import os,sys,psycopg2

def OpenDB(host=None, port=None, db=None, user=None):
    
    try:
        if host is None: host = os.environ['IOVDB_HOST']
        if port is None: port = os.environ['IOVDB_PORT']
        if db   is None: db   = os.environ['IOVDB_DB'  ]
        if user is None: user = os.environ['IOVDB_USER']
    except KeyError:
        raise ConnError('READ conn. parameter not given & not found in shell env. var.!')

    conn = None
    try:
        conn = IOVDB(connstr='host=%s port=%s dbname=%s user=%s' % (host,port,db,user))
        warning('Connected: consider using WebReader API for read-access to the IOVDB')
    except psycopg2.OperationalError:
        error('Failed to connect the database!')
        conn = None
    return conn

def AskBinary(msg):
    user_input = ''
    print msg
    while not user_input:
        sys.stdout.write('[y/n]:')
        sys.stdout.flush()
        user_input = sys.stdin.readline().rstrip('\n')
        if not user_input.lower() in ['y','n']:
            print 'Invalid user input:', user_input
            user_input=''
        else: break
    print
    return user_input.lower() == 'y'
