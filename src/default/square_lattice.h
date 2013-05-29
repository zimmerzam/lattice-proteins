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

#ifndef SQUARE_LATTICE_H
#define SQUARE_LATTICE_H

#include "../lattice.h"

typedef lattice<2,4,4> square_lattice;

template<>
square_lattice::lattice(){
	direction = {{ 'N','S','W', 'E' }};
	symmetry_excluded = {{ {'W'} }};
	opposite = { {'N','S'},{'S','N'},{'E','W'},{'W','E'} };
	next = { {'N',direction }, {'S',direction }, 
				   {'E',direction }, {'W',direction } 
				 };
}

#endif 
