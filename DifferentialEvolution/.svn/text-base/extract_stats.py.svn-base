#! /usr/bin/python

import scipy.stats
import numpy
import os


dedata = []
cdedata = []
print "Wilcoxon"

for n in [10, 30]:
	for f in xrange(1, 21):
		de = None
		cde = None
		for cmd in ["de", "cde"]:
			loc = "/home/wk/programming/cinvestav/DifferentialEvolution/stats/" + cmd + "-output/"
			data = []
			for i in xrange(1000):
				fn = loc + str(f) + "-" + str(n) + "-" + str(i+1) + ".out"
				try:
					file = open(fn, "r")
				except:
					break

				last = None
				while True:
					s = file.readline()
					if s == "":
						break
					last = s
				data += [float(last[8:-1])]
			
			if cmd == "de":
				de = data
				dedata += [data]
			else:
				cde = data
				cdedata += [data]
		
		u, pvalue = scipy.stats.ranksums(cde, de)
		if pvalue <= 0.05:
			if u < 0:
				match = "+"
			else:
				match = "-"
		else:
			match = "="
		print match

print "DE"
for data in dedata:
	print "%e / %e / %e" % (min(data), numpy.average(data), numpy.std(data))

print "CDE"
for data in cdedata:
	print "%e / %e / %e" % (min(data), numpy.average(data), numpy.std(data))

