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

#include "iterate.h"
#include "lattice.h"
#include "sequence.h"
#include "hamiltonian.h"
#include "contact_map.h"
#include "density_of_states.h"
#include "utils.h"

#include <iterator>

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
class lattice_model{
	private:
		lattice<dimensions, n_directions, connectivity> space;
		word<alphabet_size> sequence;
		hamiltonian<alphabet_size, n_classes> energy_parameters;
		InteractionClass getInteractionClass;
	public:
    typedef contact_map<n_classes, InteractionClass> contact_map_type;
    
		lattice_model( std::array<char, alphabet_size> letters ):sequence(letters), energy_parameters(letters){};
		double getEnergy( const std::string& path, const std::string& sequence );
		double getEnergy( const std::string& sequence, const contact_map_type& map );
		density_of_states getDensityOfStates( const std::string& sequence );
		contact_map_type getContactMap( const std::string& path );
		
		/* Iterators */
		template <typename Functor> 
		struct iterator{
		  typedef typename word<alphabet_size>::template iterator<Functor> words;
		  typedef typename lattice<dimensions, n_directions, connectivity>::template iterator<Functor> paths;
		};
		
		template < typename Functor >
		typename iterator<Functor>::words iterateSequences( unsigned int length, unsigned int first, unsigned int last, unsigned int skip, Functor& todo );
		template < typename Functor >
		typename iterator<Functor>::words iterateSequences( unsigned int length, unsigned int skip, Functor& todo );
		template < typename Functor >
		typename iterator<Functor>::words iterateSequences( std::string first, std::string last, unsigned int skip, Functor& todo );

		/* Iterate all possible paths */
    template< typename Functor >
    typename iterator<Functor>::paths iterateSAW( unsigned int length, Functor& todo );
    
    void initialize_energy_param(std::string filename);
    
    void initialize_SAW(unsigned int length);
    void initialize_SAW(std::string filename);
    

};

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
double lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::getEnergy( const std::string& path, const std::string& sequence ){
	double ene = 0.;
  std::string::const_iterator last = path.end(); --last;
  for(std::string::const_iterator i = path.begin(); i!=last; ++i){ 
		for(std::string::const_iterator j = i; j!=path.end(); ++j){
		  unsigned int ch_i = std::distance( path.begin(), i );
		  unsigned int ch_j = std::distance( path.begin(), j );
			int cls = getInteractionClass(path, ch_i, ch_j );
			if(cls >-1 and cls <(int)n_classes){
				ene += energy_parameters.getParameter( sequence[ch_i], sequence[ch_j+1], cls );
			}
		}
	}
	return ene;
}

//TODO
template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
double lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::getEnergy( const std::string& sequence, const contact_map_type& map ){
  return 0;
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
density_of_states lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::getDensityOfStates( const std::string& sequence ){
  compute_density_of_states< lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass> > dos(*this);
  iterateSAW(sequence.size(),dos)( {sequence} );
  return dos.getDensityOfStates();
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
typename lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::contact_map_type lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::getContactMap( const std::string& path ){
  return contact_map_type(path);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
typename lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::template iterator<Functor>::words lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( unsigned int length, unsigned int first, unsigned int last, unsigned int skip, Functor& todo ){
	return sequence.iterateWords(length, first, last, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
typename lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::template iterator<Functor>::words lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( unsigned int length, unsigned int skip, Functor& todo ){
  return sequence.iterateWords(length, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template < typename Functor >
typename lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::template iterator<Functor>::words lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSequences( std::string first, std::string last, unsigned int skip, Functor& todo ){
	return sequence.iterateWords(first, last, skip, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
template< typename Functor >
typename lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::template iterator<Functor>::paths lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::iterateSAW( unsigned int length, Functor& todo ){
	return space.iterate_SAW(length, todo);
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::initialize_SAW(unsigned int length){
  space.initialize_SAW(length);
};

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity, unsigned int alphabet_size, unsigned int n_classes, typename InteractionClass >
void lattice_model<dimensions, n_directions, connectivity, alphabet_size, n_classes, InteractionClass>::initialize_energy_param(std::string filename){
  energy_parameters.readFromFile(filename);
};

#endif 
