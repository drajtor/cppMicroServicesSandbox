#include <string>
#include <iostream>

#include "ConsoleLogger.h"

void ConsoleLogger::logInfo (const std::string message) const{
	std::cout << message << std::endl;	

}

