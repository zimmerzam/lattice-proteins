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

#ifndef FILL_STL_CONTAINER_H
#define FILL_STL_CONTAINER_H

#include "../iterate.h"
#include <set>
#include <vector>
#include <list>
template <typename stl_container>
struct fill_stl_container{
  stl_container* container;
  
  fill_stl_container( stl_container& cnt){
    container = &cnt;
  };

  void operator()(std::list<std::string> kwargs){};
};

template<>
void fill_stl_container< std::set<std::string> >::operator()(std::list<std::string> kwargs){
  if( kwargs.size() != 1 ){
    return;
  }
  container->insert( kwargs.front() );
}

template<>
void fill_stl_container< std::vector<std::string> >::operator()(std::list<std::string> kwargs){
  if( kwargs.size() != 1 ){
    return;
  }
  container->push_back( kwargs.front() );
}

template<>
void fill_stl_container< std::list<std::string> >::operator()(std::list<std::string> kwargs){
  if( kwargs.size() != 1 ){
    return;
  }
  container->push_back( kwargs.front() );
}

#endif
