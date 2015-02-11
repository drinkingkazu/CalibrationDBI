from ROOT import lariov, TFile, TTree
import sys, os

if (len(sys.argv) != 2):
    print "Please provide a single input file as argument."

calibTPCwriter = lariov.GetCalibTPCResults(sys.argv[1])
calibTPCwriter.PrepareTrees()
calibTPCwriter.FillSnapshot(4.7,1.0)
calibTPCwriter.FillSnapshot(14,1.0)
calibTPCwriter.FillSnapshot(25,1.0)
fout = TFile.Open("out.root","RECREATE")
tree = TTree("tree_out","")
calibTPCwriter.WriteSnapshotColl(fout,tree)

