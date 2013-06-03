import matplotlib.pyplot as plt
from matplotlib.patches import PathPatch
from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection

import saw

saws = ["NNWNEESENNWWW","NNWNEESENNWWN","NNWNEESENNWWW","NNWNEESENNWWN"]
seqs = ["HPPHHPPHPPHPPH","HPPHHPPHPPHPPP","HPPHHPPHPPHPPP","HPPHHHPPHPPHPP"]
  
path, Hverts, Pverts = saw.path( saws, seqs )

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
