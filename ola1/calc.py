#!/usr/local/bin/python

import sys
import statistics as stats

try: 
        file = open(sys.argv[1])
except:
        print("Usage: (File)")
        sys.exit(0)
v = []
n = []
d = []
b = []

for line in file:
    if(line.startswith("V")):
        v.append(int(line[2:].strip()))
    if(line.startswith("N")):
        n.append(int(line[2:].strip()))
    if(line.startswith("d")):
        d.append(int(line[2:].strip()))
    if(line.startswith("b")):
        b.append(float(line[2:].strip()))

vMin = v[0]
nMin = n[0]
dMin = d[0]
bMin = b[0]

vMax = v[0]
nMax = n[0]
dMax = d[0]
bMax = b[0]

for vNum,nNum,dNum,bNum in zip(v,n,d,b):
    if(vNum < vMin):
        vMin = vNum
    if(nNum < nMin):
        nMin = nNum
    if(dNum < dMin):
        dMin = dNum
    if(bNum < bMin):
        bMin = bNum
    if(vNum > vMax):
        vMax = vNum
    if(nNum > nMax):
        nMax = nNum
    if(dNum > dMax):
        dMax = dNum
    if(bNum > bMax):
        bMax = bNum

vMed = stats.median(v)
nMed = stats.median(n)
dMed = stats.median(d)
bMed = stats.median(b)

vMean = stats.mean(v)
nMean = stats.mean(n)
dMean = stats.mean(d)
bMean = stats.mean(b)

vStd = stats.stdev(v)
nStd = stats.stdev(n)
dStd = stats.stdev(d)
bStd = stats.stdev(b)

print(vMin, vMed, vMean, vMax, vStd)
print(nMin, nMed, nMean, nMax, nStd)
print(dMin, dMed, dMean, dMax, dStd)
print(bMin, bMed, bMean, bMax, bStd)


