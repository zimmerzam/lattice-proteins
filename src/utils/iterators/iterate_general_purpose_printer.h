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

#ifndef UTILS_GENERAL_PURPOSE_PRINTER_H
#define UTILS_GENERAL_PURPOSE_PRINTER_H

#include <iostream>
#include <list>
#include <string>

struct general_purpose_printer{
	void operator()(std::list<std::string> kwargs){
  	for(std::list<std::string>::iterator it = kwargs.begin(); it!=kwargs.end();++it){
			std::cout << *it << "  ";
		}
		std::cout << std::endl;
	}
};

#endif
