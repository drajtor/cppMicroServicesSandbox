#include <iostream>


#include "cppmicroservices/Framework.h"
#include "cppmicroservices/FrameworkFactory.h"

int main (int argc, char** argv){

	std::cout << "Services manager" << std::endl;

	cppmicroservices::FrameworkFactory framFact;
	auto framework = framFact.NewFramework();

return 0;
}	
