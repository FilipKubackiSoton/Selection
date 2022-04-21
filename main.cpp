#include <iostream>
#include "MbRandom.h"
#include "measure.h"
#include "path.h"
#include "settings.h"
#include "mcmc.h"
#include "popsize.h"
#include <stdio.h>
#include <dirent.h>
#include <sstream>
#include <string>
#include <fstream>
#include <string.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

#include<algorithm>

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

// trim from left
inline std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(0, s.find_first_not_of(t));
    return s;
}

// trim from right
inline std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v")
{
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}

// trim from left & right
inline std::string& trim(std::string& s, const char* t = " \t\n\r\f\v")
{
    return ltrim(rtrim(s, t), t);
}

bool hasEnding (std::string const &fullString, std::string const &ending) {
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

int main (int argc, char * const argv[]) {

	std::vector<std::string> arguments_i;
	std::vector<char*> cstrings_i ;
	arguments_i = {"./sr", "-D", "tmp", "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", "tmp"};
	for(auto& str : arguments_i){
		cstrings_i.push_back(const_cast<char*> (str.c_str()));
	}

	settings mySettings((int)cstrings_i.size(), cstrings_i.data());
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

			std::string fname = "input_1000.csv";
			//cout<<"Enter the file name: ";
			//cin>>fname;
		
			std::vector<std::vector<std::string>> content;
			std::vector<std::string> row;
			std::string line, word;
		
			std::fstream file (fname, std::ios::in);
			if(file.is_open())
			{
				while(std::getline(file, line))
				{
					row.clear();
		
					std::stringstream str(line);
		
					while(std::getline(str, word, ','))
						row.push_back(trim(word));
					content.push_back(row);
				}
			}
			else
				std::cout<<"Could not open the file\n";
			

			for(int i=1;i<content.size();i++)
				{
					// write to file 

					std::string filename = content[i][1]+".txt";
					std::ofstream MyFile(filename);
					MyFile << content[i][2] << "\t" << content[i][2+1] 		<< "\t" << -6123 	<< "\t" << -5500 << "\n";
					MyFile << content[i][4] << "\t" << content[i][4+1] 		<< "\t" << -5535 	<< "\t" << -4906 << "\n";
					MyFile << content[i][6] << "\t" << content[i][6+1] 		<< "\t" << -5051 	<< "\t" << -4240 << "\n";
					MyFile << content[i][8] << "\t" << content[i][8+1] 		<< "\t" << -4507 	<< "\t" << -3935 << "\n";
					MyFile << content[i][10] << "\t" << content[i][10+1] 	<< "\t" << -4001 	<< "\t" << -3461 << "\n";
					MyFile << content[i][12] << "\t" << content[i][12+1] 	<< "\t" << -3517 	<< "\t" << -3013 << "\n";
					MyFile << content[i][14] << "\t" << content[i][14+1] 	<< "\t" << -3044 	<< "\t" << -2471 << "\n";
					MyFile << content[i][16] << "\t" << content[i][16+1] 	<< "\t" << -2527 	<< "\t" << -2045 << "\n";
					MyFile << content[i][18] << "\t" << content[i][18+1] 	<< "\t" << -1947 	<< "\t" << -1550 << "\n";
					MyFile << content[i][20] << "\t" << content[i][20+1] 	<< "\t" << -1504 	<< "\t" << -971 << "\n";
					MyFile << content[i][22] << "\t" << content[i][22+1] 	<< "\t" << -1094 	<< "\t" << -492 << "\n";
					MyFile << content[i][24] << "\t" << content[i][24+1] 	<< "\t" << -400 	<< "\t" << -400 << "\n";
					MyFile.close();

					// compute 
					std::vector<std::string> arguments = {"./sr", "-D", filename, "-G", "25", "-N", "10000", "-n", "500000", "-d", "0.001", "-F", "20", "-f", "1000", "-s", "100", "-P", "constant.pop", "-e", "8067", "-a", "-o", content[i][1]};

					std::vector<char*> argvv;
					for (const auto& argg : arguments)
						argvv.push_back((char*)argg.data());
					argvv.push_back(nullptr);

					std::cout<< argvv[2]<<std::endl;
					
					settings mySettings(argvv.size() - 1, argvv.data());
					MbRandom* rr = new MbRandom(mySettings.get_seed());
					mcmc myMCMC(mySettings, rr);

					// remove file 

					char * tab2 = new char [filename.length()+1];
					strcpy (tab2, filename.c_str());

					if( std::remove( tab2 ) != 0 )
						std::perror( "Error deleting file" );
					else
						std::puts( "File successfully deleted" );
					
				};		
			}

		
	} else {
		std::cout << "No task specified" << std::endl;
		std::cout << "-b x0,xt,gamma,t for bridge path" << std::endl;
		std::cout << "-X x0,x1,...,xn -N n0,n1,...nn -T t0,t1,...tn for mcmc with just allele frequencies" << std::endl;
	}
		
	delete r;



}