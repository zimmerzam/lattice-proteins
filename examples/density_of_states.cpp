#include <iostream>
#include <cmath>
#include <sstream>

#include "../src/saw.h"
#include "../src/hp.h"
#include "../src/dos.h"

const long double nn_hh_energy = 0.;
const long double  n_hh_energy = -1.;

int main(int argc, char* argv[]){
	// Option parser
	bool saw_flag = false;
	bool density_flag = false;
	bool length_flag = false;
	std::string saw_file = "";
	std::string density_file = "";
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "s:d:l:")) != -1){
		switch (c){
			case 's':
				saw_flag = true;
				saw_file = optarg;
				break;
			case 'd':
				density_flag = true;
				density_file = optarg;
				break;
			case 'l':
				length_flag = true;
				length = atoi(optarg);
		}
	}
	if(not saw_flag and not (density_flag and length_flag) ){
		printf ("Usage: ./markov ( -s saw_file ) OR ( -d density_file - l length )\n");
		return 1;
	}

	if(saw_flag){
		std::vector<saw> saws;
		std::ifstream sawfile;
		sawfile.open(saw_file.c_str(),std::fstream::in); // open file
	 	std::string line="";
 		while(getline(sawfile, line)) {
 	  	saws.push_back( readSaw(line) );
 		}
		length = saws[0].structure.size()+1;

		for(int seq = pow(2,length)-1; seq >=0; --seq){ // 0:P , 1:H
			density_states density;
			for(std::vector<saw>::iterator savoid = saws.begin(); savoid != saws.end(); ++savoid){
				long double energy = hpEnergy(seq,*savoid);
				++density[energy];
			}
			std::cout << printDensity(seq,length, density);
		}
	}
	else if(density_flag and length_flag){
		std::map<std::string, density_states> density;
		std::ifstream densityfile;
		densityfile.open(density_file.c_str(),std::fstream::in); // open file
		std::string line="";
		while(getline(densityfile, line)) {
			std::pair<std::string, density_states> tmp = readDensity(line);
 	  	density[ tmp.first ] = tmp.second;
 		}
 		for( std::map<std::string, density_states, compare_hp>::iterator it = density.begin(); it!=density.end(); ++it ){
 			if( is_two_state_folder( it->second ) != it->second.end() ){
 				std::cout << printDensity(it->first, it->second);
 			}
 		}	
	}
	

	return 0;
}
