# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# FindRJson
# -------------
#
# Locate RJson library
#
# This module defines:
#
# ::
#
# RJSON_LIBRARIES, the name of the library to link against
# RJSON_INCLUDE_DIRS, where to find the headers
# RJSON_FOUND, if false, do not try to link against
# RJSON_VERSION_STRING - human-readable string containing the
# version of RJson
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# RJSON_LIBRARY (same value as RJSON_LIBRARIES)
# RJSON_INCLUDE_DIR (same value as RJSON_INCLUDE_DIRS)
# RJSON_FOUND (same value as RJSON_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

find_path(RJSON_INCLUDE_DIR rapidjson.h
  HINTS
    ENV RJSONDIR
    ${RJSON_DIR}
    C:/libraries/rapidjson
  PATH_SUFFIXES RJSON
                # path suffixes to search inside ENV{RJSONDIR}
                include/rapidjson include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

if(RJSON_INCLUDE_DIR AND EXISTS "${RJSON_INCLUDE_DIR}/rapidjson.h")
  file(STRINGS "${RJSON_INCLUDE_DIR}/rapidjson.h" RJSON_VERSION_MAJOR_LINE REGEX "^#define[ \t]+RJSON_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${RJSON_INCLUDE_DIR}/rapidjson.h" RJSON_VERSION_MINOR_LINE REGEX "^#define[ \t]+RJSON_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${RJSON_INCLUDE_DIR}/rapidjson.h" RJSON_VERSION_PATCH_LINE REGEX "^#define[ \t]+RJSON_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+RJSON_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" RJSON_VERSION_MAJOR "${RJSON_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+RJSON_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" RJSON_VERSION_MINOR "${RJSON_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+RJSON_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" RJSON_VERSION_PATCH "${RJSON_VERSION_PATCH_LINE}")
  set(RJSON_VERSION_STRING ${RJSON_VERSION_MAJOR}.${RJSON_VERSION_MINOR}.${RJSON_VERSION_PATCH})
  unset(RJSON_VERSION_MAJOR_LINE)
  unset(RJSON_VERSION_MINOR_LINE)
  unset(RJSON_VERSION_PATCH_LINE)
  unset(RJSON_VERSION_MAJOR)
  unset(RJSON_VERSION_MINOR)
  unset(RJSON_VERSION_PATCH)
endif()

set(RJSON_LIBRARIES ${RJSON_LIBRARY})
set(RJSON_INCLUDE_DIRS ${RJSON_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(rapidjson
                                  REQUIRED_VARS RJSON_LIBRARIES RJSON_INCLUDE_DIRS
                                  VERSION_VAR RJSON_VERSION_STRING)

# for backward compatibility
set(RJSON_LIBRARY ${RJSON_LIBRARIES})
set(RJSON_INCLUDE_DIR ${RJSON_INCLUDE_DIRS})
set(RJSON_FOUND ${RJSON_FOUND})
mark_as_advanced(RJSON_LIBRARY RJSON_INCLUDE_DIR)

