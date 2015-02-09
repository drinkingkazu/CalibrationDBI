import sys,__main__
from IOVAPI import OpenDB
from datetime import datetime

def list_folder():
    db = OpenDB()
    folders = db.getFolders()
    for f in folders:
        print '\033[93m ',f,'\033[00m'
    db.disconnect()

def list_column(arg):
    fname = arg[0]
    db = OpenDB()
    folder = db.openFolder(fname)
    print '\033[93m ',fname,'\033[00m','=>',folder._getDataColumns()
    db.disconnect()

def list_iov(arg):
    fname = arg[0]
    db = OpenDB()
    folder = db.openFolder(fname)
    iovs = folder.getIOVs(0,2047570047)
    for x in xrange(len(iovs)):

        if x < (len(iovs)-1):
            print '  IOV id %d : %s => %s' % (iovs[x][0],iovs[x][1],iovs[x+1][1])
        else:
            print '  IOV id %d : %s => future' % (iovs[x][0],iovs[x][1])
    print

def list_ch(arg):
    if not len(arg) == 2: raise IndexError
    from WebDBI import lariov
    from ROOT import TTimeStamp
    web_reader = lariov.WebReader()
    t = datetime.strptime(arg[1],'%Y-%m-%d %H:%M:%S')

    t = TTimeStamp(t.year, t.month, t.day, t.hour, t.minute, t.second);

    data = web_reader.Request(arg[0],t)

    for ch in xrange(data.NRows()):
        for col in xrange(data.NColumns()):
            print data.Field(ch,col),
        print
    print data.NRows()
    
if __name__ == '__main__':

    actions = { 'folder' : list_folder,
                'column' : list_column,
                'iov'    : list_iov,
                'ch'     : list_ch
                }

    if len(sys.argv) < 2 or not sys.argv[1].lower() in actions.keys():
        sys.stderr.write('\n')
        sys.stderr.write('Usage: %s %s $ARG\n' % (__main__.__file__,actions.keys()))
        sys.stderr.write('\n')
        sys.exit(1)

    action = actions[sys.argv[1].lower()]

    try:
        if len(sys.argv) == 2:
            action()
        else:
            action(sys.argv[2:len(sys.argv)])
    except (TypeError, IndexError) as e:
        sys.stderr.write('\n')
        sys.stderr.write('  Invalid argument (%s) for %s!\n' % (sys.argv[2:len(sys.argv)],sys.argv[1]))
        sys.stderr.write('\n')
        raise e
        sys.exit(1)
    sys.exit(0)
