#/usr/bin/python

import copy
import os
import random
import sys

def genTest(dirName, iTest):
  maxTest = dirName == "testy_max"
  f = open(dirName + "/{0:02}.in".format(iTest), "w")
  random.seed()
  n = random.randint(1,100) if not maxTest else 20000000 // ((iTest+2) // 2)
  m = random.randint(1,100) if not maxTest else 20000000 // ((iTest+2) // 2)
  print >>f, n
  for i in range(n):
    print >>f, random.randint(1, m)
  f.close()

dirName = "testy_moje" if len(sys.argv) == 1 else sys.argv[1]
if not os.path.exists(dirName):
  os.mkdir(dirName)
for iTest in range(4 if dirName == "testy_max" else 99):
  genTest(dirName, iTest)
