# Example files description #

You can build all the examples with the command `make`

## sequences.cpp ##

This is a really very simple (and useless?) program I wrote in order to show 
how to use the **iterator** class.  
The program iterates all the possible five-char strings of 'A','B' and 'C'.

In order to build the executable use the command `make sequences`.  

The usage is very simple. Write  

`./sequences -l length [options]`

where *length* is an integer relative to the number of residues in the saw.  

The output is in the *sequence format* described in the *example_data_files* 
README.

Use the option *-h* for a comprehensive list of options and/or for help.

## saw.cpp ##

This programs allows the user to compute all the self-avoiding-walks (**saw**s) 
of a given length on a square or cubic lattice.  

In order to build the executable use the command `make saw`.  

The usage is very simple. Write  

`./saw -l length [options]`

where *length* is an integer relative to the number of residues in the saw.  

By default the program prints the number of different saws it computed. If the
option *-p* is passed, it prints all the saws in the *path format* described
in the *example_data_files* README.  

Use the option *-h* for help.

### Example usage ###

The following command:  

`./saw -l 16 -d 2`

should return  

`I have found 802075 self-avoiding-walks`.

## model.cpp ##

A very minimal working example of how to build a lattice model (in this case an
`HP` model on a square lattice) and how to iterate every possible paths and 
sequences.

In order to build the executable use the command `make model`.  

# TODO #
Allow the user to enter the length of the paths and what to print as output 
(list of sequences or list of paths)

### Example usage ###

The following command:  

`./model`

should return a list of five-char string representing sequences and a list of all
five-residues saw paths on a square lattice.

## hamiltonian.cpp ##

This script simply read a file containing the hamiltonian parameters for your 
model (See the *example_data_files* README for more informations about the 
hailtonian file format ) and print it out. It can be used to check the 
correctness of the file.

In order to build the executable use the command `make hamiltonian`. 

 ### Example usage ###

The following command:  

`./hamiltonian -f parameter_file -a comma_separated_list_of_residue`

should print the content of the input file.  
For example  

`./hamiltonian -f example_data_files/hamiltonian.param -a A,B,C,D`

# Drawing paths, density of states and more #

See the README.md file provided in the *drawing-scripts* directory.
