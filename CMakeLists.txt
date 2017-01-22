cmake_minimum_required(VERSION 3.5.0)

# Prevent from running cmake in root directory.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Source and build directories cannot be the same.")
endif ()

option(BUILD_EXAMPLES "Build with examples." ON)

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

# Dependencies
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

# Modules.
add_subdirectory(modules/util)
add_subdirectory(modules/event)
add_subdirectory(modules/attribute)
add_subdirectory(modules/os)
add_subdirectory(modules/graphic)
add_subdirectory(modules/core)
add_subdirectory(modules/widget)

# Generate empty cpp file when generating Xcode projects.
# Xcode won't build properly without an actual source file in the cmake add_library command.
if(${CMAKE_GENERATOR} STREQUAL Xcode)
	file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
	file(GLOB EMPTY_FILE ${CMAKE_CURRENT_BINARY_DIR}/empty.cpp)
endif()

# Create static library.
add_library(${PROJECT_NAME} STATIC
	        ${EMPTY_FILE}
	        $<TARGET_OBJECTS:axUtil>
	        $<TARGET_OBJECTS:axEvent>
			$<TARGET_OBJECTS:axAttribute>
			$<TARGET_OBJECTS:axOS>
			$<TARGET_OBJECTS:axGraphic>
			$<TARGET_OBJECTS:axCore>
			$<TARGET_OBJECTS:axWidget>)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

# Create dynamic library.
add_library(axLibDyn SHARED
	        ${EMPTY_FILE}
	        $<TARGET_OBJECTS:axUtil>
	        $<TARGET_OBJECTS:axEvent>
			$<TARGET_OBJECTS:axAttribute>
			$<TARGET_OBJECTS:axOS>
			$<TARGET_OBJECTS:axGraphic>
			$<TARGET_OBJECTS:axCore>
			$<TARGET_OBJECTS:axWidget>)

set_target_properties(axLibDyn PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

set_target_properties(axLibDyn PROPERTIES OUTPUT_NAME axlib)

# Link Dependencies
target_link_libraries(axLibDyn ${PNG_LIBRARY})
target_link_libraries(axLibDyn  ${FREETYPE_LIBRARY})
target_link_libraries(axLibDyn "-framework Cocoa")
target_link_libraries(axLibDyn "-framework OpenGL")

# Examples.
if (BUILD_EXAMPLES)
	add_subdirectory(example/example01)
	add_subdirectory(example/blank)
	add_subdirectory(example/widget)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION /usr/local/lib/)
install(TARGETS axLibDyn DESTINATION /usr/local/lib/)

