#pragma once

#include <string>
#include <exception>
#include <vector>

#include "cppmicroservices/Framework.h"

class BundleManagerException : public std::exception {

private:
	std::string message;

public:
	BundleManagerException(const std::string& msg) : message(msg) {}

	const char* what() const noexcept override{
		return message.c_str();
	}	
};

class BundleManager {

private:
	std::vector<std::string> bundlesToLoad;
	std::shared_ptr<cppmicroservices::Framework> framework;

public:
	explicit BundleManager(std::shared_ptr<cppmicroservices::Framework> framework) : framework(framework){}

	void readAvailableBundles(const std::string& inputFile);
	void installAvailableBundles() const;
	void startBundles() const;
	void startBundles(const std::vector<std::string>& bundlesToStart) const;
	void stopBundles() const;
	void stopBundles(const std::vector<std::string>& bundlesToStop) const;
	void printServicesStatus() const;

};
