#include "../src/sequence.h"

struct print{
	void operator() (std::string seq){
		std::cout << seq << std::endl;
	}
};

int main(int argc, char* argv[]){

	// Option parser
	bool usage_flag = false;
	unsigned int skip = 0, first = 0, length = 10, last = 0;
	int c;

	while ((c = getopt (argc, argv, "s:L:f:l:h")) != -1){
		switch (c){
			case 'L':
				length = atoi( optarg );
				break;
			case 's':
				skip = atoi( optarg );
				break;
			case 'f':
				first = atoi( optarg );
				break;
			case 'l':
				last = atoi( optarg );
				break;
		  case 'h':
		    usage_flag = true;
		    break;
		}
	}
	
	if(last==0){
		last=pow(3,length)-1;
	}
	
	if(usage_flag ){
		printf ("Usage: ./sequence [options] \n");
		printf ("Options:\n");
		printf ("\t-L sequence length ( default: 10 )\n");
		printf ("\t-f unsigned int: first sequence to print ( default: 10 )\n");
		printf ("\t-l unsigned int: last  sequence to print ( default: pow(3,length) )\n");
		printf ("\t-s skip ( default: 0 )\n");
		printf ("\t-h help \n");
		return 1;
	}

	word<3> dict( {{'A', 'B', 'C'}} );
	
	print printer;
	dict.iterate_words( dict.toString(first, length), dict.toString(last, length), skip, printer );
	
	return 0;
}
