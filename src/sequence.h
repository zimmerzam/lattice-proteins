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

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <array>
#include <map>
#include <cmath>
#include <string>
#include <iostream>

#include "iterate.h"

template < unsigned int alphabet_size >
class word{
	private:
		std::array<char,alphabet_size> alphabet;
		std::map<char, unsigned int> letter_index;
		
	public:
		word( std::array<char, alphabet_size> list ): alphabet(list) {
			for(unsigned int i = 0; i != alphabet.size(); ++i){
				letter_index[ alphabet[i] ] = i;
			}
		};
	
		int toInt( std::string seq );
		std::string toString(int iseq, unsigned int length);
		
		template <typename Functor>
    class iterate_word: public iterate<Functor>{
  		private:
  			word& parent;
      public:
        iterate_word( unsigned int length, unsigned int first, unsigned int last, unsigned int skip, Functor& todo, word<alphabet_size>& parent): iterate<Functor>::iterate(length,first,last,skip,todo), parent(parent) {};
        void operator()( typename iterate<Functor>::kwargs_type kwargs = typename iterate<Functor>::kwargs_type({}) );
    };
		
		template < typename Functor >
		iterate_word<Functor> iterateWords( int length, int first, int last, unsigned int skip, Functor& todo );
		template < typename Functor >
		iterate_word<Functor> iterateWords( int length, unsigned int skip, Functor& todo );
		template < typename Functor >
		iterate_word<Functor> iterateWords( std::string first, std::string last, unsigned int skip, Functor& todo );
};

template < unsigned int alphabet_size >
template <typename Functor>
void word<alphabet_size>::iterate_word<Functor>::operator()( typename iterate<Functor>::kwargs_type kwargs){
	if(iterate<Functor>::first >= iterate<Functor>::last){
		return;
	}
	++iterate<Functor>::skip;
	for (unsigned int i = iterate<Functor>::first; i < iterate<Functor>::last; i+=iterate<Functor>::skip){
		typename iterate<Functor>::kwargs_type kw = kwargs;
		kw.push_back( parent.toString(i, iterate<Functor>::length ) );
		iterate<Functor>::todo( kw );
	}
}

template < unsigned int alphabet_size >
int word<alphabet_size>::toInt(std::string seq){
	int iseq = 0;
	for(unsigned int i = 0; i < seq.size(); ++i){
		iseq += letter_index[ seq[i] ]*pow( alphabet_size, i );
	}
	return iseq;
}

template < unsigned int alphabet_size >
std::string word<alphabet_size>::toString(int iseq, unsigned int length){
	std::string seq = "";
	int p_iseq = iseq;
	for(unsigned int i = 0; i < length; ++i){
		iseq /= alphabet_size;
		seq += alphabet[ p_iseq - iseq*alphabet_size ];
		p_iseq = iseq;
	}
	return seq;
}

template < unsigned int alphabet_size >
template < typename Functor >
word<alphabet_size>::iterate_word<Functor> word<alphabet_size>::iterateWords( int length, int first, int last, unsigned int skip, Functor& todo ){
	return word<alphabet_size>::iterate_word<Functor>( length, first, last, skip, todo, *this );
}

template < unsigned int alphabet_size >
template < typename Functor >
word<alphabet_size>::iterate_word<Functor> word<alphabet_size>::iterateWords( int length, unsigned int skip, Functor& todo ){
	return word<alphabet_size>::iterateWords<Functor>( length, 0, pow(alphabet_size, length), skip, todo, *this );
}

template < unsigned int alphabet_size >
template < typename Functor >
word<alphabet_size>::iterate_word<Functor> word<alphabet_size>::iterateWords( std::string first, std::string last, unsigned int skip, Functor& todo ){
	if( first.size() != last.size() ){
		std::cout << " The input strings have different lengths " << std::endl;
		return word<alphabet_size>::iterateWords<Functor>( 0, 0, 0, 0, todo );
	}
	return word<alphabet_size>::iterateWords<Functor>( first.size(), toInt(first), toInt(last)+1, skip, todo );
}

#endif
