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

#ifndef DENSITY_OF_STATES
#define DENSITY_OF_STATES

typedef std::map<double, double> density_states;

std::string printDensity(std::string seq, density_states density){
	std::ostringstream line;
	line << seq;
	line << "  ";
	for( density_states::iterator dns = density.begin(); dns != density.end(); ++dns ){
		line << "(";
		line << dns->first;
		line << ",";
		line << dns->second;
		line << ")  ";
	}
	line << std::endl;
	return line.str();
}

std::string printDensity(int seq, unsigned int length, density_states density){
	return printDensity( hpSeq(seq,length), density );
}

std::pair<std::string,density_states> readDensity(std::string line){
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));
	density_states density;
	std::string seq = tokens[0];
	for(unsigned int i = 1; i < tokens.size(); ++i){
		std::istringstream map(tokens[i].substr(1, tokens[i].size()-2));
		std::string x1,x2;
		std::getline(map,x1,',');
		double key = atof(x1.c_str());
		std::getline(map,x2,',');
		double value = atof(x2.c_str());
		density[key] = value;
	}
	return std::make_pair(seq,density);
}

density_states::iterator is_two_state_folder( density_states& density ){
	density_states::iterator it = density.begin(), itm = density.begin(), itp = density.begin(), last = density.end();
	--last;
	++it; ++itp; ++itp;
	for( ; it!=density.end(); ++it, ++itm, ++itp ){
	  if( itp->second > 0 and it->second > 0 and itm->second > 0 and it!=last and itp!=density.end() ){
  		double sec_der = ( log(itp->second) - log(it->second) )/( itp->first - it->first ) - ( log(it->second) - log(itm->second) )/( it->first - itm->first );
	  	if(sec_der > 0){
	  		return it;
	  	}
	  }
		if(it==last){
		  itp=last;
		}
	}
	return it;
}

density_states::iterator free_energy_barrier( density_states& density, double temperature ){
	density_states::iterator it = density.begin(), itm = density.begin(), itp = density.begin(), last = density.end();
	--last;
	++it; ++itp; ++itp;
	for( ; it!=density.end(); ++it, ++itm, ++itp ){
	  if( itp->second > 0 and it->second > 0 and itm->second > 0 and it!=last and itp!=density.end() ){
  		double sec_der = ( log(itp->second) - log(it->second) )/( itp->first - it->first ) - ( log(it->second) - log(itm->second) )/( it->first - itm->first );
	  	if(sec_der > 0){
	  		return it;
	  	}
	  }
		if(it==last){
		  itp=last;
		}
	}
	return it;
}

double distanceDensity( density_states& den1, density_states& den2 ){
  std::set<double> enelist;
  for(density_states::iterator it = den1.begin(); it!=den1.end(); ++it){
    enelist.insert(it->first);
  }
  for(density_states::iterator it = den2.begin(); it!=den2.end(); ++it){
    enelist.insert(it->first);
  }
  double dist = 0.;
  for(std::set<double>::iterator it = enelist.begin(); it!=enelist.end(); ++it){
    dist += pow(( den1[*it] - den2[*it] ),2.);
  }
  return sqrt(dist);
}

#endif
