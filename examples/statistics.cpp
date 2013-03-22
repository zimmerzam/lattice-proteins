#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <cmath>
#include <unistd.h>
#include "../src/saw.h"

int main(int argc, char* argv[]){
  // Option parser
	bool fold_flag = false;
  bool other_flag = false;
  bool hom_flag = false;
  bool info_flag = false;
  bool histogram_flag = false;
  bool too_much_flags = false;
	std::string foldfile = "";
	int c;

	while ((c = getopt (argc, argv, "f:oie")) != -1){
		switch (c){
			case 'f':
				fold_flag = true;
				foldfile = optarg;
				break;
      case 'o':
        hom_flag=true;
        if(other_flag)
          too_much_flags=true;
        else
          other_flag=true;
        break;
      case 'i':
        info_flag=true;
        if(other_flag)
          too_much_flags=true;
        else
          other_flag=true;
        break;
      case 'e':
        histogram_flag = true;
        if(other_flag)
          too_much_flags = true;
        else
          other_flag=true;
        break;
		}
	}
	if(not fold_flag or not other_flag or too_much_flags){
		printf ("Usage: ./fold -f fold_file [only one option]\n\
             options:\n\
             -o : print homologous structures\n\
             -i : print other info\n\
             -e : print energy histogram\n");
		return 1;
	}
  std::vector<saw> saws = readFoldFile(foldfile);
  sort( saws.begin(), saws.end(), sawSort);

  // print homologous structures
  if(hom_flag){
    homologous hom;
    for(std::vector<saw>::iterator savoid=saws.begin(); savoid!=saws.end();++savoid){
      hom[savoid->structure].push_back(*savoid);
    }
    printHomologous(hom);
  }
  // print energy histogram
  else if(histogram_flag){
    std::map< long double,std::vector<saw> > hist;
    for(std::vector<saw>::iterator savoid=saws.begin(); savoid!=saws.end();++savoid){
      hist[savoid->energy].push_back(*savoid);
    }
    for(std::map< long double,std::vector<saw> >::iterator ene = hist.begin(); ene!=hist.end(); ++ene){
      std::cout << ene->first << "  " << ene->second.size() << "  ";
      for(std::vector<saw>::iterator savoid = ene->second.begin(); savoid!=ene->second.end(); ++savoid){
        std::cout << savoid->structure << "  ";
      }
      std::cout << std::endl;
    }
  }
  // print some additional info
  else if(info_flag){
    std::cout << "minimum energy structures:\n";
    double en = saws[0].energy;
    int i = 0;
    while(en==saws[0].energy){
      std::cout << saws[i].structure << "  "
                << saws[i].sequence  << "  "
                << saws[i].energy    << std::endl;
      ++i;
      en=saws[i].energy;    
    }
    unsigned int last = saws.size()-1;
    i=0;
    en=saws[last].energy;
    std::cout << "maximum energy structures:\n";
    while(en==saws[last].energy){
      std::cout << saws[last-i].structure << "  "
                << saws[last-i].sequence  << "  "
                << saws[last-i].energy    << std::endl;
      ++i;
      en=saws[last-i].energy;
    }
  }
  return 0;
}
