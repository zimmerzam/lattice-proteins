#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <unistd.h>
#include <sstream>
#include "../../lattice-proteins/src/saw.h"
#include "../../lattice-proteins/src/hp.h"
#include "../../lattice-proteins/src/dos.h"

//const long double nn_hh_energy = 0.18479956785;
const long double n_hh_energy = -1.;
const long double nn_hh_energy = 0.;

double sawDistance(const int& seq, saw& s1, saw& s2){
  double dist =0.;
  unsigned int s1_cnt = 0, s2_cnt = 0;
  std::set< int > contact;
  for(std::set< int >::iterator cnt = s1.contact.nearest.begin(); cnt!=s1.contact.nearest.end();++cnt ){
		if((seq&(*cnt))==(*cnt)){
			contact.insert(*cnt);
      ++s1_cnt;
		}
	}
	for(std::set< int >::iterator cnt = s2.contact.nearest.begin(); cnt!=s2.contact.nearest.end();++cnt ){
		if((seq&(*cnt))==(*cnt)){
			if( contact.find(*cnt)!=contact.end() ){
			  ++dist;
			}
			++s2_cnt;
		}
	}
  return dist/std::max(s1_cnt,s2_cnt);
}

density_states distanceDistribution(const int& seq, std::vector< saw >& saws){
  density_states density;
  std::vector< saw >::iterator last = saws.end(); --last;
  for(std::vector< saw >::iterator f = saws.begin(); f!=last; ++f){
    std::vector< saw >::iterator s = f; ++s;
    for(; s!=saws.end(); ++s){
      double distance = sawDistance(seq, *f, *s);
      ++density[distance];
    }
  }
  return density;
}

int main(int argc, char* argv[]){
	// Option parser
	bool saw_flag = false;
	bool density_flag = false;
	std::string saw_file = "";
	std::string density_file = "";
	int c;

	while ((c = getopt (argc, argv, "s:d:")) != -1){
		switch (c){
			case 's':
				saw_flag = true;
				saw_file = optarg;
				break;
			case 'd':
				density_flag = true;
				density_file = optarg;
				break;
		}
	}
	if(not saw_flag or not density_flag){
		printf ("Usage: ./similarity -s saw_file -d density_file \n");
		return 1;
	}

  // read saws
	std::vector<saw> saws;
	std::ifstream sawfile;
	sawfile.open(saw_file.c_str(),std::fstream::in);
 	std::string line="";
 	while(getline(sawfile, line)) {
   	saws.push_back( readSaw(line) );
 	}
	// get free energy barrier
	std::map<int, double> g_nat, g_den, f_barr;
	std::map<std::string, density_states> gibbs;
	std::ifstream densityfile;
	densityfile.open(density_file.c_str(),std::fstream::in); // open file
	while(getline(densityfile, line)) {
		std::pair<std::string, density_states> tmp = readDensity(line);
		density_states::iterator barr = is_two_state_folder( tmp.second );
		if( barr!=tmp.second.end() ){
		  f_barr[hpSeq( tmp.first )] = barr->first + 0.00001;
		}
 	}

  unsigned int length = saws[0].structure.size()+1;
  std::map< int, std::vector<saw> > native;
	for(int seq = pow(2,length)-1; seq >=0; --seq){ // 0:P , 1:H
	  if( f_barr.find(seq)==f_barr.end() ){
	    continue;
	  }
		double trans_energy = f_barr[seq];
		for(std::vector<saw>::iterator savoid = saws.begin(); savoid != saws.end(); ++savoid){
			double energy = hpEnergy(seq,*savoid);
			if( energy < trans_energy ){
			  native[seq].push_back(*savoid);
			}
		}
	}
	
	for(std::map< int, std::vector<saw> >::iterator it = native.begin(); it!=native.end(); ++it){
	  density_states prob = distanceDistribution(it->first, it->second);
	  std::cout << printDensity( hpSeq(it->first, length), prob );
	}
	
	return 0;
}
