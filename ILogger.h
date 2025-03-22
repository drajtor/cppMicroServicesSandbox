#pragma once

#include <string>

class ILogger {
public:
	virtual void logInfo (const std::string) const = 0;

};
