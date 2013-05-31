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

#ifndef LATTICE_MODEL_H
#define LATTICE_MODEL_H

#include "lattice.h"
#include "sequence.h"
#include "hamiltonian.h"
#include "contact_map.h"
#include "density_of_states.h"

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
class lattice_model{
	private:
		lattice<dimensions, n_directions, connectivity> space;
		word<alphabet_size> sequence;
		hamiltonian<alphabet_size, n_classes> energy_parameters;
		InteractionClass getInteractionClass;
	public:
		lattice_model( std::array<char, alphabet_size> letters ):sequence(letters), energy_parameters(letters){};
		double getEnergy( const std::string& path, const std::string& sequence );
		double getEnergy( const std::string sequence, contact_map<n_classes, InteractionClass> map );
		density_of_states getDensityOfStates( const std::string& sequence );
		contact_map<n_classes, InteractionClass> getContactMap( const std::string& path );
		
		/* Iterate all possible sequences */
		template < typename Functor >
		void iterateSequences( int length, int first, int last, unsigned int skip, Functor& todo );
		template < typename Functor >
		void iterateSequences( int length, unsigned int skip, Functor todo );
		template < typename Functor >
		void iterateSequences( std::string first, std::string last, unsigned int skip, Functor& todo );
		
		/* Iterate all possible paths */
		template< typename Functor >
    void iterateRW( unsigned int length, Functor& todo );
    template< typename Functor >
    void iterateSAW( unsigned int length, Functor& todo );
};

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
double lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::getEnergy( const std::string& path, const std::string& sequence ){
	double ene = 0.;
	for( unsigned int i = 0; i!=sequence.size(); ++i ){
		for( unsigned int j = i; j!=sequence.size(); ++j ){
			int cls = getInteractionClass(path, i, j);
			if(cls >-1 and cls <n_classes){
				ene += energy_parameters.getParameter( sequence[i], sequence[j], cls );
			}
		}
	}
	return ene;
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( int length, int first, int last, unsigned int skip, Functor& todo ){
	sequence.iterate_words(length, first, last, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( int length, unsigned int skip, Functor todo ){
	sequence.iterate_words(length, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( std::string first, std::string last, unsigned int skip, Functor& todo ){
	sequence.iterate_words(first, last, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template< typename Functor >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateRW( unsigned int length, Functor& todo ){
	space.iterate_RW(length, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template< typename Functor >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSAW( unsigned int length, Functor& todo ){
	space.iterate_SAW(length, todo);
}
#endif 
