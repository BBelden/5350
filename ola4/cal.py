#!/usr/bin/env python
import sys
import statistics as stats

try:
	file = open(sys.argv[1])
except:
	print("Usage: (File)")
	sys.exit(0)

runs = []
for line in file:
    runs.append(int(line.strip()))

mn = stats.mean(runs)

std = stats.stdev(runs)

print (sys.argv[1],": mean ",mn," std ",std)
