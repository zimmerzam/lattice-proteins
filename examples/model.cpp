#include "../src/model.h"
#include "../src/default/square_lattice.h"

#include <string>
#include <iostream>

struct getInteractions{
};

struct printer{
	void operator()(std::string string){
		std::cout << string << std::endl;
	}

} print;

int main(){
	lattice_model<2,4,4,2,1,getInteractions> HP224( {{'H','P'}} );
	HP224.iterateSAW(5, print);
	HP224.iterateSequences(6, 0, print);
	return 0;
}
