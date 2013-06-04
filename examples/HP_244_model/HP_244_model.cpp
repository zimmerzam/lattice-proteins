#include "model_definition.h"
#include <array>
#include <getopt.h>

using namespace hp_244;

struct general_purpose_printer{
	void operator()(std::list<std::string> kwargs){
  	for(std::list<std::string>::iterator it = kwargs.begin(); it!=kwargs.end();++it){
			std::cout << *it << "  ";
		}
		std::cout << std::endl;
	}
} print;

template <typename Model, typename Functor>
struct compute_contact_map: public iterate<Functor>{
  typename Model::contact_map_type (Model::*pt2Member)(const std::string&);
  Model* model;
  compute_contact_map( Model& mdl, Functor& todo) : iterate<Functor>::iterate(0,0,0,0,todo), pt2Member( &Model::getContactMap ){
    model = &mdl;
  };

  void operator()(typename iterate<Functor>::kwargs_type kwargs){
    typename Model::contact_map_type cnt = (model->getContactMap)(kwargs.front());
    kwargs.push_back(cnt.toString());
    iterate<Functor>::todo(kwargs);
	}
};

int main(int argc,char* argv[]){
	// Option parser
	bool length_flag = false;
	bool print_saw_flag = false, print_seq_flag = false, print_cnt_flag = false;
	bool usage_flag = false;
	unsigned int length = 0;
	int c;

	while ((c = getopt (argc, argv, "l:psch")) != -1){
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
		return 1;
	}

  model hp244( alphabet );
  
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
  return 0;
}
