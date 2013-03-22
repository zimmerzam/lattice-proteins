#include <iostream>
#include <vector>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unistd.h>

#include "../src/saw.h"

struct topology{
	char direction[8];
	std::map<char,char> opposite;
	int children;
	topology(char dir[], std::map<char,char> opp, int near){
		for(int i =0; i < near; ++i){
			direction[i] = dir[i];
		}
		opposite = opp;
		children = near;
	};
};

void sawUpdate(std::string word, bool check_symmetry, unsigned int length, std::vector<saw>& saws, topology& top, bool print){
	unsigned int size = word.size();
	if(size==length){
		contact_map map = getContacts(word);
		saw new_saw(word,map);
		saws.push_back( new_saw );
		if(print){
			printSaw(new_saw);
		}
		return;
	}
	for(int c = 0; c < top.children; ++c){
		char next = top.direction[c];
		if(next!=top.opposite[ word[size-1] ]){
			if(check_symmetry and next=='E')
				continue;
			std::string test = word;
			test+=next;
			if( isSaw(test) ){
				bool check_symm = (check_symmetry and next=='W') ? false : check_symmetry;
				sawUpdate(test, check_symm, length, saws, top, print);
			}
			else{
				continue;
			}
		}
		else{
			continue;
		}
	}
}

int main(int argc, char* argv[]){
	// Option parser
	bool length_flag = false;
	bool print_saw_flag = false;
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "l:p")) != -1){
		switch (c){
			case 'l':
				length_flag = true;
				length = (unsigned int) atoi(optarg)-1;
				break;
			case 'p':
				print_saw_flag = true;
				break;
		}
	}
	if(not length_flag){
		printf ("Usage: ./structures -l length -p(to print the structures)\n");
		return 1;
	}
	
	// Structures...
	std::vector<saw> saws;
	int total = (int)pow(2.5,length); // total saw estimation
	saws.reserve(total);
	
	char dir[4] = {'N', 'S', 'W', 'E'};
	std::map<char,char> opposite;
	opposite['N']='S';
	opposite['S']='N';
	opposite['W']='E';
	opposite['E']='W';
	topology top(dir,opposite,4);
	
	sawUpdate("N", true, length, saws, top, print_saw_flag);
	if(not print_saw_flag)
		printf("I have found %d self-avoiding-walks\n",saws.size());
		
	return 0;
}
