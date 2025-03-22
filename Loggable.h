#pragma once

#include <memory>
#include "ILogger.h"

class Loggable {
protected:
	std::shared_ptr<ILogger> logger;

public:
	explicit Loggable (std::shared_ptr<ILogger> logger) : logger(logger){};
	virtual ~Loggable() = default;
};
