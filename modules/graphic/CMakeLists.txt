cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Graphic)
# 
set(CMAKE_PREFIX_PATH cmake)
# find_package(cmake/FindFreetype2.cmake)
include(../../cmake/FindFreetype2.cmake)
include(../../cmake/FindPng.cmake)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Graphic directories.
set(GRAPHIC_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(GRAPHIC_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Graphic files.
file(GLOB_RECURSE GRAPHIC_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${GRAPHIC_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE GRAPHIC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${GRAPHIC_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${GRAPHIC_SOURCE_FILES})
source_group(include FILES ${GRAPHIC_INCLUDE_FILES})

# axGraphic objects library.
add_library(axGraphic OBJECT ${GRAPHIC_INCLUDE_FILES} ${GRAPHIC_SOURCE_FILES})

# Target properties.
set_target_properties(axGraphic PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axGraphic PUBLIC ${GRAPHIC_INCLUDE_DIRECTORY})
target_include_directories(axGraphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../util/include)
target_include_directories(axGraphic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../math/include)
target_include_directories(axGraphic PUBLIC ${FREETYPE2_INCLUDE_DIRS})
target_include_directories(axGraphic PUBLIC ${PNG_INCLUDE_DIRS})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# libaxGraphic library.
add_library(libaxGraphic STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axGraphic>)

# Target properties.
set_target_properties(libaxGraphic PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(libaxGraphic PUBLIC ${GRAPHIC_INCLUDE_DIRECTORY})
target_include_directories(libaxGraphic PUBLIC ${FREETYPE2_INCLUDE_DIRS})

set_target_properties(libaxGraphic PROPERTIES FOLDER axGraphic)
set_target_properties(libaxGraphic PROPERTIES OUTPUT_NAME axGraphic)
