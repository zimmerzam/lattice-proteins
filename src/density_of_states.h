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

#include <float.h>

class density_of_states{
	protected:
		typedef std::map<double, double> density_type;
		std::string sequence;
		density_type density;
	public:
	  density_of_states(){};
		std::string toString();
    void fromString(const std::string&);
    
    void clear();
    void setBin(double en, double dos);
    void incrementBin(double en, double incr);
    double getBin(double en);
		
		typedef typename density_type::iterator iterator;
    typedef typename density_type::const_iterator const_iterator;
    typedef typename density_type::reverse_iterator reverse_iterator;
    iterator begin(){return density.begin();};
    iterator end(){return density.end();};
    reverse_iterator rbegin(){return density.rbegin();};
    reverse_iterator rend(){return density.rend();};
		
		iterator transitionBarrier();
		double transitionTemperature( double initial_temperature = 1., double accuracy = 0.01 );
};

void density_of_states::clear(){
  density.clear();
}

void density_of_states::setBin(double en, double dos){
  density[en] = dos;
}

void density_of_states::incrementBin(double en, double incr){
  density[en]+=incr;
}

double density_of_states::getBin(double en){
  return density[en];
}

/*
void density_of_states::fromString(std::string line){
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));
	sequence = tokens[0];
	for(unsigned int i = 1; i < tokens.size(); ++i){
		std::istringstream map(tokens[i].substr(1, tokens[i].size()-2));
		std::string x1,x2;
		std::getline(map,x1,',');
		double key = atof(x1.c_str());
		std::getline(map,x2,',');
		double value = atof(x2.c_str());
		density[key] = value;
	}
}
*/
std::string density_of_states::toString(){
	std::ostringstream line;
	line << sequence;
	line << "  ";
	for( iterator dns = begin(); dns != end(); ++dns ){
		line << "(";
		line << dns->first;
		line << ",";
		line << dns->second;
		line << ")  ";
	}
	return line.str();
}
/*
density_of_states::iterator density_of_states::transitionBarrier(){
	iterator it = begin(), itm = begin(), itp = begin(), last = end();
	--last;
	++it; ++itp; ++itp;
	for( ; it!=end(); ++it, ++itm, ++itp ){
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

double density_of_states::transitionTemperature( double initial_temperature, double accuracy){
	iterator barrier = transitionBarrier();
  if(barrier==density.end()){
    return DBL_MAX;
  }
	double temperature = initial_temperature;
	iterator& first_den = barrier; ++first_den;
	double delta_G = 0, derivative = 0;
	double tmp = 0;
	for( iterator it = begin(); it != barrier; ++it ){
	  tmp = (it->second)*exp(-(it->first)/temperature);
	  delta_G -= tmp;
	  derivative -= (it->first)*tmp;
	}
	tmp = (barrier->second)*exp(-(barrier->first)/temperature);
  delta_G -= tmp;
	derivative -= (barrier->first)*tmp;
	for( iterator it = first_den; it != end(); ++it ){
	  tmp = (it->second)*exp(-(it->first)/temperature);
	  delta_G += tmp;
	  derivative += (it->first)*tmp;
	}
	
	double prev_delta = delta_G;
	while (delta_G*prev_delta > 0 and std::fabs(delta_G) > accuracy){
	  prev_delta = delta_G;
	  temperature = temperature - accuracy*delta_G/derivative;
	  //std::cout << temperature << "  " << delta_G << "  " << derivative << std::endl;
	  if(temperature > 100 or temperature < 0){
	    return DBL_MAX;
	  }
	  delta_G = 0;
	  derivative = 0;
	  for( iterator it = density.begin(); it != barrier; ++it ){
  	  tmp = (it->second)*exp(-(it->first)/temperature);
	    delta_G -= tmp;
	    derivative -= (it->first)*tmp;
	  }
	  tmp = (barrier->second)*exp(-(barrier->first)/temperature);
    delta_G -= tmp;
	  derivative -= (barrier->first)*tmp;
	  for( iterator it = first_den; it != density.end(); ++it ){
	    tmp = (it->second)*exp(-(it->first)/temperature);
	    delta_G += tmp;
	    derivative += (it->first)*tmp;
	  }
	}
	return temperature;
}
*/
#endif
