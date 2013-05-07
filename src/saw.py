# **************************************************************************** #
#                                                                              #
#    Copyright 2013 Stefano Zamuner                                            #
#                                                                              #
#    This file is part of lattice-proteins.                                    #
#                                                                              #
#    BioCpp is free software: you can redistribute it and/or modify            #
#    it under the terms of the GNU General Public License as published by      #
#    the Free Software Foundation, either version 3 of the License, or         #
#    (at your option) any later version.                                       #
#                                                                              #
#    BioCpp is distributed in the hope that it will be useful,                 #
#    but WITHOUT ANY WARRANTY; without even the implied warranty of            #
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             #
#    GNU General Public License for more details.                              #
#                                                                              #
#    You should have received a copy of the GNU General Public License         #
#    along with BioCpp.  If not, see <http://www.gnu.org/licenses/>.           #
#                                                                              #
# **************************************************************************** #

import matplotlib.pyplot as plt
from matplotlib.path import Path
from matplotlib.patches import PathPatch

from matplotlib.patches import Circle
from matplotlib.collections import PatchCollection

def path(saws, seqs, width=13 ):
  vertices = []
  codes = []
  Hverts = []
  Pverts = []
  xoff=0.
  yoff=0.
  max_yoff = 0.
  for i in range(len(saws)):
    saw = saws[i]
    seq = seqs[i]
    
    codes.append( Path.MOVETO )
    for j in range( len(saw) ):
      codes.append(Path.LINETO)
    minx=0
    miny=0
    maxx=0
    maxy=0
    tmp = [(0.,0.)]
    for pos, dir in enumerate(saw):
      coordx = tmp[pos][0]
      coordy = tmp[pos][1]
      if(dir=='N'):
        coordy += 1.
      elif(dir=='S'):
        coordy -= 1.
      elif(dir=='W'):
        coordx -= 1.
      elif(dir=='E'):
        coordx += 1.
      if(coordx>maxx):
        maxx = coordx
      elif(coordx<minx):
        minx = coordx
      if(coordy>maxy):
        maxy = coordy
      elif(coordy<miny):
        miny = coordy
      coord = (coordx,coordy)
      tmp.append(coord)
    xoff = xoff - minx + 1      
    if( maxy-miny>max_yoff ):
      max_yoff = maxy-miny
    if (xoff+maxx > width):
      xoff = -minx+1
      yoff = yoff+max_yoff+1
      max_yoff = 0.
    for idx,vert in enumerate(tmp):
      x = vert[0]
      y = vert[1]
      vertix = (x+xoff, y-miny+yoff+1)
      vertices.append( vertix )
      if(seq[idx]=='P'):
        Pverts.append(vertix)
      elif(seq[idx]=='H'):
        Hverts.append(vertix)
    xoff = xoff + maxx
  return Path(vertices,codes), Hverts, Pverts
