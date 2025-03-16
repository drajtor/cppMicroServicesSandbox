#include <fstream>
#include <iomanip>
#include <iostream>
#include <functional>
#include <optional>

#include "BundleManager.h"
#include "cppmicroservices/BundleContext.h"

using namespace cppmicroservices;

void BundleManager::readAvailableBundles(const std::string& inputFile){
 	std::lock_guard<std::mutex> lock(m_mutex);	
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
	std::lock_guard<std::mutex> lock (m_mutex);
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

void BundleManager::forEachBundle (const Bundle::State state, 
				   const std::function<void(Bundle&)>& action, 
				   const std::optional<std::vector<std::string>>& bundleNames
				   ) const{
	std::lock_guard<std::mutex> lock (m_mutex);
	auto bundles = framework->GetBundleContext().GetBundles();
	for (auto& bundle : bundles){
		if (bundle.GetState() == state){
			if (!bundleNames || std::find(bundleNames->begin(), bundleNames->end(), bundle.GetSymbolicName()) != bundleNames->end()){
				action(bundle);
			}
		}
	}
}

void BundleManager::startBundles() const{
	forEachBundle(Bundle::STATE_INSTALLED, [](Bundle& bundle){
		bundle.Start();
		}, std::nullopt);
}

void BundleManager::startBundles(const std::vector<std::string>& bundlesToStart) const{
	forEachBundle(Bundle::STATE_INSTALLED, [](Bundle& bundle){
		bundle.Start();
		}, bundlesToStart);
}

void BundleManager::stopBundles() const{
	forEachBundle(Bundle::STATE_ACTIVE, [](Bundle& bundle){
		bundle.Stop();
		}, std::nullopt);
}
void BundleManager::stopBundles(const std::vector<std::string>& bundlesToStop) const{
	forEachBundle(Bundle::STATE_ACTIVE, [](Bundle& bundle){
		bundle.Stop();
		}, bundlesToStop);
}
void BundleManager::printServicesStatus() const{
	std::lock_guard<std::mutex> lock (m_mutex);
	for (const auto& bundle : framework->GetBundleContext().GetBundles()){
		std::cout << 	"--ID: " << std::setw(2)  << bundle.GetBundleId() << 
				" --NAME: " << std::setw(20) << std::left << bundle.GetSymbolicName() <<
				" --SATATE: " << std::setw(10) << std::right << bundle.GetState() <<
				std::endl;
	}
}


