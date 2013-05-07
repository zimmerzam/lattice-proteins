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

#ifndef HP_H
#define HP_H

#include <cfloat>
#include <string>

enum hp_pair{PP,HP,HH};

extern const long double nn_hh_energy;
extern const long double  n_hh_energy;

int hpSeq(std::string seq){
	int iseq = 0;
	for(unsigned int i = 0; i < seq.size(); ++i){
		if(seq[i]=='H')
			iseq = (iseq|(1<<i));
	}
	return iseq;
}

std::string hpSeq(int iseq, unsigned int length){
	std::string seq = "";
	for(unsigned int i = 0; i < length; ++i){
		if(iseq&(1<<i))
			seq+='H';
		else
			seq+='P';
	}
	return seq;
}

double distance_hp( std::string s1, std::string s2 ){
	if(s1==s2){
		return 0.;
	}
	unsigned int length = s1.size();
	if(length!=s2.size()){
		return DBL_MAX;
	}
	std::vector<unsigned int> diff;
	diff.push_back(0);
	for(unsigned int pos = 0; pos != length; ++pos){
		if(s1[pos] != s2[pos]){
			diff.push_back(pos+1);
		}
	}
	diff.push_back(length+1);
//	double dist = 0;
//	for(unsigned int i = 1; i != diff.size(); ++i){
//		dist += 1./(diff[i] - diff[i-1]);
//	}
	return (double)diff.size();
}

long double hpEnergy(int seq,saw& savoid){
	long double energy = 0.; 
	for(std::set< int >::iterator cnt = savoid.contact.nearest.begin(); cnt!=savoid.contact.nearest.end();++cnt ){
		if((seq&(*cnt))==(*cnt))
			energy+=n_hh_energy;
	}
	for(std::set< int >::iterator cnt = savoid.contact.next_nearest.begin(); cnt!=savoid.contact.next_nearest.end();++cnt ){
		if((seq&(*cnt))==(*cnt))
			energy+=nn_hh_energy;
	}
	return energy;
}

struct compare_hp{
	private:
		std::string reference;
		double value( std::string s ){
			return distance_hp(s,reference);
		}
	public:
		compare_hp(unsigned int length, char c){
			reference = std::string(length, c);
		};
    bool operator()(const std::string s1, const std::string s2) {
    	return value(s1) > value(s2); 
    }
};

#endif
