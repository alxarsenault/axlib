cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Math)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Math directories.
set(MATH_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(MATH_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Math files.
file(GLOB_RECURSE MATH_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${MATH_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE MATH_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${MATH_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${MATH_SOURCE_FILES})
source_group(include FILES ${MATH_INCLUDE_FILES})

# axMath objects library.
add_library(axMath OBJECT ${MATH_INCLUDE_FILES} ${MATH_SOURCE_FILES})

# Target properties.
set_target_properties(axMath PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axMath PUBLIC ${MATH_INCLUDE_DIRECTORY})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axMathLib library.
add_library(libaxMath STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axMath>)

# Target properties.
set_target_properties(libaxMath PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(libaxMath PUBLIC ${MATH_INCLUDE_DIRECTORY})

set_target_properties(libaxMath PROPERTIES FOLDER axMath)
set_target_properties(libaxMath PROPERTIES OUTPUT_NAME axMath)