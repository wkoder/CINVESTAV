#! /usr/bin/python

cmd = raw_input()
i = int(raw_input())
#loc = raw_input()
loc = "/home/wk/programming/cinvestav/weolib/" + cmd + "-stats/output/"

fn = loc + cmd + "-" + str(i) + ".out"
f = open(fn, "r")
g = 0
while True:
	if f.readline() == "Final results:\n":
		break
	for i in xrange(1):
		f.readline()
	g = g + 1
	print g, f.readline()[18:-1]
	for i in xrange(9):
		f.readline()

f.close()

