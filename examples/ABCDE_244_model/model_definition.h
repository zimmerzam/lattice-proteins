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

#ifndef ABCD_244_MODEL_DEFINITION_H
#define ABCD_244_MODEL_DEFINITION_H

#include "../../src/model.h"
#include "../../src/default/square_lattice.h"
#include "../../src/default/hp_alphabet.h"
#include <string>
#include <array>

namespace abcd_244{

const unsigned int dimensions = 2;
const unsigned int n_directions = 4;
const unsigned int connectivity = 4;
const unsigned int alphabet_size = 4;
const unsigned int n_classes = 2;

struct get_interaction{
	lattice<dimensions,n_directions,connectivity> space;
	bool fast;
	unsigned int last_i;
	std::map<char, unsigned int> validator;

	int operator()( const std::string& path, const unsigned int& i, const unsigned int& j ){
    if(i!=last_i){
      validator.clear();
      last_i = i;
    }
    ++validator[path[j]];
    unsigned int dist = 0;
    for( typename lattice<dimensions,n_directions,connectivity>::direction_type::iterator it = space.direction.begin(); it!= space.direction.end(); ++it ){
	    dist += abs( validator[*it] - validator[ space.opposite[*it] ] );
    }
    if (abs(j-i) < 2){
      return -1;
    }
    if(dist==2){
      return 0;
    }
    return 1;
  }
};

const std::array<char,alphabet_size> alphabet = {{'A','B','C','D'}};
typedef lattice_model<dimensions,n_directions,connectivity,alphabet_size,n_classes,get_interaction> model;
typedef contact_map<n_classes,get_interaction> contact_map;

typedef hamiltonian<alphabet_size, n_classes> hamiltonian;

} // end namespace

#endif
