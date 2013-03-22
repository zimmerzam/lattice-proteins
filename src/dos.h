#ifndef DENSITY_OF_STATES
#define DENSITY_OF_STATES

typedef std::map<double, double> density_states;

std::string printDensity(std::string seq, density_states density){
	std::ostringstream line;
	line << seq;
	line << "  ";
	for( density_states::iterator dns = density.begin(); dns != density.end(); ++dns ){
		line << "(";
		line << dns->first;
		line << ",";
		line << dns->second;
		line << ")  ";
	}
	line << std::endl;
	return line.str();
}

std::string printDensity(int seq, unsigned int length, density_states density){
	return printDensity( hpSeq(seq,length), density );
}

std::pair<std::string,density_states> readDensity(std::string line){
	std::istringstream iss(line);
	std::vector<std::string> tokens;
	copy( std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				std::back_inserter<std::vector<std::string> >(tokens));
	density_states density;
	std::string seq = tokens[0];
	for(unsigned int i = 1; i < tokens.size(); ++i){
		std::istringstream map(tokens[i].substr(1, tokens[i].size()-2));
		std::string x1,x2;
		std::getline(map,x1,',');
		double key = atof(x1.c_str());
		std::getline(map,x2,',');
		double value = atof(x2.c_str());
		density[key] = value;
	}
	return std::make_pair(seq,density);
}

density_states::iterator is_two_state_folder( density_states& density ){
	density_states::iterator it = density.begin(), itm = density.begin(), itp = density.begin(), last = density.end();
	--last;
	++it; ++itp; ++itp;
	for( ; it!=density.end(); ++it, ++itm, ++itp ){
		if( it != density.begin() and it != last ){ // in the middle
			double h2 = pow( itp->first - 2*it->first + itm->first, 2. )/16.;
			double sec_der = (itp->second - 2*it->second + itm->second )/h2 ;
			if(sec_der > 0)
				return it;
		}
	}
	return it;
}


#endif
