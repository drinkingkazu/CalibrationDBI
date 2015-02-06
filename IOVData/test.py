from ROOT import lariov,TTimeStamp
db=lariov.IOVReader("string")("dbdata0.fnal.gov",
                              "8086",
                              "uboonecon_dev")

ts=TTimeStamp()
ts.SetSec(12347578)
data = db.Request("pedestals",ts);
for x in xrange(data.NChannels()):
    ch=data.Data(x)
    print "channel:",ch.Channel()
    for y in xrange(ch.size()):
        print ch[y],
    print

