#include "HP_224_model/model_definition.h"

template <typename get_energy>
struct compute_energy{
	get_energy& getEnergy;
	
	compute_energy( get_energy get ):getEnergy(get){};
	
	void operator()(std::string path,std::string sequence){
		
	}
}

int main(){

	hp_244::lattice_model model( {{'H','P'}} );

	return 0;
}
