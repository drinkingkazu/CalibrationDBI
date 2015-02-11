from ROOT import lariov,TTimeStamp
db=lariov.WebReader("string").GetME()

ts=TTimeStamp()
ts.SetSec(12347578)
data = db.Request("pedestals",ts);
print data.NChannels()
for x in xrange(data.NChannels()):
    ch=data.ChData(x)
    print "channel:",ch.Channel()
    for y in xrange(ch.size()):
        print ch[y],
    print

