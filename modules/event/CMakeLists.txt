cmake_minimum_required(VERSION 3.5.0)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Event)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Event directories.
set(EVENT_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EVENT_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Event files.
file(GLOB_RECURSE EVENT_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${EVENT_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE EVENT_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${EVENT_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${EVENT_SOURCE_FILES})
source_group(include FILES ${EVENT_INCLUDE_FILES})

# axEvent objects library.
add_library(axEvent OBJECT ${EVENT_INCLUDE_FILES} ${EVENT_SOURCE_FILES})

# Target properties.
set_target_properties(axEvent PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axEvent PUBLIC ${EVENT_INCLUDE_DIRECTORY})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axEventLib library.
add_library(libaxEvent STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axEvent>)

# Target properties.
set_target_properties(libaxEvent PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(libaxEvent PUBLIC ${EVENT_INCLUDE_DIRECTORY})

set_target_properties(libaxEvent PROPERTIES FOLDER axEvent)
set_target_properties(libaxEvent PROPERTIES OUTPUT_NAME axEvent)

install(FILES ${EVENT_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxEvent DESTINATION /usr/local/lib/)
