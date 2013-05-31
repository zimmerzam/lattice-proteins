#include "../src/default/square_lattice.h"
#include "../src/default/cubic_lattice.h"
#include <iostream>
#include <list>
#include <string>

struct printer{
	unsigned int total;
	bool print_saw;
	
	printer(bool print_saw_flag){
		total=0;
		print_saw = print_saw_flag;
	}
	
	void operator()(std::list<std::string> kwargs){
		++total;
		if( print_saw ){
			for(std::list<std::string>::iterator it = kwargs.begin(); it!=kwargs.end();++it){
				std::cout << *it << "  ";
			}
			std::cout << std::endl;
		}
	}
};

int main(int argc, char* argv[]){

	// Option parser
	bool length_flag = false;
	bool print_saw_flag = false;
	bool usage_flag = false;
	unsigned int dimension = 2;
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "l:d:ph")) != -1){
		switch (c){
			case 'l':
				length_flag = true;
				length = (unsigned int) atoi(optarg);
				break;
			case 'p':
				print_saw_flag = true;
				break;
			case 'd':
				dimension = (unsigned int) atoi(optarg);
				break;
		  case 'h':
		    usage_flag = true;
		    break;
		}
	}
	if(not length_flag or usage_flag){
		printf ("Usage: ./saw -l length [options]\n");
		printf ("Options:\n");
		printf ("\t-d unsigned int: lattice dimensions (default=2, possible values: 2,3)\n");
		printf ("\t-p Print the structures (default=false)\n");
		return 1;
	}

  printer print( print_saw_flag );
  if(dimension==2){
  	square_lattice square;
	  square_lattice::iterate_saw<printer> it = square.iterate_SAW(length,print);
	  it( );
	  if( not print_saw_flag ){
	  	printf("I have found %u self-avoiding-walks\n",print.total);
	  }
	}
	else if(dimension==3){
	  cubic_lattice cubic;
	  cubic_lattice::iterate_saw<printer> it = cubic.iterate_SAW(length,print);
	  it( {} );
	  if( not print_saw_flag ){
	  	printf("I have found %u self-avoiding-walks\n",print.total);
	  }
	}
	return 0;
}
