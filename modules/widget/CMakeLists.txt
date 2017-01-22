cmake_minimum_required(VERSION 3.5.0)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Widget)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Widget directories.
set(WIDGET_INCLUDE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(WIDGET_SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/source)

# Widget files.
file(GLOB_RECURSE WIDGET_INCLUDE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${WIDGET_INCLUDE_DIRECTORY}/*.hpp)
file(GLOB_RECURSE WIDGET_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${WIDGET_SOURCE_DIRECTORY}/*.cpp)

# File groups.
source_group(source FILES ${WIDGET_SOURCE_FILES})
source_group(include FILES ${WIDGET_INCLUDE_FILES})

# axWidget objects library.
add_library(axWidget OBJECT ${WIDGET_INCLUDE_FILES} ${WIDGET_SOURCE_FILES})

# Target properties.
set_target_properties(axWidget PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Include directory.
target_include_directories(axWidget PUBLIC ${WIDGET_INCLUDE_DIRECTORY})
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../core/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../core/osx)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../util/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../math/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../event/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../os/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../attribute/include)
target_include_directories(axWidget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../graphic/include)
target_include_directories(axWidget PUBLIC ${PNG_INCLUDE_DIRS})

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# axWidgetLib library.
add_library(libaxWidget STATIC ${EMPTY_FILE} $<TARGET_OBJECTS:axWidget>)

# Target properties.
set_target_properties(libaxWidget PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

set_target_properties(libaxWidget PROPERTIES FOLDER axWidget)
set_target_properties(libaxWidget PROPERTIES OUTPUT_NAME axWidget)

install(FILES ${WIDGET_INCLUDE_FILES} DESTINATION /usr/local/include/axlib/)
install(TARGETS libaxWidget DESTINATION /usr/local/lib/)
