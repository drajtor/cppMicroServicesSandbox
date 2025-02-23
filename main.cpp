#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "cppmicroservices/Framework.h"
#include "cppmicroservices/FrameworkFactory.h"
#include "cppmicroservices/BundleContext.h"
#include "cppmicroservices/FrameworkEvent.h"
#include "cppmicroservices/ServiceReference.h"

#include "dictionaryService/IDictionaryService.h"

using namespace cppmicroservices;

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

	FrameworkFactory framFact;
	auto framework = framFact.NewFramework();

	framework.Start();

	try {
		for (auto const path : bundleNames){
			framework.GetBundleContext().InstallBundles(path);	
		}

	}catch(const std::runtime_error &e){
		std::cerr << "Runtime exception: " << e.what() << std::endl;
		return (-1);
	}catch (const std::invalid_argument &e){
		std::cerr << "Invalid argument exception: " << e.what() << std::endl;
		return (-1);
	}catch(const std::logic_error &e){
		std::cerr << "Logic exception: " << e.what() << std::endl;
		return (-1);
	}	


	for (auto bundle : framework.GetBundleContext().GetBundles()){
		if (bundle.GetSymbolicName() == "dictionary_service"){
			bundle.Start();
		}
	}
	
	for (auto const bundle : framework.GetBundleContext().GetBundles()){
		std::cout << 	"--ID: " << std::setw(2)  << bundle.GetBundleId() << 
				" --NAME: " << std::setw(20) << std::left << bundle.GetSymbolicName() <<
				" --SATATE: " << std::setw(10) << std::right << bundle.GetState() <<
				std::endl;
	}


	ServiceReference serviceReference = framework.GetBundleContext().GetServiceReference<IDictionaryService>();
	if (serviceReference){
		std::shared_ptr<IDictionaryService> dictionaryService = framework.GetBundleContext().GetService(serviceReference);
		std::string word = "Kaka";
		std::cout << " word found? " << dictionaryService->checkWord(word) << std::endl;
	}else{
		std::cout << "Service reference for dictionary service not found" << std::endl;
	}

	framework.Stop();
	switch (auto event = framework.WaitForStop(std::chrono::seconds(2)).GetType(); event){
		case FrameworkEvent::FRAMEWORK_STOPPED:
			std::cout << "Framework stopped on demoand" << std::endl;
			break;
		case FrameworkEvent::FRAMEWORK_ERROR:
			std::cout << "Framework stopped because of an ERROR" << std::endl;
			break;
		case FrameworkEvent::FRAMEWORK_WAIT_TIMEDOUT:
			std::cout << "Framework stopped because of timeout" << std::endl;
			break;
		default:
			std::cout << "Framework stopped, not handled" << std::endl;
			break;
	}
	

	return 0;
}	
