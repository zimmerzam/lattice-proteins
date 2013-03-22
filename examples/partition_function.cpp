#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include "../src/saw.h"
#include "../src/hp.h"
#include "../src/bach.h"

const long double nn_hh_energy = 0.18479956785;
const long double  n_hh_energy = -1.;

int main(int argc, char* argv[]){
	// Option parser
	bool saw_flag = false;
	bool param_flag = false;
	std::string saw_file = "";
	std::string param_file = "";
	int c;

	while ((c = getopt (argc, argv, "s:p:")) != -1){
		switch (c){
			case 's':
				saw_flag = true;
				saw_file = optarg;
				break;
			case 'p':
				param_flag = true;
				param_file = optarg;
				break;
		}
	}
	if(not saw_flag or not param_flag){
		printf ("Usage: ./partition_function -s saw_file -p param_file \n");
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
	bach_param par = readBachParam(param_file,length);
	for( std::vector< std::map<hp_pair,double> >::iterator it = par.classn.begin(); it!=par.classn.end(); ++it ){
		(*it)[HH]+=1;
	}
	
	std::string open_struct = "";
	for(unsigned int i = 1; i < length; ++i){
		open_struct+="N";
	}
	
	for(int seq = pow(2,length)-1; seq >=0; --seq){ // 0:P , 1:H
		long double Z = 0.;
		long double bach_en = bachEnergy(seq, open_struct, par, true), min_en = 0;
		std::vector<saw>::iterator tmp = saws.begin();
		for(std::vector<saw>::iterator savoid = saws.begin(); savoid != saws.end(); ++savoid){
			long double energy = hpEnergy(seq,*savoid);
			if(energy < min_en){
				min_en = energy;
				tmp = savoid;
			}
			Z += exp(-energy/0.05);
		}
		std::cout << hpSeq(seq,length) << "  " << log(Z) << "  " << bach_en << "  " 
							<< tmp->contact.nearest.size() << "  " 
							<< tmp->contact.next_nearest.size() << std::endl;
	}
	
	return 0;
}
