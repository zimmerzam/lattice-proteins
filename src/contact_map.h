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
};

#endif
