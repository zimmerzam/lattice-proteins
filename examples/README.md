# Data file format #

## Files describing Self Avoiding Walks ##
Each line describing a **saw** is divided into three space-separated fields.  

The *first field* describes the structure as a sequence of *directions* 
('N' is North, 'S' is South, 'E' is East and 'W' is West). The first direction
is always North and the first non-North one is West.  

The *second field* describes a contact-map. It is a list of comma-separated 
integer describing pair of residues that are nearest neighbors (distance is 1) 
and non-consecutive.  

The *third field* describes a contact-map. It is a list of comma-separated
integer describing pair of residues that are next-nearest-neighbors (distance 
is sqrt(2) ).  

The contact between residues at position `i` and `j` is represented by integer 
`pow(2,i)+pow(2,j)`  

### Example line ###

`NNNNNNNNNNNNWSS  [18432,33792]  [10240,17408,20480,33280,34816]`

## Files describing Density of States ##

Each line contains a variable number of space-separated fields.  

The *first field* describes the sequence.  

Each of the *other fields* describes a pair `(float,integer)` where the float is
the energy of the sequence and the integer is the number of structures in which 
the sequence has that energy.  

Each line has to end with two spaces!  

Note: a variable number of other fields are allowed. This kind of files can be 
read only by the python script *graph_density_of_states.py* at the moment.  

### Example line ###

`HHPPHPPHHHHHHHHH  (-5.78241,12)  (-5.152,7)  (-4.9672,37)  (-4.78241,180)`

## Files describing Folded Structures (Deprecated) ##

Each line is divided into three space-separated fields.  

The *first field* describes the protein sequence, as a string containing only `H`
or `P` characters.  

The *second field* describes the structure as a sequence of *directions* (see
Self Avoiding Walk format above).  

The *third field* is the energy associated to the sequence folded in the 
corresponding structure.  

### Example line ###

`PHPHPPHHHHHHPPHP  NWNNESESENEESWS  -4.7064`

## Files describing Homologous Structures (Deprecated) ##

Each line contains a variable number of space-separated fields.  

The *first field* describes the structure.  

Each of the *other fields* describes a sequence that is associated
to that structure.  

### Example line ###

`NNNWWWSSSENNESS  HHHPHPPPHPHHPHHH  HHHPHPPPHHHHPHHH  HHHPHPPPPPHHPHHH`

# Example files description #

## structures.cpp ##

This programs allows the user to compute all the self-avoiding-walks (**saw**s) 
of a given length on a square lattice.  

In order to build the executable use the command `make structures`.  

The usage is very simple. Write  

`./structures -l length [options]`

where *length* is an integer relative to the number of residues in the saw.  

By default the program prints the number of different saws it computed. If the
option *-p* is passed, it prints all the saws in the SAW format described above.  

Use the option *-h* for help.

### Example usage ###

The following command:  

`./structures -l 16`

should return  

`I have found 802075 self-avoiding-walks`.

## density_of_states.cpp ##

This program takes a file with a list of self-avoiding-walks and print the 
density of states for each *HP* sequence of the appropriate length.  

The program can also be used to filter and existing density_of_states file.
The only available filter excludes all the sequences that are not a 
two-state folder. You can use it by enabling the flag *-t*.  

In order to build the executable use the command `make density_of_states`.  

### Example usage ###

`./density_of_states -s saw.dat`

or

`./density_of_states -d density.dat -t`.

## transition.cpp ##

This program takes a file containing a list of density of states and for each
line adds two fields:  

the *first field* is the energy at which there is the transition (concavity of
density of states change sign)  

the *second field* is the transition energy  

To build the executable use the command `make transition`  

Basic usage:  

`./transition -d density_file`.

## graph_density_of_states.py ##

This script takes a density\_of\_states file and plot a graph with free energy
or density of states (depending on the options passed)

Basic usage:  

`./graph_density_of_states.py [options] density_file`.  

For a detailed list of options use the flag `-h`.  

It is possible to use this script in order to read files with additional 
informations on each line. The additional info will be printed on the shell.
Suppose the file contains two more fields at the eand of each line. The first 
field being a *temperature* and the second an *energy*.  
Simply use the command  

`./graph_density_of_states.py density_file -a temperature,energy`

and the file will be processed correctly.  

Note: some options can be changed in runtime!

