#!/usr/bin/env python
import sys
import statistics as stats

try:
	file = open(sys.argv[1])
except:
	print("Usage: (File)")
	sys.exit(0)

v = []
for line in file:
    v.append(int(line.strip()))

vMin = v[0]

vMax = v[0]


for vNum in v:
    if(vNum < vMin):
        vMin = vNum
    if(vNum > vMax):
        vMax = vNum

vMed = stats.median(v)

vMean = stats.mean(v)

vStd = stats.stdev(v)

print(vMin, vMax, vMed, vMean, vStd)
