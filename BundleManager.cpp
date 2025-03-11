#include <fstream>
#include <iomanip>
#include <iostream>

#include "BundleManager.h"
#include "cppmicroservices/BundleContext.h"

using namespace cppmicroservices;

TODO powalczyc z duplikacja kodu (petle przeszukujace bundle)
TODO dodac wielowatkowasc



void BundleManager::readAvailableBundles(const std::string& inputFile){
	std::cout << "Services manager" << std::endl;

	std::ifstream file (inputFile);
	if (!file.is_open()){
		throw BundleManagerException("can't open input file");
	}
	
	std::string line; 
	while (std::getline(file, line)){
		bundlesToLoad.push_back(line);
	}

	if (bundlesToLoad.size() == 0){
		throw BundleManagerException("no bundle found in input file"); 
	}
}

void BundleManager::installAvailableBundles() const{
	try {
		for (const auto& path : bundlesToLoad){
			framework->GetBundleContext().InstallBundles(path);	
		}

	}catch(const std::runtime_error &e){
		throw BundleManagerException (std::string("Runtime exception: ") + e.what());
	}catch (const std::invalid_argument &e){
		throw BundleManagerException (std::string("Invalid argument exception: ") + e.what());
	}catch(const std::logic_error &e){
		throw BundleManagerException (std::string("Logic exception: ") +  e.what());
	}	
}

void BundleManager::startBundles() const{
	auto bundles = framework->GetBundleContext().GetBundles();
	for (auto& bundle : bundles){
		if (bundle.GetState() == Bundle::STATE_INSTALLED){
			bundle.Start();
		}
	}
}

void BundleManager::startBundles(const std::vector<std::string>& bundlesToStart) const{
	auto bundles = framework->GetBundleContext().GetBundles();
	for (auto& bundle : bundles){
		for (const auto& bundleName : bundlesToStart){
			if (bundle.GetSymbolicName() == bundleName && bundle.GetState() == Bundle::STATE_INSTALLED){
				bundle.Start();
			}
		}
	}
}

void BundleManager::stopBundles() const{
	auto bundles = framework->GetBundleContext().GetBundles();
	for (auto& bundle : bundles){
		if (bundle.GetState() == Bundle::STATE_ACTIVE){
			bundle.Stop();
		}
	}
}
void BundleManager::stopBundles(const std::vector<std::string>& bundlesToStop) const{
	auto bundles = framework->GetBundleContext().GetBundles();
	for (auto& bundle : bundles){
		for (const auto& bundleName : bundlesToStop){
			if (bundle.GetSymbolicName() == bundleName && bundle.GetState() == Bundle::STATE_ACTIVE){
				bundle.Stop();
			}
		}
	}	
}
void BundleManager::printServicesStatus() const{
	for (const auto& bundle : framework->GetBundleContext().GetBundles()){
		std::cout << 	"--ID: " << std::setw(2)  << bundle.GetBundleId() << 
				" --NAME: " << std::setw(20) << std::left << bundle.GetSymbolicName() <<
				" --SATATE: " << std::setw(10) << std::right << bundle.GetState() <<
				std::endl;
	}
}


