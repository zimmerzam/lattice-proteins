# Data file format #

## Files describing Paths ##
Each line describing a **path** contains a string describing the path.  

Each character represent a particular direction. For instance, for a square 2D
lattice each path could be a sequence of 'N', 'S', 'W' and 'E' ('N' is North, 
'S' is South, 'E' is East and 'W' is West). 

### Example line ###

`NNNNNNNNNNNNWSS`

## Files describing Contact Maps ##

Each line contains a variable number of space-separated fields, depending on the
number of contact classes you define in your model.

The *first field* always describes a path

The *following fields* describes list the pair of residues that belongs to each 
of the contact classes defined. Each *field* is a list of comma-separated 
integer describing pair of residues that belong to the same contact class.  

The contact between residues at position `i` and `j` is represented by integer 
`pow(2,i)+pow(2,j)`  

### Example line ###

`NEEENWW  [36,66]  [5,9,10,17,18,20,33,34,40,65,68,72,80]`

## Files describing Density of States ##

Each line contains a variable number of space-separated fields.  

The *first field* describes the sequence.  

Each of the *other fields* describes a pair `(float,integer)` where the float is
the energy of the sequence and the integer is the number of structures in which 
the sequence has that energy.  

Note: a variable number of other fields are allowed. This kind of files can be 
read only by the python script *graph_density_of_states.py* at the moment.  

### Example line ###

`HHPPHPPHHHHHHHHH  (-5.78241,12)  (-5.152,7)  (-4.9672,37)  (-4.78241,180)`

## Files describing Hamiltonian parameters ##

These files are composed by a one-line header and by a body.  
The *header* line starts with the string `RES` and is a list of N space separated 
letters. Each letter should identify a residue in your model.  
The *body* contains as many lines as the number of contact classes in the model.
Each line is identify by the string `HAM` and contains a list of N(N+1)/2 
parameters.

### Example line ###

`RES   A  B  C  D`  
`HAM   0  2  0  0  0  3  0  0  0  0`

In this simple example this is the order used in order to list the parameters:  
`AA AB AC AD BB BC BD CC CD DD`
