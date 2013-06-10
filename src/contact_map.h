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

#ifndef CONTACT_MAP_H
#define CONTACT_MAP_H

#include <string>
#include <vector>
#include <set>

typedef std::set< int > contacts;

template< unsigned int n_classes, typename InteractionClass >
class contact_map{
	protected:
		typedef typename std::set< unsigned int > contact_type;
	private:
		std::array< contact_type, n_classes > data;
		InteractionClass getInteractionClass;
	public:
		contact_map(){};
		contact_map( std::string path );
		
		void addContact( unsigned int contact, unsigned int cls );
		contact_type getContacts( unsigned int cls );
		
		std::string toString();
};

template< unsigned int n_classes, typename InteractionClass >
contact_map<n_classes, InteractionClass>::contact_map( std::string path ){
  unsigned int size = path.size();
  for(unsigned int i=0; i!=size-1; ++i){
    for(unsigned int j=i+1; j!=size; ++j){
      unsigned int cnt = ( (1<<j)|(1<<i) );
      int cls = getInteractionClass( path, i, j );
      if( (int)cls > -1 and cls < (int)n_classes ){
        addContact( cnt, cls );
      }
    }
  }
}

template< unsigned int n_classes, typename InteractionClass >
void contact_map<n_classes, InteractionClass>::addContact( unsigned int contact, unsigned int cls ){
  data[cls].insert(contact);
}

template< unsigned int n_classes, typename InteractionClass >
typename contact_map<n_classes, InteractionClass>::contact_type contact_map<n_classes, InteractionClass>::getContacts( unsigned int cls ){
  return data[cls];
}

template< unsigned int n_classes, typename InteractionClass >
std::string contact_map<n_classes, InteractionClass>::toString(){
  std::string str = "";
  for(unsigned int cls = 0; cls!=n_classes; ++cls){
    str+="[";
    for(typename contact_type::iterator it=data[cls].begin(); it!=data[cls].end(); ++it){
      if(it!=data[cls].begin()){
        str+=",";
      }
      std::stringstream ss;
      ss << *it;
      str+=ss.str();
    }
    str+="]  ";
  }
  return str;
}
#endif
