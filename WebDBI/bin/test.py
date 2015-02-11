from ROOT import lariov,TTimeStamp
db=lariov.WebReader("string")("dbdata0.fnal.gov",
                              "8086",
                              "uboonecon_dev",
                              10)
ts=TTimeStamp()
ts.SetSec(12347578)
data = db.Request("pedestals",ts);
print data.NChannels()
for x in xrange(data.NChannels()):
    ch=data.Data(x)
    print "channel:",ch.Channel()
    for y in xrange(ch.size()):
        print ch[y],
    print

