#! /usr/bin/python

cmd = raw_input()
#loc = raw_input()
loc = "/home/wk/programming/cinvestav/weolib/" + cmd + "-stats/output/"
for i in xrange(1000):
	fn = loc + cmd + "-" + str(i+1) + ".out"
	try:
		f = open(fn, "r")
	except:
		break;

	while True:
		line = f.readline()
		if line == "Final results:\n":
			for k in xrange(2):
				f.readline()
			
			print f.readline()[12:-1] + ";" + f.readline()[15:-1] + ";" + f.readline()[18:-1]

			break

	f.close()

