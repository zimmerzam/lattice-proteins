#include "../src/default/square_lattice.h"
#include <iostream>

struct printer{
	unsigned int total;
	bool print_saw;
	
	printer(bool print_saw_flag){
		total=0;
		print_saw = print_saw_flag;
	}
	
	void operator()(std::string path){
		++total;
		if( print_saw ){
			std::cout << path << std::endl;
		}
	}
};

int main(int argc, char* argv[]){

	// Option parser
	bool length_flag = false;
	bool print_saw_flag = false;
	bool usage_flag = false;
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "l:ph")) != -1){
		switch (c){
			case 'l':
				length_flag = true;
				length = (unsigned int) atoi(optarg);
				break;
			case 'p':
				print_saw_flag = true;
				break;
		  case 'h':
		    usage_flag = true;
		    break;
		}
	}
	if(not length_flag or usage_flag){
		printf ("Usage: ./saw -l length [options]\n");
		printf ("Options:\n");
		printf ("\t-p Print the structures (default=false)\n");
		return 1;
	}

	square_lattice square;
	printer print( print_saw_flag );
	square.iterate_SAW(length,print);
	if( not print_saw_flag ){
		printf("I have found %u self-avoiding-walks\n",print.total);
	}
	return 0;
}
