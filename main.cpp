#include <iostream>
#include <string>

#include "cppmicroservices/Framework.h"
#include "cppmicroservices/FrameworkFactory.h"
#include "cppmicroservices/BundleContext.h"
#include "cppmicroservices/FrameworkEvent.h"
#include "cppmicroservices/ServiceReference.h"

#include "BundleManager.h"
#include "dictionaryService/IDictionaryService.h"

using namespace cppmicroservices;

//TODO change to app argument?
const std::string INPUT_FILE_REL_PATH = "../input";

int main (int argc, char** argv){
	
	FrameworkFactory framFact;
	std::shared_ptr<Framework> framework = std::make_shared<Framework>(framFact.NewFramework());
	BundleManager bundleManager(framework);	

	try{
		bundleManager.readAvailableBundles(INPUT_FILE_REL_PATH);
	}catch(BundleManagerException e){
		std::cout << e.what() << std::endl;
	}
	framework->Start();
	try{
		bundleManager.installAvailableBundles();
	} catch(BundleManagerException e){
		std::cout << e.what() << std::endl;
	}	
	
	std::vector<std::string> bundles = {"dictionary_service"};
	bundleManager.startBundles(bundles);
	bundleManager.printServicesStatus();
	
	ServiceReference serviceReference = framework->GetBundleContext().GetServiceReference<IDictionaryService>();
	if (serviceReference){
		std::shared_ptr<IDictionaryService> dictionaryService = framework->GetBundleContext().GetService(serviceReference);
		std::string word = "Kaka";
		std::cout << " word found? " << dictionaryService->checkWord(word) << std::endl;
	}else{
		std::cout << "Service reference for dictionary service not found" << std::endl;
	}

	bundleManager.stopBundles(bundles);
	bundleManager.printServicesStatus();
	framework->Stop();
	
	switch (auto event = framework->WaitForStop(std::chrono::seconds(2)).GetType(); event){
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


