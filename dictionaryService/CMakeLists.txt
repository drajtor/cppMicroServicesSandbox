cmake_minimum_required(VERSION 3.0)

set (_lib_name "dictionary_service")

set (_srcs 
	IDictionaryService.cpp
	Activator.cpp
)

# Add a special source file to the _srcs variable that
# will enable dependency checking on bundle resources.
usFunctionGetResourceSource(TARGET ${_lib_name} OUT _srcs)

# Generate bundle initialization code
usFunctionGenerateBundleInit(TARGET ${_lib_name} OUT _srcs)


add_library(${_lib_name} ${_srcs})


# Add the US_BUNDLE_NAME target property
set_property(TARGET ${_lib_name} APPEND PROPERTY US_BUNDLE_NAME ${_lib_name})

# Add the required compile definition
set_property(TARGET ${_lib_name} APPEND PROPERTY COMPILE_DEFINITIONS US_BUNDLE_NAME=${_lib_name})

# Embed the manifest file
usFunctionEmbedResources(TARGET ${_lib_name} WORKING_DIRECTORY resources FILES manifest.json)

target_link_libraries (${_lib_name} CppMicroServices)

