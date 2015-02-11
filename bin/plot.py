from lariov import lariov
from ROOT import TTimeStamp, TGraph, TCanvas
import sys
from datetime import datetime
from array import array
folder = sys.argv[1]
ch     = int(sys.argv[2])
param  = str(sys.argv[3])
start  = datetime.strptime(sys.argv[4],'%Y-%m-%d %H:%M:%S')
end    = datetime.strptime(sys.argv[5],'%Y-%m-%d %H:%M:%S')
npoints = 100
if len(sys.argv)>=7:
    npoints= int(sys.argv[6])

db = lariov.WebReader("double").GetME()
start = TTimeStamp(start.year, start.month,  start.day, 
                   start.hour, start.minute, start.second, 
                   start.microsecond*1000, 
                   False)
end = TTimeStamp(end.year, end.month,  end.day, 
                 end.hour, end.minute, end.second, 
                 end.microsecond*1000, 
                 False)

xarray=[]
yarray=[]

ts = TTimeStamp(start)
period = int(float(end.GetSec() - start.GetSec()) / float(npoints))
param_index = -1

min_val = 999999999.
max_val = -1. * min_val
for x in xrange(npoints):
    ts.SetSec(start.GetSec() + period * x)
    snapshot = db.Request(folder,ts)
    if param_index < 0:
        param_index = snapshot.Name2Index(param)
    ch_data = snapshot.ChData(0)

    val = ch_data[param_index]
    xarray.append(ts.GetSec())
    yarray.append(val)

    if val > max_val: max_val = val
    if val < min_val: min_val = val

if max_val == min_val:
    if not max_val:
        max_val = 1.
        min_val = -1.
    else:
        max_val = max_val*1.05
        min_val = min_val*0.95
else:
    max_val = max_val * 1.1
    min_val = min_val * 0.9

xarray = array('d',xarray)
yarray = array('d',yarray)

c=TCanvas("c","",600,500)
g=TGraph(npoints,xarray,yarray)
g.Draw("AP")
g.GetXaxis().SetTimeDisplay(1);
g.GetXaxis().SetNdivisions(-503);
g.GetXaxis().SetTimeFormat("%Y-%m-%d %H:%M");
g.GetXaxis().SetTimeOffset(0,"gmt");
g.GetXaxis().SetRangeUser(start.GetSec(),end.GetSec())
g.SetMarkerStyle(22)
g.SetMarkerSize(1)
g.SetMaximum(max_val)
g.SetMinimum(min_val)
g.Draw("APL")
c.Update()
sys.stdin.readline()
