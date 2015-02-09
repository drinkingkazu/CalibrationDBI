from ROOT import lariov, TTimeStamp, TFile, TTree
from ROOT import std

field_name = std.vector("string")()
field_type = std.vector("string")()

field_name.push_back("channel")
field_name.push_back("mean")
field_name.push_back("rms")
field_type.push_back("bigint")
field_type.push_back("real")
field_type.push_back("real")

folder = "pedestal"

col  = lariov.SnapshotCollection("string")(folder)
ss   = lariov.Snapshot("string")(folder,field_name,field_type)
data = lariov.ChData("string")()

start = TTimeStamp()
end   = TTimeStamp()

for x in xrange(10):

    ss.clear()
    start.SetSec(x*100)
    end.SetSec((x+1)*100-1)
    ss.Reset(start,end)
    for y in xrange(100):

        data.resize(2,"")
        data.Channel(y)
        data[0]="10."
        data[1]="0.5"
        ss.push_back(data)
    col.Append(ss)

fout = TFile.Open("out.root","RECREATE")
tree = TTree("iov_tree","")
col.Write(tree)
tree.Write()
fout.Close()

fin = TFile.Open("out.root","READ")
col.Read(fin)
fin.Close()
