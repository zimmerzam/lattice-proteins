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

#ifndef ITERATE_COMPUTE_CONTACT_MAP_H
#define ITERATE_COMPUTE_CONTACT_MAP_H

#include "../../iterate.h"

template <typename Model, typename Functor>
struct compute_contact_map: public iterate<Functor>{
  typename Model::contact_map_type (Model::*pt2Member)(const std::string&);
  Model* model;
  compute_contact_map( Model& mdl, Functor& todo) : iterate<Functor>::iterate(0,0,0,0,todo), pt2Member( &Model::getContactMap ){
    model = &mdl;
  };

  void operator()(typename iterate<Functor>::kwargs_type kwargs){
    typename Model::contact_map_type cnt = (model->getContactMap)(kwargs.front());
    kwargs.push_back(cnt.toString());
    iterate<Functor>::todo(kwargs);
	}
};

#endif
