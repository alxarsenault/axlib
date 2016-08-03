cmake_minimum_required(VERSION 3.2.1)

# Prevent from running cmake in root directory.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif ()

project(axlib)

set(CMAKE_BUILD_TYPE Debug)

# Debug output path.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Debug)

# Release output path.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Release)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/${CMAKE_SYSTEM_PROCESSOR}/Release)

# message("FOLDER :" ${PROJECT_SOURCE_DIR})
# message("FOLDER :" ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG})

# Modules.
add_subdirectory(modules/math)
add_subdirectory(modules/util)
add_subdirectory(modules/event)
add_subdirectory(modules/attribute)
add_subdirectory(modules/os)
add_subdirectory(modules/graphic)
add_subdirectory(modules/core)
add_subdirectory(modules/widget)

# Examples.
add_subdirectory(example/example01)

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

add_library(${PROJECT_NAME} STATIC 
	        ${EMPTY_FILE}
	        $<TARGET_OBJECTS:axMath>
	        $<TARGET_OBJECTS:axUtil>
	        $<TARGET_OBJECTS:axEvent>
			$<TARGET_OBJECTS:axAttribute>
			$<TARGET_OBJECTS:axOS>
			$<TARGET_OBJECTS:axGraphic>
			$<TARGET_OBJECTS:axCore>
			$<TARGET_OBJECTS:axWidget>)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")


