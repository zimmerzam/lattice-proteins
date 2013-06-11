/* ************************************************************************** */
/*                                                                            */
/*    Copyright 2013 Stefano Zamuner                                          */
/*                                                                            */
/*    This file is part of lattice-proteins.                                  */
/*                                                                            */
/*    BioCpp is free software: you can redistribute it and/or modify          */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    BioCpp is distributed in the hope that it will be useful,               */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with BioCpp.  If not, see <http://www.gnu.org/licenses/>.         */
/*                                                                            */
/* ************************************************************************** */

#include "../src/hamiltonian.h"

int main(int argc, char* argv[]){

	// Option parser
	bool usage_flag = false;
	std::string iletters = "A,B,C,D", filename = "template_files/hamiltonian.param";
	int c;

	while ((c = getopt (argc, argv, "a:h")) != -1){
		switch (c){
			case 'a':
				iletters = std::string( optarg );
				break;
		  case 'h':
		    usage_flag = true;
		    break;
		}
	}
	if(usage_flag or iletters.size()!=7){
		printf ("Usage: ./hamiltonian [options] \n");
		printf ("Options:\n");
		printf ("\t-f a filename (default: template_files/hamiltonian.param)\n");
		printf ("\t-a list of four comma-separated char ( default: A,B,C,D )\n");
		printf ("\t-h help \n");
		return 1;
	}

	std::array<char,4> letters =  {{iletters[0],iletters[2], iletters[4], iletters[6]}};
	hamiltonian<4,3> en(letters);
	en.readFromFile(filename.c_str());
	std::cout << std::endl << " This is the input file. " << std::endl << std::endl;
	en.print();
	
	return 0;
}
