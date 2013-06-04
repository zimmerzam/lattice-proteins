#include "model_definition.h"
#include "../../src/utils.h"
#include <array>
#include <getopt.h>

using namespace hp_244;

int main(int argc,char* argv[]){
  // Option parser
  bool length_flag = false;
  bool print_saw_flag = false, print_seq_flag = false, print_cnt_flag = false;
  bool print_dos_flag = false;
  bool usage_flag = false;
  unsigned int length = 0;
  int c;

  while ((c = getopt (argc, argv, "l:pschd")) != -1){
    switch (c){
      case 'l':
        length_flag = true;
        length = (unsigned int) atoi(optarg);
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
    }
  }
  if(not length_flag or usage_flag){
    printf ("Usage: ./saw -l length [options]\n");
    printf ("Options:\n");
    printf ("\t-p Print the structures (default=false)\n");
    printf ("\t-s Print the sequences (default=false)\n");
    printf ("\t-c Print contact-maps (default=false)\n");
    printf ("\t-d Print density of states (default=false)\n");
    return 1;
  }

  model hp244( alphabet );
  general_purpose_printer print;
  
  if (print_seq_flag){
    hp244.iterateSequences(length,0,print)();
  }
  else if (print_saw_flag){
    hp244.iterateSAW(length,print)();
  }
  else if (print_cnt_flag){
    compute_contact_map<model,general_purpose_printer> contact(hp244,print);
    hp244.iterateSAW(length,contact)();
  }
  else if(print_dos_flag){
    hp244.initialize_SAW(length);
    iterate_compute_density_of_states<model,general_purpose_printer> it_dos(hp244, print);
    hp244.iterateSequences(length,0,it_dos)();
  } 
  return 0;
}
