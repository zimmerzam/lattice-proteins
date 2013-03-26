import sys
import matplotlib.pyplot as plt
from random import random
import math

filename = sys.argv[1]
file = open(filename, 'r')

data = {}
for line in file:
  token = line.split('  ')
  seq = token[0]
  x = []
  y = []
  for dos in token[1:-1]:
    energy,value = dos[1:-1].split(',')
    if(float(value)>0):
      x.append( float(energy) )
      y.append( math.log(float(value)) )
  data[seq] = {"energy":x, "value":y}

length = len(data.keys()[0])

while True:
  print "Insert an HP sequence (or a list of comma-separated HP sequences) of length " + str(length)
  line = sys.stdin.readline()[:-1]
  if (line == 'Q' or line == 'q'):
    break
  sequences = line.split(',')
  for seq in sequences:
    if (seq not in data.keys() ):
      print seq + " is not a valid sequence"
      continue
    plt.plot(data[seq]["energy"], data[seq]["value"], marker='o', linestyle='--', color=(random(),random(),random()), label=seq)
  plt.xlabel('Energy')
  plt.ylabel('N')
  plt.title('Density of states')
  plt.legend()
  plt.show()
