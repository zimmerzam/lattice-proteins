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

#ifndef ITERATE_H
#define ITERATE_H

#include <list>
#include <string>
#include <initializer_list>

template< typename Functor >
class iterate{
	protected:
		unsigned int length; 
		unsigned int first; 
		unsigned int last; 
		unsigned int skip; 
		Functor& todo;
	public:
		typedef std::list<std::string> kwargs_type;
		iterate( unsigned int length, unsigned int first, unsigned int last, unsigned int skip, Functor& todo ): length(length),first(first),last(last),skip(skip), todo(todo){};
		void operator()( kwargs_type kwargs = kwargs_type({}) ){
			todo(kwargs);
		};
};

#endif
