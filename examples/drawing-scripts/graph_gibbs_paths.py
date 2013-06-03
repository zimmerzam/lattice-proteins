import matplotlib.pyplot as plt
from matplotlib.patches import PathPatch
from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection

import saw
import sys

gibbsfile = open(sys.argv[1])
sequence = sys.argv[2]

saws_hp = []
saws_bach = []

for line in gibbsfile:
  token = line.split()
  if( token[0]!=sequence ):
    continue
  saws_hp = token[8][1:-1].split("  ")
  saws_bach = token[9][1:-1].split("  ")

if( len(saws_hp)==0 ):
  print "sequence not found"
  exit()

seqs_hp = [sequence for i in range(len(saws_hp))]
seqs_bach = [sequence for i in range(len(saws_bach))]

path, Hverts, Pverts = saw.path( saws_bach, seqs_bach )

patches = [ PathPatch(path, facecolor='None', edgecolor='black', lw=3) ]
for h in Hverts:
  patches.append( Circle( h, 0.15, facecolor='red' ) )
for p in Pverts:
  patches.append( Circle( p, 0.15, facecolor='blue' ) )

fig = plt.figure()
ax = fig.add_subplot(111)
for patch in patches:
  ax.add_patch(patch)

[xmin, ymin],[xmax, ymax] = path.get_extents().get_points()
extents = (xmin-1, ymin-1),(xmax+1, ymax+1)
ax.update_datalim(extents)
ax.autoscale_view()
ax.set_aspect('equal')

plt.show()
