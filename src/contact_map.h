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

#ifndef CONTACT_MAP_H
#define CONTACT_MAP_H

#include <string>
#include <vector>
#include <set>

typedef std::set< int > contacts;

struct contact_map{
	contacts nearest;
	contacts next_nearest;
};

contact_map getContacts(std::string word){
	contact_map map;
	for(unsigned int i=0; i<word.size()-1;i++){
		int count_h = 0;
		int count_v = 0;
		for(unsigned int j=i; j<word.size();j++){
			if(word[j]=='W')
				count_h-=1;
			else if(word[j]=='E')
				count_h+=1;
			else if(word[j]=='N')
				count_v+=1;
			else if(word[j]=='S')
				count_v-=1;
			if( j>i+1 and ( (abs(count_h)==1 and count_v==0) or (abs(count_v)==1 and count_h==0) ) ){
				map.nearest.insert( (1<<i)|(1<<(j+1)) );
			}
			else if( abs(count_v)==1 and abs(count_h)==1 ){
				map.next_nearest.insert( (1<<i)|(1<<(j+1)) );
			}
		}
	}
	return map;
}

#endif
