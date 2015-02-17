import sys
import ROOT
ROOT.gSystem.Load("libIOVDB")
ROOT.gSystem.Load("libIOVData")
from ROOT import lariov, TTimeStamp, TFile, TTree
from ROOT import std

folder = "pedestal"
ss   = lariov.Snapshot("lariov::ChDataToy")(folder)
col  = lariov.SnapshotCollection("lariov::ChDataToy")(folder)
data = lariov.ChDataToy()

start = TTimeStamp()

for x in xrange(45):

    ss.clear()
    start.SetSec(x*600)
    ss.Reset(start)
    for y in xrange(8300):
        data.Channel(y)
        data.Set(float(y),float(y),float(y));
        ss.Append(data)
    col.Append(ss)

fout = TFile.Open("out.root","RECREATE")
tree = TTree("iov_tree","")
col.Write(tree)
tree.Write()
fout.Close()

fin = TFile.Open("out.root","READ")
col.Read(fin)
fin.Close()
