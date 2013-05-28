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

#ifndef SAW_H
#define SAW_H

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include "contact_map.h"

class saw{
	private:
		std::string structure;
		contact_map contact;
	public:
		saw(){};
		saw(std::string form, contact_map map);
		saw(std::string line);
		
		void print();
		bool operator<(const saw& other);
		bool validate();
		
};

saw::saw( std::string form, contact_map map ){
	structure=form;
	contact=map;
}

saw::saw(std::string line){
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));\
				
	structure = tokens[0];
	std::istringstream map1(tokens[1].substr(1, tokens[1].size()-2));
	while(!map1.eof()){
		std::string x;
		std::getline(map1,x,',');
		int cnt = atoi(x.c_str());
		if(cnt!=0)
			contact.nearest.insert(atoi(x.c_str()));
	}
	std::istringstream map2(tokens[2].substr(1, tokens[2].size()-2));
	while(!map2.eof()){
		std::string x;
		std::getline(map2,x,',');
		int cnt = atoi(x.c_str());
		if(cnt!=0)
			contact.next_nearest.insert(atoi(x.c_str()));
	}
}

void saw::print(){
	printf("%s  [", structure.c_str());
	for(contacts::iterator cnt = contact.nearest.begin(); cnt!=contact.nearest.end();++cnt){
		if(cnt==contact.nearest.begin())
			printf("%d",*cnt);
		else
			printf(",%d",*cnt);
	}
	printf("]  [");
	for(contacts::iterator cnt = contact.next_nearest.begin(); cnt!=contact.next_nearest.end();++cnt){
		if(cnt==contact.next_nearest.begin())
			printf("%d",*cnt);
		else
			printf(",%d",*cnt);
	}
	printf("]\n");
}

bool saw::operator<(const saw& other){
	return structure < other.structure;
}

bool saw::validate(){
	int count_v = 0;
	int count_h = 0;
	unsigned int size = structure.size();
	for(unsigned int i=0; i<size;i++){
		if(structure[size-i-1]=='W')
			count_h-=1;
		else if(structure[size-i-1]=='E')
			count_h+=1;
		else if(structure[size-i-1]=='N')
			count_v+=1;
		else if(structure[size-i-1]=='S')
			count_v-=1;
		if(count_v==0 and count_h==0)
			return false;
	}
	return true;
}

std::vector<saw> readSawFile(std::string filename){
  std::vector<saw> saws;
  std::ifstream sawfile;
  sawfile.open(filename.c_str(),std::fstream::in);
  std::string line="";
 	while(getline(sawfile, line)) {
   	saws.push_back( saw(line) );
 	}
  return saws;
}


#endif
