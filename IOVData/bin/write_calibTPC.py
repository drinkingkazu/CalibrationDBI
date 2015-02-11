from ROOT import lariov, TFile, TTree
import sys, os

if (len(sys.argv) != 2):
    print "Please provide a single input file as argument."

ff = TFile.Open("out.root","RECREATE")

calibTPCwriter = lariov.GetCalibTPCResults(sys.argv[1])
calibTPCwriter.PrepareTrees()
calibTPCwriter.PrepareSnapshotCollection("TPC_Calib_ASIC4.7_Sh1")
calibTPCwriter.FillSnapshot(4.7,1.0)
calibTPCwriter.PrepareSnapshotCollection("TPC_Calib_ASIC14_Sh1")
calibTPCwriter.FillSnapshot(14,1.0)
calibTPCwriter.PrepareSnapshotCollection("TPC_Calib_ASIC25_Sh1")
calibTPCwriter.FillSnapshot(25,1.0)
calibTPCwriter.WriteToFile(ff)



