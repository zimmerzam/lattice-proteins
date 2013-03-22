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
