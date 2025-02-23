#include <string>
#include "cppmicroservices/ServiceInterface.h"

class US_ABI_EXPORT IDictionaryService {

public:
	virtual ~IDictionaryService();
	virtual bool checkWord(const std::string &word) = 0;

};
