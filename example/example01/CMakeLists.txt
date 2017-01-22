cmake_minimum_required(VERSION 3.5.0)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(example01)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Util files.
file(GLOB_RECURSE EXAMPLE01_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
file(GLOB_RECURSE EXAMPLE01_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# File groups.
source_group(source FILES ${EXAMPLE01_SOURCE_FILES})
source_group(include FILES ${EXAMPLE01_INCLUDE_FILES})

add_executable(example01 ${EXAMPLE01_SOURCE_FILES} ${EXAMPLE01_INCLUDE_FILES})

# Target properties.
set_target_properties(libaxUtil PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

target_include_directories(example01 PUBLIC 
		${UTIL_INCLUDE_DIRECTORY}
		${EVENT_INCLUDE_DIRECTORY})

set_target_properties(example01 PROPERTIES FOLDER example/)

target_link_libraries(example01 libaxUtil libaxEvent libaxGraphic)
