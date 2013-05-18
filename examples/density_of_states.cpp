#include <iostream>
#include <cmath>
#include <sstream>

#include "../src/saw.h"
#include "../src/hp.h"
#include "../src/dos.h"

const long double nn_hh_energy = 0.;
const long double  n_hh_energy = -1.;

std::vector<std::string> sortDensity( std::map<std::string, density_states>& density, std::vector<std::string> sorted, std::string& reference ){
  if(sorted.size() <= 1 ){
    return sorted;
  }
  std::string pivot = sorted.back();
  std::vector<std::string> smaller, bigger, Smaller, Bigger;
  density_states ref_den = density[reference], piv_den = density[pivot];
  sorted.pop_back();
  double dist_piv = distanceDensity( piv_den, ref_den );
  for(std::vector<std::string>::iterator it = sorted.begin(); it!=sorted.end(); ++it){
    if( distanceDensity( density[*it], ref_den ) <= dist_piv ){
      smaller.push_back(*it);
    }
    else{
      bigger.push_back(*it);
    }
  }
  if(smaller.size()>0){
    Smaller = sortDensity(density, smaller, reference);
  }
  if(bigger.size()>0){
    Bigger = sortDensity(density, bigger, reference);
  }
  Smaller.push_back(pivot);
  if(Bigger.size()>0){
    Smaller.insert(Smaller.end(), Bigger.begin(), Bigger.end());
  }
  return Smaller;
};

std::vector<std::string> sortDensity( std::map<std::string, density_states>& density, std::string reference ){
  std::vector<std::string> sorted;
  for( std::map<std::string, density_states>::iterator it = density.begin(); it!=density.end(); ++it ){
    if(it->first!=reference){
      sorted.push_back(it->first);
    }
  }
  std::vector<std::string> to_return = sortDensity( density, sorted, reference );
  to_return.insert(to_return.begin(), reference);
  return to_return;
};

std::vector<std::string> sortDensity( std::map<std::string, density_states>& density ){
  double max_dist = 0;
  std::vector<std::string> best_order;
  for( std::map<std::string, density_states>::iterator it = density.begin(); it!=density.end(); ++it ){
    std::vector<std::string> sorted = sortDensity(density, it->first);
    if( distanceDensity( it->second, density[sorted.back()] ) > max_dist ){
      max_dist = distanceDensity( it->second, density[sorted.back()] );
      best_order = sorted;
    }
  }
  return best_order;
};

int main(int argc, char* argv[]){
	// Option parser
	bool saw_flag = false;
	bool density_flag = false;
	bool length_flag = false;
	bool two_state_flag = false;
	bool order_flag = false;
	std::string saw_file = "";
	std::string density_file = "";
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "s:d:l:to")) != -1){
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
				break;
		  case 't':
		    two_state_flag = true;
		    break;
		  case 'o':
		    order_flag = true;
		    break;
		}
	}
	if(not saw_flag and not (density_flag and length_flag) ){
		printf ("Usage: ./density_of_states ( -s saw_file ) OR ( -d density_file - l length -t )\n");
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
			std::cout << printDensity(seq,length, density) << std::endl;
		}
	}
	else if(density_flag and length_flag and ( two_state_flag or order_flag) ){
		std::map<std::string, density_states> density;
		std::ifstream densityfile;
		densityfile.open(density_file.c_str(),std::fstream::in); // open file
		std::string line="";
		while(getline(densityfile, line)) {
			std::pair<std::string, density_states> tmp = readDensity(line);
 	  	density[ tmp.first ] = tmp.second;
 		}
 		if( two_state_flag ){
   		for( std::map<std::string, density_states>::iterator it = density.begin(); it!=density.end(); ++it ){
 	  		if( is_two_state_folder( it->second ) != it->second.end() ){
 	  			std::cout << printDensity(it->first, it->second) << std::endl;
 	  		}
 	  	}
  	}
	  else if(order_flag){
	    std::vector<std::string> sorted = sortDensity(density);
	    for(std::vector<std::string>::iterator it = sorted.begin(); it != sorted.end(); ++it ){
	      std::cout << printDensity( *it, density[*it] ) << std::endl;
	    }
	  }
  }
	return 0;
}
