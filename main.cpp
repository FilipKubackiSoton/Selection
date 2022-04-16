#include <iostream>
#include "MbRandom.h"
#include "measure.h"
#include "path.h"
#include "settings.h"
#include "mcmc.h"
#include "popsize.h"
#include <stdio.h>
#include <dirent.h>

// void run_selection(std::vector<std::string> arguments){
// 	//std::vector<std::string> arguments = {"./sr", "-D", file_name, "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", file_name};

// 	std::vector<char*> argvv;
// 	for (const auto& arg : arguments)
// 		argvv.push_back((char*)arg.data());
// 	argvv.push_back(nullptr);

// 	settings mySettings(argvv.size() - 1, argvv.data());
// 	MbRandom* rr = new MbRandom(mySettings.get_seed());
	
// 	//std::cout << entry->d_name<<" - " << arguments[2] << " - " << mySettings.get_baseName() <<std::endl;
	
// 	mcmc myMCMC(mySettings,rr);
// 	delete rr;

// }

void run_test(std::string file_name){
	std::vector<std::string> arguments;
	std::vector<char*> cstrings ;
	arguments = {"./sr", "-D", file_name, "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", file_name};
	for(auto& str : arguments){
		cstrings.push_back(const_cast<char*> (str.c_str()));
	}

	settings mySettings((int)cstrings.size(), cstrings.data());
	MbRandom* r = new MbRandom(mySettings.get_seed());
	mcmc myMCMC(mySettings, r);
}

int main (int argc, char * const argv[]) {

	settings mySettings(argc, argv);
	MbRandom* r = new MbRandom(mySettings.get_seed());

	if (mySettings.get_p()) {
		mySettings.print();
	}
	
	if (mySettings.get_bridge()) {
		wfMeasure myWF(r,0);
		std::vector<double> pars = mySettings.parse_bridge_pars();
        std::cerr << "Creating bridge with (x0, xt, gamma, t) = (" << pars[0] << ", " << pars[1]
            << ", " << pars[2] << ", " << pars[3] << ")" << std::endl;
		myWF.set_num_test(mySettings.get_num_test());
		myWF.set_gamma(pars[2]);
		path* myPath = new path(myWF.fisher(pars[0]),myWF.fisher(pars[1]),0,pars[3],&myWF,mySettings);
		myWF.invert_path(myPath);
		if (mySettings.get_output_tsv()) {
			myPath->print_tsv(std::cout) ;
		} else {
			myPath->print(std::cout);
		}
		delete myPath;
	} else if (mySettings.get_mcmc()) {
		if (mySettings.get_linked()) {
			
		} else {
				std::vector<std::string> s = {"data/1.txt", "data/2.txt", "data/3.txt"};

			for(int i = 0; i <= 2; i++){
				
//				std::cout<<i<<" - "<< argv[i]<<std::endl;
				
				std::vector<std::string> arguments = {"./sr", "-D", s[i], "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", s[i]};

				std::vector<char*> argvv;
				for (const auto& arg : arguments)
					argvv.push_back((char*)arg.data());
				argvv.push_back(nullptr);

				std::cout<<i<<" - "<< argv[2] << " - "<< argvv[2]<<std::endl;
				
				settings mySettings(argvv.size() - 1, argvv.data());
				MbRandom* rr = new MbRandom(mySettings.get_seed());
				//argv['FILENMAE'] = FILE
				//settings mySettings(argc, argv);
				//MbRandom* r = new MbRandom(mySettings.get_seed());


				mcmc myMCMC(mySettings, rr);
			}
				
			}

		
	} else {
		std::cout << "No task specified" << std::endl;
		std::cout << "-b x0,xt,gamma,t for bridge path" << std::endl;
		std::cout << "-X x0,x1,...,xn -N n0,n1,...nn -T t0,t1,...tn for mcmc with just allele frequencies" << std::endl;
	}
		
	delete r;
	//settings mySettings(argc, argv);



}
/*
	//std::cout<<"ARGC: "<<argc<<std::endl;

 	// for(int i = 0; i < argc; ++i)
    //     std::cout << argv[i] << '\n';

	//std::cout<<"ARGV: "<<argv<<std::endl;
	settings mySettings(argc, argv);
	
	MbRandom* r = new MbRandom(mySettings.get_seed());
	
	if (mySettings.get_p()) {
		mySettings.print();
	}
	
	if (mySettings.get_bridge()) {
		wfMeasure myWF(r,0);
		std::vector<double> pars = mySettings.parse_bridge_pars();
        // std::cerr << "Creating bridge with (x0, xt, gamma, t) = (" << pars[0] << ", " << pars[1]
        //     << ", " << pars[2] << ", " << pars[3] << ")" << std::endl;
		myWF.set_num_test(mySettings.get_num_test());
		myWF.set_gamma(pars[2]);
		path* myPath = new path(myWF.fisher(pars[0]),myWF.fisher(pars[1]),0,pars[3],&myWF,mySettings);
		myWF.invert_path(myPath);
		// if (mySettings.get_output_tsv()) {
		// 	myPath->print_tsv(std::cout) ;
		// } else {
		// 	myPath->print(std::cout);
		// }
		delete myPath;
	} else if (mySettings.get_mcmc()) {
		if (mySettings.get_linked()) {
			
		} else {
			//settings mySettings(argc, argv);
			//MbRandom* r = new MbRandom(mySettings.get_seed());
			//mcmc myMCMC(mySettings,r);


			struct dirent *entry = nullptr;
			DIR *dp = nullptr;

			dp = opendir(argc > 1 ? "data" : "/");
			if (dp != nullptr) {
				while ((entry = readdir(dp))){
					std::string file_name = entry->d_name;
					// skip hiden files and dirs
					if(file_name == "." || file_name == "..")
						continue;
					printf ("%s\n", entry->d_name);
					
					// initialize vector with cmd arguments 
					std::vector<std::string> arguments = {"./sr", "-D", file_name, "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", file_name};

					run_selection(arguments);
					
				}
					
			closedir(dp);
			}

			
		}
	} else {
		// std::cout << "No task specified" << std::endl;
		// std::cout << "-b x0,xt,gamma,t for bridge path" << std::endl;
		// std::cout << "-X x0,x1,...,xn -N n0,n1,...nn -T t0,t1,...tn for mcmc with just allele frequencies" << std::endl;
	}
		
	delete r;
}


*/