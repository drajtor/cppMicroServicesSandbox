#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "cppmicroservices/Framework.h"
#include "cppmicroservices/FrameworkFactory.h"
#include "cppmicroservices/BundleContext.h"

//TODO change to app argument?
const std::string INPUT_FILE_REL_PATH = "../input";

int main (int argc, char** argv){

	std::cout << "Services manager" << std::endl;

	std::ifstream inputFile (INPUT_FILE_REL_PATH);
	if (!inputFile.is_open()){
		std::cerr << "can't open input file" << std::endl;
		return -1;
	}
	
	std::string line; 
	std::vector<std::string> bundleNames;
	while (std::getline(inputFile, line)){
		bundleNames.push_back(line);
	}

	if (bundleNames.size() == 0){
		std::cerr << "no bunle found in input file" << std::endl;
		return -1;
	}
	inputFile.close();

	cppmicroservices::FrameworkFactory framFact;
	auto framework = framFact.NewFramework();

	framework.Start();

	for (auto const path : bundleNames){
		framework.GetBundleContext().InstallBundles(path);	
	}

	for (auto const bundle : framework.GetBundleContext().GetBundles()){
		std::cout << 	"--ID: " << std::setw(2)  << bundle.GetBundleId() << 
				" --NAME: " << std::setw(20) << std::left << bundle.GetSymbolicName() <<
				" --SATATE: " << std::setw(10) << std::right << bundle.GetState() <<
				std::endl;
	}


	return 0;
}	
