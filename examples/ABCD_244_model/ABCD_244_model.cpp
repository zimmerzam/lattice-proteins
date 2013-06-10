#include "model_definition.h"
#include "../../src/utils.h"
#include <array>
#include <getopt.h>

using namespace abcd_244;

int main(int argc,char* argv[]){
  // Option parser
  bool length_flag = false;
  bool print_saw_flag = false, print_seq_flag = false, print_cnt_flag = false;
  bool print_dos_flag = false;
  bool usage_flag = false;
  unsigned long int length = 0;
  unsigned long int first = 1, last = 0, skip = 0;
  std::string hamiltonian_param_file = "abcd_hamiltonian.param";
  int c;

  while ((c = getopt (argc, argv, "l:f:pschdi:a:k:")) != -1){
    switch (c){
      case 'l':
        length_flag = true;
        length = (unsigned int) atoi(optarg);
        break;
      case 'f':
        hamiltonian_param_file = (std::string) optarg;
        break;
      case 'p':
        print_saw_flag = true;
        break;
      case 's':
        print_seq_flag = true;
        break;
      case 'c':
        print_cnt_flag = true;
        break;
      case 'd':
        print_dos_flag = true;
        break;
      case 'h':
        usage_flag = true;
        break;
      case 'i':
        first = (unsigned int) atoi(optarg);
        break;
      case 'a':
        last = (unsigned int) atoi(optarg);
        break;
      case 'k':
        skip = (unsigned int) atoi(optarg);
        break;
    }
  }
  if(not length_flag or usage_flag){
    printf ("Usage: ./saw -l length [options]\n");
    printf ("Options:\n");
    printf ("\t-f 'param_file' Pass a file containing hamiltonian parameters (default='abcd_hamiltonian.param')\n");
    printf ("\t-p Print the structures (default=false)\n");
    printf ("\t-s Print the sequences (default=false)\n");
    printf ("\t-c Print contact-maps (default=false)\n");
    printf ("\t-d Print density of states (default=false)\n");
    printf ("\t-i (unsigned int) First sequence\n");
    printf ("\t-a (unsigned int) Last sequence\n");
    printf ("\t-k (unsigned int) Number of sequences to skip during iteration (default=0)\n");
    printf ("By default all sequences are iterated\n");
    return 1;
  }

  model abcd244( alphabet );
  general_purpose_printer print;
  
  if (print_seq_flag){
  	if(first > last){
	    abcd244.iterateSequences(length,skip,print)();
	  }
	  else{
	    abcd244.iterateSequences(length, first, last, skip, print)();
	  }
  }
  else if (print_saw_flag){
    abcd244.iterateSAW(length,print)();
  }
  else if (print_cnt_flag){
    compute_contact_map<model,general_purpose_printer> contact(abcd244,print);
    abcd244.iterateSAW(length,contact)();
  }
  else if(print_dos_flag){
    abcd244.initialize_SAW(length);
    abcd244.initialize_energy_param(hamiltonian_param_file);
    iterate_compute_density_of_states<model,general_purpose_printer> it_dos(abcd244, print);
    if(first > last){
	    abcd244.iterateSequences(length,skip,it_dos)();
	  }
	  else{
	    abcd244.iterateSequences(length, first, last, skip, it_dos)();
	  }
  } 
  return 0;
}
