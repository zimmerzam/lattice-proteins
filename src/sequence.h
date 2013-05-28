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
#include <initializer_list>

template < int alphabet_size >
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
		
		template < typename Functor >
		void iterate_words( int length, int first, int last, unsigned int skip, Functor todo );
		template < typename Functor >
		void iterate_words( int length, unsigned int skip, Functor todo );
		template < typename Functor >
		void iterate_words( std::string first, std::string last, unsigned int skip, Functor todo );
};

template < int alphabet_size >
int word<alphabet_size>::toInt(std::string seq){
	int iseq = 0;
	for(unsigned int i = 0; i < seq.size(); ++i){
		iseq += letter_index[ seq[i] ]*pow( alphabet_size, i );
	}
	return iseq;
}

template < int alphabet_size >
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

template < int alphabet_size >
template < typename Functor >
void word<alphabet_size>::iterate_words( int length, int first, int last, unsigned int skip, Functor todo ){
	if(first >= last){
		return;
	}
	++skip;
	for (int i = first; i < last; i+=skip){
		todo( toString(i, length) );
	}
}

template < int alphabet_size >
template < typename Functor >
void word<alphabet_size>::iterate_words( int length, unsigned int skip, Functor todo ){
	iterate_words( length, 0, pow(alphabet_size, length), skip, todo );
}

template < int alphabet_size >
template < typename Functor >
void word<alphabet_size>::iterate_words( std::string first, std::string last, unsigned int skip, Functor todo ){
	if( first.size() != last.size() ){
		return;
	}
	iterate_words( first.size(), toInt(first), toInt(last)+1, skip, todo );
}

#endif
