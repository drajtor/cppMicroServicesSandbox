#include <string>
#include <algorithm>

#include "cppmicroservices/BundleActivator.h"
#include "cppmicroservices/BundleContext.h"
#include "cppmicroservices/ServiceProperties.h"
#include "IDictionaryService.h"

using namespace cppmicroservices;

namespace {

	class Activator : public BundleActivator {
		
		class DictionaryImpl : public IDictionaryService{

			std::set<std::string> dictionary;
		public:
			DictionaryImpl (){
				dictionary.insert("kaka");
				dictionary.insert("demona");
				dictionary.insert("i");
				dictionary.insert("juz");
			}
		
			bool checkWord (const std::string& word){
				std::string iword(word);

				std::transform(iword.begin(), iword.end(), iword.begin(), ::tolower);

				return dictionary.find(iword) != dictionary.end();
			}
		};

	public:
			
	void Start(BundleContext bundleContext){
		std::shared_ptr<IDictionaryService> service = std::make_shared<DictionaryImpl>();
		ServiceProperties serviceProperties;
		serviceProperties["Language"] = std::string("English");
		bundleContext.RegisterService<IDictionaryService>(service, serviceProperties);	
	}

	void Stop(BundleContext){}

	};
};

CPPMICROSERVICES_EXPORT_BUNDLE_ACTIVATOR(Activator)

