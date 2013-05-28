#include "../src/hamiltonian.h"

int main(int argc, char* argv[]){

	// Option parser
	bool usage_flag = false;
	std::string iletters = "A,B,C,D", filename = "template_files/hamiltonian.param";
	int c;

	while ((c = getopt (argc, argv, "a:h")) != -1){
		switch (c){
			case 'a':
				iletters = std::string( optarg );
				break;
		  case 'h':
		    usage_flag = true;
		    break;
		}
	}
	if(usage_flag or iletters.size()!=7){
		printf ("Usage: ./hamiltonian [options] \n");
		printf ("Options:\n");
		printf ("\t-f a filename (default: template_files/hamiltonian.param)\n");
		printf ("\t-a list of four comma-separated char ( default: A,B,C,D )\n");
		printf ("\t-h help \n");
		return 1;
	}

	std::array<char,4> letters =  {{iletters[0],iletters[2], iletters[4], iletters[6]}};
	hamiltonian<4,3> en(letters);
	en.readFromFile(filename.c_str());
	std::cout << std::endl << " This is the input file. " << std::endl << std::endl;
	en.print();
	
	std::cout << std::endl << " This is the parameter for pair A-A in class 0. " << std::endl << std::endl;
	std::cout << "A  A  0  " << en.getParameter('A','A',0) << std::endl;
	
	return 0;
}
