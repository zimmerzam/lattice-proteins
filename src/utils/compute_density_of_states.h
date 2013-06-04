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

#ifndef UTILS_COMPUTE_DOS_H
#define UTILS_COMPUTE_DOS_H

#include <string>
#include <list>
#include "../density_of_states.h"

template <typename Model>
struct compute_density_of_states{
  double (Model::*pt2Member)(const std::string&, const std::string&);

  Model* model;
  density_of_states density;
  unsigned int n_states;

  compute_density_of_states( Model& mdl) : pt2Member( &Model::getEnergy ){
    model = &mdl;
    n_states = 0;
  };

  void operator()(std::list<std::string> kwargs){
    std::list<std::string>::iterator it = kwargs.begin();
    std::string seq  = (*it); ++it;
    std::string path = (*it);
    double en = (model->getEnergy)(path, seq);
    density.incrementBin(en,1.);
    ++n_states;
	}
	
	density_of_states& getDensityOfStates(){
	  for( density_of_states::iterator it = density.begin(); it != density.end(); ++it ){
	    it->second /= n_states;
	  }
	  return density;
	}
};

#endif
