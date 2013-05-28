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

#ifndef LATTICE_H
#define LATTICE_H

#include <array>
#include <map>
#include <set>
#include <string>
#include <iostream>
template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity >
class lattice{
  private:
    typedef std::array< char, n_directions > direction_type;
    typedef std::array< std::set< char >, dimensions-1 > symmetry_excluded_type;
    typedef std::map< char, char > opposite_type;
    typedef std::map< char, std::array<char, connectivity-1> > next_type;
  protected:
    direction_type direction;
    symmetry_excluded_type symmetry_excluded;
    opposite_type opposite;
    next_type next;
    
    bool sawValidate( std::string path );
    template <typename Functor>
    void sawUpdate( std::string path, unsigned int length, std::pair<bool, unsigned int> check_symmetry, Functor& todo );
  public:
    lattice();
    
    template< typename Functor >
    void iterate_RW( unsigned int length, Functor& todo );
    
    template< typename Functor >
    void iterate_SAW( unsigned int length, Functor& todo );  
};

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity >
bool lattice<dimensions, n_directions, connectivity>::sawValidate(std::string path){
  std::map<char,unsigned int> validator;
  for(unsigned int i = 0; i!=path.size(); ++i){
    ++validator[ path[path.size()-1-i] ];
    bool toreturn = true;
    for( typename direction_type::iterator it = direction.begin(); it!= direction.end(); ++it ){
      toreturn = toreturn and ( validator[*it] == validator[ opposite[*it] ] );
    }
    if( toreturn ){
      return false;
    }
  }
  return true;
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity >
template< typename Functor >
void lattice<dimensions, n_directions, connectivity>::sawUpdate( std::string path, unsigned int length, 
                                                     std::pair<bool, unsigned int> check_symmetry, Functor& todo ){
  unsigned int size = path.size();
  if(size==length){
    todo(path);
    return;
  }
  char last = path[size-1];
  for(int c = 0; c != connectivity-1; ++c){
    char next_dir = next[last][c];
    if(check_symmetry.first and symmetry_excluded[check_symmetry.second].find(next_dir)!=symmetry_excluded[check_symmetry.second].end()){
      continue;
    }
    std::string test = path;
    test+=next_dir;
    if( sawValidate(test) ){
      bool ch_sym = (check_symmetry.first and symmetry_excluded[check_symmetry.second].find(opposite[next_dir])!=
                     symmetry_excluded[check_symmetry.second].end() ) ? false : check_symmetry.first;
      std::pair<bool, unsigned int> check;
      if( not ch_sym and check_symmetry.second < dimensions-2 ){
        check = std::make_pair(true, check_symmetry.second+1);
      }
      else if( not ch_sym and check_symmetry.second >= dimensions-2 ){
        check = std::make_pair(false, check_symmetry.second);
      }
      else{
        check = check_symmetry;
      }
      sawUpdate(test, length, check, todo);
    }
  }
}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity >
template< typename Functor >
void lattice<dimensions, n_directions, connectivity>::iterate_RW( unsigned int length, Functor& todo ){

}

template< unsigned int dimensions, unsigned int n_directions, unsigned int connectivity >
template< typename Functor >
void lattice<dimensions, n_directions, connectivity>::iterate_SAW( unsigned int length, Functor& todo ){
  std::string path = "";
  path += direction[0];
  std::pair<bool, unsigned int> check_symmetry = std::make_pair(true,0);
  sawUpdate( path, length-1, check_symmetry, todo );
}
#endif