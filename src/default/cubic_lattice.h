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

#ifndef CUBIC_LATTICE_H
#define CUBIC_LATTICE_H

#include "../lattice.h"

typedef lattice<3,6,6> cubic_lattice;

template<>
cubic_lattice::lattice(){
	direction = {{ 'N','S','W', 'E', 'T', 'B' }};
	symmetry_excluded = {{ {'W','T', 'B'}, {'B'} }};
	opposite = { {'N','S'},{'S','N'},{'E','W'},{'W','E'},{'T','B'},{'B','T'} };
	next = { {'N',direction }, {'S',direction }, 
				   {'E',direction }, {'W',direction },
				   {'T',direction }, {'B',direction } 
				 };
}

#endif 
