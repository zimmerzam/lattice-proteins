#include "../src/model.h"
#include "../src/default/square_lattice.h"

#include <string>
#include <iostream>

struct getInteractions{
  int operator()(std::string path, unsigned int i, unsigned int j){
    
    return -1;
  }
};

struct printer{
	void operator()(std::list<std::string> kwargs){
	  for(std::list<std::string>::iterator kw = kwargs.begin(); kw!=kwargs.end(); ++kw){
  		std::cout << *kw << "  ";
  	}
  	std::cout << std::endl;
	}

} print;

int main(){
	lattice_model<2,4,4,2,1,getInteractions> HP224( std::array<char,2>( {{'H','P'}} ) );
	HP224.iterateSequences(5, 0, print)();
	HP224.iterateSAW(5, print)();
	return 0;
}
