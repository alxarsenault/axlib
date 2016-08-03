# - Try to find LibXml2
# Once done this will define
#  LIBXML2_FOUND - System has LibXml2
#  LIBXML2_INCLUDE_DIRS - The LibXml2 include directories
#  LIBXML2_LIBRARIES - The libraries needed to use LibXml2
#  LIBXML2_DEFINITIONS - Compiler switches required for using LibXml2

# Try to find Freetype2.
find_path(FREETYPE2_INCLUDE_DIR freetype.h
		/usr/local/include/freetype2
		/usr/include/freetype2
		NO_DEFAULT_PATH)

find_library(FREETYPE2_LIBRARY
		NAMES freetype
		PATHS
		/usr/local/lib
		/usr/lib
		/opt/local/lib
		)

message(${FREETYPE2_INCLUDE_DIR} ${FREETYPE2_LIBRARY})

if (FREETYPE2_INCLUDE_DIR AND FREETYPE2_LIBRARY)
	set(FREETYPE2_FOUND TRUE)
	set(FREETYPE2_LIBRARIES ${FREETYPE2_LIBRARY})
	set(FREETYPE2_INCLUDE_DIRS ${FREETYPE2_INCLUDE_DIR}/.. ${FREETYPE2_INCLUDE_DIR})
else ()
    message(STATUS "Couldn't find freetype.")
endif ()
