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

#ifndef HAMILTONIAN_H
#define HAMILTONIAN_H

#include <vector>
#include <map>
#include <string>
#include <array>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>

template<unsigned int alphabet_size, unsigned int n_classes>
class hamiltonian{
	private:
		std::array<char, alphabet_size> alphabet;
		std::vector< std::pair<char, char> > pairs;
		std::map< std::pair<char, char>, std::array<double, n_classes> > parameters;
	public:
		hamiltonian( std::array<char, alphabet_size> alphabet ): alphabet(alphabet){
			for(unsigned int i = 0; i < alphabet.size(); ++i){
				for(unsigned int j = i; j < alphabet.size(); ++j){
					pairs.push_back( std::make_pair( alphabet[i], alphabet[j] ) );
				}
			}
		};
		
		void readFromFile(std::string filename);
		void print();
		
		double getParameter(char ch1, char ch2, int cls);
};

template<unsigned int alphabet_size, unsigned int n_classes>
void hamiltonian< alphabet_size, n_classes >::readFromFile(std::string filename){
	std::ifstream ham_file;
  ham_file.open(filename.c_str(),std::fstream::in);
  std::string line="";
  int idx = 0;
 	while(getline(ham_file, line) and idx != n_classes) {
 		std::string identifier = line.substr(0,4);
   	if( identifier != "HAM " and identifier!="RES " ){
   		continue;
   	}
   	if( identifier == "RES " ){
   		std::istringstream iss(line);
			std::vector<std::string> tokens;
			copy( std::istream_iterator<std::string>(iss),
						std::istream_iterator<std::string>(),
						std::back_inserter<std::vector<std::string> >(tokens));
			for(unsigned int i = 1; i != tokens.size(); ++i){
				if( tokens[i].c_str()[0]!= alphabet[i-1] ){
					std::cout << std::endl << "!!!! Probably a wrong parameter file !!!!\n";
					return;
				}
			}
   	}
   	else{
	   	std::istringstream iss(line);
			std::vector<std::string> tokens;
			copy( std::istream_iterator<std::string>(iss),
						std::istream_iterator<std::string>(),
						std::back_inserter<std::vector<std::string> >(tokens));
			for(unsigned int i = 1; i != tokens.size(); ++i){
				parameters[ pairs[i-1] ][idx] = atof(tokens[i].c_str());
			}
   		++idx;
   	}
 	}
}

template<unsigned int alphabet_size, unsigned int n_classes>
void hamiltonian< alphabet_size, n_classes >::print(){
	std::cout << "RES " << "  ";
	for(unsigned int i = 0; i != alphabet.size(); ++i){
		std::cout << alphabet[i];
		if( i != (alphabet.size()-1) ){
			std::cout << "  ";
		}
	}
	std::cout << std::endl;
	
	for( unsigned int j = 0; j != n_classes; ++j ){
		std::cout << "HAM " << "  ";
		for( unsigned int i = 0; i != pairs.size(); ++i ){	
			std::cout << parameters[ pairs[i] ][j];
			if( i != (pairs.size()-1) ){
				std::cout << "  ";
			}
		}
		std::cout << std::endl;
	}
}

template<unsigned int alphabet_size, unsigned int n_classes>
double hamiltonian< alphabet_size, n_classes >::getParameter(char ch1, char ch2, int cls){
	return parameters[std::make_pair(ch1,ch2)][cls];
}


#endif
