#include "BundleManager.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "cppmicroservices/FrameworkFactory.h"

class MockLogger : public ILogger{
	MOCK_METHOD (void, logInfo, (const std::string& message), (const, override));
};

class MockFramework : public cppmicroservices::Framework {
public:
	MockFramework(const cppmicroservices::Framework& framework) : cppmicroservices::Framework(framework) {}
};


TEST (BundleManagerTest, ReadAvailableBundles_ValidInput) {
	auto logger = std::make_shared<MockLogger>();
	auto framework = cppmicroservices::FrameworkFactory().NewFramework();

	auto frameworkMock = std::make_shared<MockFramework>(framework);

	BundleManager manager(logger, frameworkMock);
	const std::string inputFile = "../testInput";
	EXPECT_NO_THROW(manager.readAvailableBundles(inputFile));

}
