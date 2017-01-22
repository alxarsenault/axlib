cmake_minimum_required(VERSION 3.5.0)

# Prevent from running cmake in root folder.
if (CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "cmake needs to be called in a sub directory.")
endif ()

project(Widget)

# Use folder.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Widget files.
file(GLOB_RECURSE Widget_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB_RECURSE Widget_XIB_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/*.xib)

# Widget objects library.
add_executable(Widget MACOSX_BUNDLE ${Widget_SOURCE_FILES} ${Widget_XIB_FILES})

# Target properties.
set_target_properties(Widget PROPERTIES LINKER_LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "-fPIC -std=c++14 ${CMAKE_CXX_FLAGS}")

set_source_files_properties(${Widget_XIB_FILES} PROPERTIES MACOSX_PACKAGE_LOCATION Resources)

# Set the OS X Bundle specific CMake variables which will be used to populate the plist for
# the application bundle
set(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME}")
set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.ax.Widget")
set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_NAME} Version 0.1")
set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
set(MACOSX_BUNDLE_SHORT_VERSION_STRING 0.1)
set(MACOSX_BUNDLE_BUNDLE_VERSION 0.1)
set(MACOSX_BUNDLE_COPYRIGHT "Copyright 2016. All Rights Reserved.")

# These variables are specific to our plist and are NOT standard CMake variables
set(MACOSX_BUNDLE_NSMAIN_NIB_FILE "MainMenu")
set(MACOSX_BUNDLE_NSPRINCIPAL_CLASS "NSApplication")

# set_target_properties(Widget PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/plist.in)
# Set a custom plist file for the app bundle
set_target_properties(Widget PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist)

set_target_properties(Widget PROPERTIES FOLDER example/)

# Include directory.
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/core/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/core/osx)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/util/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/event/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/os/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/attribute/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/graphic/include)
target_include_directories(Widget PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/widget/include)
target_include_directories(Widget PUBLIC ${PNG_INCLUDE_DIRS})

target_link_libraries(Widget axlib)
target_link_libraries(Widget ${PNG_LIBRARY} ${FREETYPE_LIBRARY})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework OpenGL")

