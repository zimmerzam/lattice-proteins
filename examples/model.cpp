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

#include "../src/model.h"
#include "../src/default/square_lattice.h"

#include <string>
#include <iostream>

struct getInteractions{
  int operator()(std::string path, unsigned int i, unsigned int j){
    return -1;
  }
};

struct printer{
	void operator()(std::list<std::string> kwargs){
	  for(std::list<std::string>::iterator kw = kwargs.begin(); kw!=kwargs.end(); ++kw){
  		std::cout << *kw << "  ";
  	}
  	std::cout << std::endl;
	}

} print;

int main(){
	lattice_model<2,4,4,2,1,getInteractions> HP224( std::array<char,2>( {{'H','P'}} ) );
	HP224.iterateSequences(5, 0, print)();
	HP224.iterateSAW(5, print)();
	return 0;
}
