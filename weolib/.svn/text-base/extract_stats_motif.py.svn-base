#! /usr/bin/python

import numpy
import os

#cmd = raw_input()
cmd = "motiffindingga"
loc = "/home/wk/programming/cinvestav/weolib/"

instances = os.listdir(loc + "instances")
instances.sort()
for finst in instances:
	f = 8
	t = 12
	inst = finst[:finst.index('.')];
	if inst == "3":
		f = 6
		t = 10

	for L in xrange(f, t+1):
		data = []
		cpu = []
		for i in xrange(1000):
			fn = loc + cmd + "-output/" + inst + "-" + str(L) + "-" + str(i+1)
			try:
				f = open(fn + ".out", "r")
			except:
				break;

			n = i+1
			f.readline()
			s = f.readline()
			data += [int(s[7:-1])]

			f = open(fn + ".time", "r")
			f.readline()
			time = f.readline()[5:-1]
			m = int(time[0])
			s = m*60 + float(time[2:-2])
			cpu += [s]

		print "%d %.3f %.3f %.3f" % (min(data), numpy.average(data), numpy.std(data), numpy.average(cpu))
		#data2 = data[:]
		#data2.sort()
		#med = data2[len(data2)/2-1]
		#medi = data.index(med)
		#print min(data), numpy.average(data), numpy.std(data), medi

