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

#ifndef ITERATE_COMPUTE_DOS_H
#define ITERATE_COMPUTE_DOS_H

#include <string>
#include "../../density_of_states.h"

template <typename Model, typename Functor>
struct iterate_compute_density_of_states: public iterate<Functor>{
  double (Model::*pt2MemberEnergy)(const std::string&, const std::string&);
  typename Model::template iterator<Functor>::paths (Model::*pt2MemberIterator)( unsigned int length, Functor& todo );

  Model* model;

  struct update_density_of_states{
    iterate_compute_density_of_states<Model, Functor>* parent;
    density_of_states density;
    unsigned int n_states;
    
    update_density_of_states( iterate_compute_density_of_states<Model, Functor>& prnt ){
      parent = &prnt;
      n_states = 0;
    };
    
    void operator()(typename iterate<Functor>::kwargs_type kwargs){
      typename iterate<Functor>::kwargs_type::iterator it = kwargs.begin();
      std::string seq  = (*it); ++it;
      std::string path = (*it);
      double en = (parent->model->getEnergy)(path, seq);
      density.incrementBin(en,1.);
      ++n_states;  
    }
    
    void clear(){
      n_states = 0;
      density.clear();
    }
    
  } updater;

  iterate_compute_density_of_states( Model& mdl, Functor& todo) : iterate<Functor>::iterate(0,0,0,0,todo), pt2MemberEnergy( &Model::getEnergy ), pt2MemberIterator( &Model::iterateSAW ), updater(*this){
    model = &mdl;
  };
  
  void operator()(typename iterate<Functor>::kwargs_type kwargs){
    updater.clear();
    std::string seq = kwargs.front();
    model->iterateSAW(seq.size(), updater)(kwargs);
    kwargs.push_back( getDensityOfStates().toString() );
    iterate<Functor>::todo(kwargs);
	}
	
	density_of_states& getDensityOfStates(){
    for( density_of_states::iterator it = updater.density.begin(); it != updater.density.end(); ++it ){
      it->second /= updater.n_states;
    }
    return updater.density;
  }
};

#endif
