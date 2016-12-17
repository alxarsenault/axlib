cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(OS)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# OS directories.
set(OS_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(OS_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# OS files.
file(GLOB_RECURSE OS_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${OS_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE OS_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${OS_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${OS_SOURCE_FILES})
source_group(include FILES ${OS_INCLUDE_FILES})

# axOS objects library.
add_library(axOS OBJECT ${OS_INCLUDE_FILES} ${OS_SOURCE_FILES})

# Target properties.
set_target_properties(axOS PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axOS PUBLIC 
		${OS_INCLUDE_DIRECTORY} 
		${CMAKE_CURRENT_SOURCE_DIR}/../util/include
		${CMAKE_CURRENT_SOURCE_DIR}/../event/include)

message("UTIL DIRDEJHDA" ${UTIL_INCLUDE_DIRECTORY})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axOSLib library.
add_library(libaxOS STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axOS>)

# Target properties.
set_target_properties(libaxOS PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(libaxOS PUBLIC ${OS_INCLUDE_DIRECTORY} ${UTIL_INCLUDE_DIRECTORY} ${EVENT_INCLUDE_DIRECTORY})

set_target_properties(libaxOS PROPERTIES FOLDER axOS)
set_target_properties(libaxOS PROPERTIES OUTPUT_NAME axOS)

install(FILES ${OS_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxOS DESTINATION /usr/local/lib/)
