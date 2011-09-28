#! /usr/bin/python

import numpy
import os

cmd = raw_input()
loc = "/home/wk/programming/cinvestav/weolib/"

instances = os.listdir(loc + "instances")
instances.sort()
for finst in instances:
	data = []
	inst = finst[:finst.index('.')];
	for i in xrange(1000):
		fn = loc + cmd + "/" + inst + "-" + str(i+1) + ".out"
		try:
			f = open(fn, "r")
		except:
			break;

		n = i+1
		for k in xrange(3):
			f.readline()
		s = f.readline()
		data += [int(s)]

	print "%d/%.3f/%.3f" % (min(data), numpy.average(data), numpy.std(data))
	#data2 = data[:]
	#data2.sort()
	#med = data2[len(data2)/2-1]
	#medi = data.index(med)
	#print min(data), numpy.average(data), numpy.std(data), medi

