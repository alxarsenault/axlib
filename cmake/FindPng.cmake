# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

# Try to find libpng.
find_path(PNG_INCLUDE_DIR png.h
		/usr/local/include/
		/usr/include/
		NO_DEFAULT_PATH)

find_library(PNG_LIBRARY
		NAMES png
		PATHS
		/usr/local/lib
		/usr/lib
		/opt/local/lib
		)

message(${PNG_INCLUDE_DIR} ${PNG_LIBRARY})

if (PNG_INCLUDE_DIR AND PNG_LIBRARY)
	set(PNG_FOUND TRUE)
	set(PNG_LIBRARIES ${PNG_LIBRARY})
	set(PNG_INCLUDE_DIRS ${PNG_INCLUDE_DIR})
else ()
    message(STATUS "Couldn't find libpng.")
endif ()
