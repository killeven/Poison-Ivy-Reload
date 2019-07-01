#coding=utf8
import os
import sys

if __name__ == '__main__':
	if len(sys.argv) != 2:
		print "python %s <funcname1[,funcname2][,funcname3]...>" % sys.argv[0]
		sys.exit(1)
	
	hash = 0
	funcnames = sys.argv[1].split(",")
	for f in funcnames:
		for c in f:
			hash = hash * 131 + ord(c)
			hash = hash & 0xffffffff
		print "#define\t%s_Hash\t\t\t\t0x%X" % (f, hash & 0x7fffffff)
		hash = 0