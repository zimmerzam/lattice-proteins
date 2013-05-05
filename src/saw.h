#ifndef SAW_H
#define SAW_H

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <map>
#include "contact_map.h"

struct saw{
	std::string structure;
	contact_map contact;
  long double energy;
  std::string sequence;

	saw(){};
	saw(std::string form, contact_map map){
		structure=form;
		contact=map;
    energy=0.;
	};
	bool operator<(const saw& other) const{
		return structure < other.structure;
	}
};

bool isSaw(std::string word){
	int count_v = 0;
	int count_h = 0;
	unsigned int size = word.size();
	for(unsigned int i=0; i<size;i++){
		if(word[size-i-1]=='W')
			count_h-=1;
		else if(word[size-i-1]=='E')
			count_h+=1;
		else if(word[size-i-1]=='N')
			count_v+=1;
		else if(word[size-i-1]=='S')
			count_v-=1;
		if(count_v==0 and count_h==0)
			return false;
	}
	return true;
}

/* simple saw file format */

void printSaw(saw s_avoiding){
printf("%s  [", s_avoiding.structure.c_str());
	for(contacts::iterator cnt = s_avoiding.contact.nearest.begin(); cnt!=s_avoiding.contact.nearest.end();++cnt){
		if(cnt==s_avoiding.contact.nearest.begin())
			printf("%d",*cnt);
		else
			printf(",%d",*cnt);
	}
	printf("]  [");
	for(contacts::iterator cnt = s_avoiding.contact.next_nearest.begin(); cnt!=s_avoiding.contact.next_nearest.end();++cnt){
		if(cnt==s_avoiding.contact.next_nearest.begin())
			printf("%d",*cnt);
		else
			printf(",%d",*cnt);
	}
	printf("]\n");
}

saw readSaw(std::string line){
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));
	contact_map contact;
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
	return saw(tokens[0], contact);
}

std::vector<saw> readSawFile(std::string filename){
  std::vector<saw> saws;
  std::ifstream sawfile;
  sawfile.open(filename.c_str(),std::fstream::in);
  std::string line="";
 	while(getline(sawfile, line)) {
   	saws.push_back( readSaw(line) );
 	}
  return saws;
}

bool sawSort(saw i, saw j){
  return (i.energy < j.energy);
}

/* Folded file format */

saw readFold(std::string line){
  std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));
	contact_map contact = getContacts(tokens[1]);
  saw new_saw(tokens[1], contact);
  new_saw.energy = atof(tokens[2].c_str());
  new_saw.sequence = tokens[0];
  return new_saw;
}

std::vector<saw> readFoldFile(std::string filename){
  std::vector<saw> saws;
  std::ifstream foldfile;
  foldfile.open(filename.c_str(),std::fstream::in);
  std::string line="";
 	while(getline(foldfile, line)) {
   	saws.push_back( readFold(line) );
 	}
  return saws;
}

/* Homologous file format */

typedef std::map<std::string,std::vector<saw> > homologous;

void printHomologous(homologous dict ){
	for(homologous::iterator it = dict.begin(); it!=dict.end(); ++it  ){
		printf("%s  %u", it->first.c_str(), it->second.size());
		for( std::vector<saw>::iterator val = it->second.begin(); val!=it->second.end(); ++val ){
			printf("%s  ",val->structure.c_str());
		}
		printf("\n");
	}
}

homologous readHomologous(std::string filename ){
 	std::ifstream homfile;
  homfile.open(filename.c_str(),std::fstream::in);
  std::string line="";
 	homologous hom;
 	while(getline(homfile, line)) {
		std::istringstream iss(line);
		std::vector<std::string> tokens;
		copy( std::istream_iterator<std::string>(iss),
					std::istream_iterator<std::string>(),
					std::back_inserter<std::vector<std::string> >(tokens));
		std::string structure = tokens[0];
		contact_map cnt = getContacts(structure);
		saw base_saw(structure, cnt);
		std::vector<saw> saws;
		for(std::vector<std::string>::iterator seq = tokens.begin()+1; seq != tokens.end(); ++seq ){
			base_saw.sequence = (*seq);
			saws.push_back(base_saw);
		}
		hom[structure] = saws;
 	}
 	return hom;
}


#endif
