# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# Findraylib
# -------------
#
# Locate raylib library
#
# This module defines:
#
# ::
#
# RAYLIB_LIBRARIES, the name of the library to link against
# RAYLIB_INCLUDE_DIRS, where to find the headers
# RAYLIB_FOUND, if false, do not try to link against
# RAYLIB_VERSION_STRING - human-readable string containing the
# version of raylib
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# RAYLIB_LIBRARY (same value as RAYLIB_LIBRARIES)
# RAYLIB_INCLUDE_DIR (same value as RAYLIB_INCLUDE_DIRS)
# RAYLIB_FOUND (same value as RAYLIB_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

if(NOT RAYLIB_INCLUDE_DIR AND RAYLIB_INCLUDE_DIR)
  set(RAYLIB_INCLUDE_DIR ${RAYLIB_INCLUDE_DIR} CACHE PATH "directory cache entry initialized from old variable name")
endif()
find_path(RAYLIB_INCLUDE_DIR raylib.h
  HINTS
    ENV RAYLIBDIR
    ${RAYLIB_DIR}
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(RAYLIB_LIBRARY
  NAMES raylib
  HINTS
    ENV RAYLIBDIR
    ${RAYLIBDIR}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)

if(RAYLIB_INCLUDE_DIR AND EXISTS "${RAYLIB_INCLUDE_DIR}/raylib.h")
  file(STRINGS "${RAYLIB_INCLUDE_DIR}/raylib.h" RAYLIB_VERSION_MAJOR_LINE REGEX "^#define[ \t]+RAYLIB_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${RAYLIB_INCLUDE_DIR}/raylib.h" RAYLIB_VERSION_MINOR_LINE REGEX "^#define[ \t]+RAYLIB_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${RAYLIB_INCLUDE_DIR}/raylib.h" RAYLIB_VERSION_PATCH_LINE REGEX "^#define[ \t]+RAYLIB_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+RAYLIB_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" RAYLIB_VERSION_MAJOR "${RAYLIB_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+RAYLIB_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" RAYLIB_VERSION_MINOR "${RAYLIB_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+RAYLIB_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" RAYLIB_VERSION_PATCH "${RAYLIB_VERSION_PATCH_LINE}")
  set(RAYLIB_VERSION_STRING ${RAYLIB_VERSION_MAJOR}.${RAYLIB_VERSION_MINOR}.${RAYLIB_VERSION_PATCH})
  unset(RAYLIB_VERSION_MAJOR_LINE)
  unset(RAYLIB_VERSION_MINOR_LINE)
  unset(RAYLIB_VERSION_PATCH_LINE)
  unset(RAYLIB_VERSION_MAJOR)
  unset(RAYLIB_VERSION_MINOR)
  unset(RAYLIB_VERSION_PATCH)
endif()

set(RAYLIB_LIBRARIES ${RAYLIB_LIBRARY})
set(RAYLIB_INCLUDE_DIRS ${RAYLIB_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(raylib
                                  REQUIRED_VARS RAYLIB_LIBRARIES RAYLIB_INCLUDE_DIRS
                                  VERSION_VAR RAYLIB_VERSION_STRING)

# for backward compatibility
set(RAYLIB_LIBRARY ${RAYLIB_LIBRARIES})
set(RAYLIB_INCLUDE_DIR ${RAYLIB_INCLUDE_DIRS})
set(RAYLIB_FOUND ${RAYLIB_FOUND})

mark_as_advanced(RAYLIB_LIBRARY RAYLIB_INCLUDE_DIR)
