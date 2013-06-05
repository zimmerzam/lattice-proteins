#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
from random import random
import math

import sys
from optparse import OptionParser


def get_additional_info(option, opt, value, parser):
  setattr(parser.values, option.dest, value.split(','))

usage = "%prog [options] density.dat\n\
Print density_od_states or free-energy of required sequences\n"

parser = OptionParser(usage=usage, version="%prog 0.1")
parser.add_option("-d", "--dos",
                  action="store_true", dest="dos", default=False,
                  help="print density of states")
parser.add_option("-l", "--log_scale",
                  action="store_true", dest="logscale", default=False,
                  help="print density of states using log scale")
parser.add_option("-f", "--free_energy",
                  action="store_true", dest="free", default=False,
                  help="print free-energy")
parser.add_option("-t", "--temperature",
                  dest="temperature", default=1.,
                  help="set temperature (used for free-energy only)")
parser.add_option('-a', '--add_info',
                  dest="additional", type='string',
                  action='callback', callback=get_additional_info,
                  help="get final column values as additional information")
                  
(options, args) = parser.parse_args()

if( options.dos and options.free ):
  parser.error(" -d and -f are mutually exclusive. ")
  
if( not options.dos and not options.free ):
  parser.error(" -d or -f is required. ")

n_info = len(options.additional) if options.additional else 0

# read density of states from the input file
filename = args[0]
density_file = open(filename, 'r')

data = {}
for line in density_file:
  token = line.split()
  seq = token[0]
  x = []
  y = []
  tk = token[1:-n_info] if n_info else token[1:]
  for dos in tk:
    energy,value = dos[1:-1].split(',')
    if(float(value)>0):
      x.append( float(energy) )
      y.append( float(value) )  
  data[seq] = {"energy":x, "value":y, "info":token[-n_info-1:-1]}
length = len(data.keys()[0])

while True:
  print "Insert a sequence (or a list of comma-separated sequences) of length " + str(length) + "\nor a valid option ('d','f','l', 't','q')"
  line = sys.stdin.readline()[:-1]
  if (line == 'Q' or line == 'q'):
    print "Goodbye!\n"
    break
  if(line == ''):
    continue
  if (line == 'd' or line == 'D'):
    print "You choose to print density of states\n"
    options.dos = True
    options.free = False
    continue
  if (line == 'f' or line == 'F'):
    print "You choose to print free-energy\n"
    options.dos = False
    options.free = True
    continue
  if (line == 'L'):
    print "You choose to use logscale (disable it with 'l')\n"
    options.logscale = True
    continue
  if (line == 'l'):
    print "You choose to disable logscale (enable it with 'L')\n"
    options.logscale = False
    continue
  if (line == 't' or line == 'T'):
    print "You are changing the temperature. Insert a non-negative float and press Enter\n"
    options.temperature = float(sys.stdin.readline()[:-1])
    print "Temperature now is " + str(options.temperature) + "\n"
    continue

  sequences = line.split(',')
  print
  for seq in sequences:
    if (seq not in data.keys() ):
      print "################################"
      print seq + " is not a valid sequence"
      continue
    zipped = zip(data[seq]["energy"], data[seq]["value"])
    values = []
    for pair in zipped:
      value = pair[1] if options.dos and not options.logscale else math.log(pair[1]) if options.dos and options.logscale else pair[0]-options.temperature*math.log(pair[1])
      values.append(value)
    plt.plot(data[seq]["energy"], values, marker='o', linestyle='--', color=(random(),random(),random()), label=seq)
    if(n_info):
      print "################################"
      print "sequence:  " + seq
      for n in range(n_info):
        print options.additional[n] + ":  " + data[seq]["info"][n]
  xlabel = 'Energy'
  ylabel = 'N' if options.dos and not options.logscale else 'log(N)' if options.dos and options.logscale else 'E-TS'
  title = 'Density of States' if options.dos and not options.logscale else 'Density of States (logscale)' if options.dos and options.logscale else 'Free Energy'
  plt.xlabel(xlabel)
  plt.ylabel(ylabel)
  plt.title(title)
  plt.legend()
  plt.show()
