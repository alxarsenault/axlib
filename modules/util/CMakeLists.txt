cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Util)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Util directories.
set(UTIL_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(UTIL_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Util files.
file(GLOB_RECURSE UTIL_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${UTIL_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE UTIL_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${UTIL_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${UTIL_SOURCE_FILES})
source_group(include FILES ${UTIL_INCLUDE_FILES})

# axUtil objects library.
add_library(axUtil OBJECT ${UTIL_INCLUDE_FILES} ${UTIL_SOURCE_FILES})

# Target properties.
set_target_properties(axUtil PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axUtil PUBLIC ${UTIL_INCLUDE_DIRECTORY})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# libaxUtil library.
add_library(libaxUtil STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axUtil>)

# Target properties.
set_target_properties(libaxUtil PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(libaxUtil PUBLIC ${UTIL_INCLUDE_DIRECTORY})

set_target_properties(libaxUtil PROPERTIES FOLDER axUtil)
set_target_properties(libaxUtil PROPERTIES OUTPUT_NAME axUtil)

install(FILES ${UTIL_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxUtil DESTINATION /usr/local/lib/)
