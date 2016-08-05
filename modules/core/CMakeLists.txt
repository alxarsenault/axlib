cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Core)

include(../../cmake/FindFreetype2.cmake)
include(../../cmake/FindPng.cmake)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Core directories.
set(CORE_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CORE_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Core files.
file(GLOB_RECURSE CORE_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CORE_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE CORE_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CORE_SOURCE_DIRECTORY}/*.cpp)

file(GLOB_RECURSE CORE_OSX_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/core/osx/*.hpp)
file(GLOB_RECURSE CORE_OSX_OBJC_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/core/osx/*.h)
file(GLOB_RECURSE CORE_OSX_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/core/osx/*.cpp)
file(GLOB_RECURSE CORE_OSX_OBJC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/core/osx/*.mm)

# File groups.
source_group(source FILES ${CORE_SOURCE_FILES})
source_group(include FILES ${CORE_INCLUDE_FILES})

source_group("core\\source" FILES ${CORE_OSX_SOURCE_FILES})
source_group("core\\source" FILES ${CORE_OSX_OBJC_SOURCE_FILES})
source_group("core\\include" FILES ${CORE_OSX_INCLUDE_FILES})
source_group("core\\include" FILES ${CORE_OSX_OBJC_INCLUDE_FILES})

# axCore objects library.
add_library(axCore OBJECT 
	${CORE_INCLUDE_FILES} ${CORE_SOURCE_FILES} 
	${CORE_OSX_INCLUDE_FILES} ${CORE_OSX_SOURCE_FILES} 
	${CORE_OSX_OBJC_INCLUDE_FILES} ${CORE_OSX_OBJC_SOURCE_FILES})

# Target properties.
set_target_properties(axCore PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axCore PUBLIC ${CORE_INCLUDE_DIRECTORY})
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/core/osx/)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../util/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../math/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../event/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../os/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../attribute/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../graphic/include)
target_include_directories(axCore PUBLIC ${FREETYPE2_INCLUDE_DIRS})
target_include_directories(axCore PUBLIC ${PNG_INCLUDE_DIRS})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axCoreLib library.
add_library(libaxCore STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axCore>)

# Target properties.
set_target_properties(libaxCore PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axCore PUBLIC ${CORE_INCLUDE_DIRECTORY})
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../util/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../math/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../event/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../os/include)
target_include_directories(axCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../graphic/include)
target_include_directories(axCore PUBLIC ${FREETYPE2_INCLUDE_DIRS})
target_include_directories(axCore PUBLIC ${PNG_INCLUDE_DIRS})

set_target_properties(libaxCore PROPERTIES FOLDER axCore)
set_target_properties(libaxCore PROPERTIES OUTPUT_NAME axCore)

install(FILES ${CORE_INCLUDE_FILES} ${CORE_OSX_INCLUDE_FILES} ${CORE_OSX_OBJC_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxCore DESTINATION /usr/local/lib/)
