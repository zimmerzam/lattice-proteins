#include "model_definition.h"
#include "../../src/utils.h"
#include <array>
#include <getopt.h>

using namespace hp_244;

struct fold_sequence{
  model& hp;
  fold_sequence(model& md):hp(md){};
  void operator()(std::list<std::string> kwargs){
    std::string sequence = *kwargs.begin();
    std::set<std::string> paths = hp.space.saws[sequence.size()];
    
    std::string path;
    double min_e;
    bool is_unique;
    for(std::set<std::string>::iterator p = paths.begin(); p != paths.end(); ++p){
      double en = hp.getEnergy(*p,sequence);
      if(fabs(en-min_e)<0.0000001){
        is_unique=false;
      }
      else if(en < min_e){
        min_e = en;
        path=*p;
        is_unique = true;
      }
    }
    
    if(is_unique){
      std::cout << sequence << "  " << path << "  " << min_e << std::endl;
    }
  }
};

int main(int argc,char* argv[]){
  // Option parser
  bool length_flag = false;
  bool usage_flag = false;
  unsigned int length = 0;
  int c;

  while ((c = getopt (argc, argv, "l:h")) != -1){
    switch (c){
      case 'l':
        length_flag = true;
        length = (unsigned int) atoi(optarg);
        break;
      case 'h':
        usage_flag = true;
        break;
    }
  }
  if(not length_flag or usage_flag){
    printf ("Usage: ./saw -l length\n");
    return 1;
  }

  model hp244( alphabet );
  fold_sequence fold(hp244);
  hp244.initialize_SAW(length);
  hp244.initialize_energy_param("hp_hamiltonian.param");
  hp244.iterateSequences(length,0,fold)();
  
  return 0;
}
