cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Attribute)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Property directories.
set(ATTRIBUTE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(ATTRIBUTE_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)
set(ATTRIBUTE_RESOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resource)

# Property files.
file(GLOB ATTRIBUTE_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_INCLUDE_DIRECTORY}/*.hpp)

file(GLOB ATTRIBUTE_SOURCE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/*.cpp)

# Property json files.
file(GLOB ATTRIBUTE_JSON_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/json/*.hpp)

file(GLOB ATTRIBUTE_JSON_SOURCE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/json/*.cpp)

# Property xml files.
file(GLOB ATTRIBUTE_XML_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/xml/*.hpp)

file(GLOB ATTRIBUTE_XML_SOURCE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/xml/*.cpp)

# Rapidjson include files.
file(GLOB_RECURSE ATTRIBUTE_RAPIDJSON_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/json/rapidjson/*.h)

# Rapidxml include files.
file(GLOB_RECURSE ATTRIBUTE_RAPIDXML_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_SOURCE_DIRECTORY}/xml/rapidxml/*.hpp)

source_group(include FILES ${ATTRIBUTE_INCLUDE_FILES})
source_group(source FILES ${ATTRIBUTE_SOURCE_FILES})

source_group("source\\json" FILES ${ATTRIBUTE_JSON_INCLUDE_FILES} ${ATTRIBUTE_JSON_SOURCE_FILES})
source_group("source\\xml" FILES ${ATTRIBUTE_XML_INCLUDE_FILES} ${ATTRIBUTE_XML_SOURCE_FILES})

source_group(rapidjson FILES ${ATTRIBUTE_RAPIDJSON_INCLUDE_FILES})
source_group(rapidxml FILES ${ATTRIBUTE_RAPIDXML_INCLUDE_FILES})

# Resources.
file(GLOB_RECURSE ATTRIBUTE_RESOURCES_FILES 
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_RESOURCE_DIRECTORY}/*.json
	${ATTRIBUTE_RESOURCE_DIRECTORY}/*.xml)

set_source_files_properties(${ATTRIBUTE_RESOURCES_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# Property library.
add_library(axAttribute OBJECT 
	${ATTRIBUTE_INCLUDE_FILES} ${ATTRIBUTE_SOURCE_FILES}
	${ATTRIBUTE_JSON_INCLUDE_FILES} ${ATTRIBUTE_JSON_SOURCE_FILES}
	${ATTRIBUTE_XML_INCLUDE_FILES} ${ATTRIBUTE_XML_SOURCE_FILES}
	${ATTRIBUTE_RESOURCES_FILES})

# Target properties.
set_target_properties(axAttribute PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

target_include_directories(axAttribute PUBLIC ${ATTRIBUTE_INCLUDE_DIRECTORY})

target_include_directories(axAttribute PUBLIC ${ATTRIBUTE_SOURCE_DIRECTORY}/json/)
target_include_directories(axAttribute PUBLIC ${ATTRIBUTE_SOURCE_DIRECTORY}/json/rapidjson)

target_include_directories(axAttribute PUBLIC ${ATTRIBUTE_SOURCE_DIRECTORY}/xml/)
target_include_directories(axAttribute PUBLIC ${ATTRIBUTE_SOURCE_DIRECTORY}/xml/rapidxml)

target_include_directories(axAttribute PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../util/include)

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axProperty library.
add_library(libaxAttribute STATIC 
			${EMPTY_FILE}
			$<TARGET_OBJECTS:axAttribute>)

# Target properties.
set_target_properties(libaxAttribute PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

set_target_properties(libaxAttribute PROPERTIES FOLDER axAttribute)
set_target_properties(libaxAttribute PROPERTIES OUTPUT_NAME axAttribute)

file(GLOB_RECURSE ATTRIBUTE_INSTALL_INCLUDE_FILES  
	${CMAKE_CURRENT_SOURCE_DIR} 
	${ATTRIBUTE_INCLUDE_DIRECTORY}/*.hpp)

install(FILES ${ATTRIBUTE_INSTALL_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxAttribute DESTINATION /usr/local/lib/)

# #------------------------------------------------------------------------------
# # Example
# #------------------------------------------------------------------------------
# add_executable(valid ${CMAKE_CURRENT_SOURCE_DIR}/example/valid.cpp)

# set_target_properties(valid PROPERTIES FOLDER axProperty/example)
# target_include_directories(valid PUBLIC ${PROPERTY_INCLUDE_DIRECTORY})
# target_link_libraries(valid axProperty)

