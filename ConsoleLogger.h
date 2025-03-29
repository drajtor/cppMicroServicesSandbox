#pragma once

#include "ILogger.h"

class ConsoleLogger : public ILogger {
public:
	void logInfo (const std::string&) const override;

};
