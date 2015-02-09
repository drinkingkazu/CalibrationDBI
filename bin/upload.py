from lariov import IOVDataUploader
import os,sys
k=IOVDataUploader()

if len(sys.argv) < 2:
    print
    print 'Usage: %s $DATA_FILE1 $DATA_FILE2 ... [$FOLDER_NAME]'
    print
    sys.exit(1)
if os.path.isfile(sys.argv[-1]):
    for x in xrange(len(sys.argv)-1):
        k.add(sys.argv[x+1])
else:
    for x in xrange(len(sys.argv)-2):
        k.add(sys.argv[x+1],sys.argv[-1])
k.upload()
