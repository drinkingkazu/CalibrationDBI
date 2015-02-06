from IOVAPI import uploader
import sys
k=uploader()
k.read(sys.argv[1])
k.upload()
