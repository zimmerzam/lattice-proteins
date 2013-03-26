import numpy as np
import matplotlib.pyplot as plt
import sys

filename = sys.argv[1]
file = open(filename, 'r')

data = {}
min_ene = 10000.;
max_ene = -10000.;
for line in file:
  token = line.split('  ')
  seq = token[0]
  x = []
  y = []
  logy = []
  for dos in token[1:-1]:
    energy,value = dos[1:-1].split(',')
    if( float(energy) < min_ene ):
      min_ene = float(energy)
    if(float(energy) > max_ene):
      max_ene = float(energy)
    x.append( float(energy) )
    y.append( float(value) )
  data[seq] = {"energy":x, "value":y}

length = len(data.keys()[0])
x_bin = len(data[data.keys()[0]]["energy"])
y_bin = len(data)

x = []
y = []
for idx, key in enumerate(data.keys()):
  for i in range( len(data[key]["value"]) ):
    for j in range( int(data[key]["value"][i]) ):
      x.append( data[key]["energy"][i] )
      y.append( idx )

hist,xedges,yedges = np.histogram2d(x,y,bins=[x_bin,y_bin],range=[[min_ene ,max_ene],[0,y_bin]])
hist[np.where(hist>0)] = np.log10( hist[np.where(hist>0)] )
extent = [xedges[0], xedges[-1], yedges[0], yedges[-1] ]
plt.imshow(hist.T,extent=extent,interpolation='hanning',origin='lower')
plt.colorbar()
plt.show()

print hist
