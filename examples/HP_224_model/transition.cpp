#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <sstream>
#include <list>
#include "../src/saw.h"
#include "../src/hp.h"
#include "../src/dos.h"

//const long double nn_hh_energy = 0.18479956785;
const long double n_hh_energy = -1.;
const long double nn_hh_energy = 0.;

int main(int argc, char* argv[]){
	// Option parser
	bool density_flag = false;
	bool usage_flag = false;
	std::string density_file = "";
	int c;

	while ((c = getopt (argc, argv, "s:p:d:t")) != -1){
		switch (c){
			case 'd':
				density_flag = true;
				density_file = optarg;
				break;
		  case 'h':
		    usage_flag = true;
		}
	}
	if(not density_flag or usage_flag){
		printf ("Usage: ./transition -d density_file \n");
		return 1;
	}

	// get density_of_states for two_state_folder only
	std::ifstream densityfile;
	densityfile.open(density_file.c_str(),std::fstream::in); // open file
  double prev_transition_T = 0.1;
  std::string line="";
	while(getline(densityfile, line)) {
		std::pair<std::string, density_states> tmp = readDensity(line);
		density_states::iterator barr = is_two_state_folder( tmp.second );
		if( barr==tmp.second.end() ){
		  continue;
		}
    double trans_energy = barr->first;
    
    double transition_T = transitionTemperature(tmp.second, barr, prev_transition_T);
    prev_transition_T = transition_T < 20 and transition_T > 0 ? transition_T : 0.1;
    
    std::cout << printDensity(tmp.first, tmp.second) << "  "
              << trans_energy << "  "
              << transition_T << "  "
              << std::endl;
 	}
	
	return 0;
}
