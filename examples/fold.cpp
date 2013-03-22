#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include "../src/saw.h"
#include "../src/hp.h"

const long double nn_hh_energy = 0.18479956785;
const long double  n_hh_energy = -1.;

int main(int argc, char* argv[]){
	// Option parser
	bool saw_flag = false;
	std::string saw_file = "";
	int c;

	while ((c = getopt (argc, argv, "s:")) != -1){
		switch (c){
			case 's':
				saw_flag = true;
				saw_file = optarg;
				break;
		}
	}
	if(not saw_flag){
		printf ("Usage: ./fold -s saw_file\n");
		return 1;
	}

	std::vector<saw> saws;
	std::ifstream sawfile;
	sawfile.open(saw_file.c_str(),std::fstream::in); // open file
 	std::string line="";
 	while(getline(sawfile, line)) {
   	saws.push_back( readSaw(line) );
 	}
	unsigned int length = saws[0].structure.size()+1;
	
	for(int seq = 0; seq < pow(2,length); ++seq){ // 0:P , 1:H
		long double min_energy = 0.;
		std::string min_struct = "";
		bool more_than_one = true;
		for(std::vector<saw>::iterator savoid = saws.begin(); savoid != saws.end(); ++savoid){
			long double energy = hpEnergy(seq,*savoid);
			if (energy < min_energy ){
				min_energy=energy;
				more_than_one = false;
				min_struct = savoid->structure;
			}
			else if (energy==min_energy and more_than_one==false){
				more_than_one = true;
				min_struct = "";
			}
		}
		if(not more_than_one){
			std::cout << hpSeq(seq,length) << "  " << min_struct << "  " << min_energy << std::endl;
		}
	}
	
	return 0;
}
