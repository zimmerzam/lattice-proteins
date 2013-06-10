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

