## Drawing Scripts ##

These are small python scripts that allow you to easily graph paths, density of 
states and more.
Be sure you have *python 2.7* or compatible and matplotlib installed on your 
computer.

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

Use 

`./graph_density_of_states.py density_file -h`

for a detailed description of available options and/or to get some help
