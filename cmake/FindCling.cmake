# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# Findcling
# -------------
#
# Locate cling library
#
# This module defines:
#
# ::
#
# CLING_LIBRARIES, the name of the library to link against
# CLING_INCLUDE_DIRS, where to find the headers
# CLING_FOUND, if false, do not try to link against
# CLING_VERSION_STRING - human-readable string containing the
# version of cling
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# CLINGIMAGE_LIBRARY (same value as CLING_LIBRARIES)
# CLINGIMAGE_INCLUDE_DIR (same value as CLING_INCLUDE_DIRS)
# CLINGIMAGE_FOUND (same value as CLING_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

find_path(CLING_INCLUDE_DIR Interpreter.h
  HINTS
    ENV CLINGDIR
    ${CLING_DIR}
    C:/libraries/Cling/
    /opt/cling/include/cling/Interpreter/
  PATH_SUFFIXES CLING
                # path suffixes to search inside ENV{CLINGDIR}
                include/cling include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(CLING_LIBRARY
  NAMES cling
  HINTS
    ENV CLINGDIR
    ${CLINGDIR}
    /opt/cling/lib/
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
)

if(CLING_INCLUDE_DIR AND EXISTS "${CLING_INCLUDE_DIR}/Interpreter.h")
  file(STRINGS "${CLING_INCLUDE_DIR}/Interpreter.h" CLING_VERSION_MAJOR_LINE REGEX "^#define[ \t]+CLING_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${CLING_INCLUDE_DIR}/Interpreter.h" CLING_VERSION_MINOR_LINE REGEX "^#define[ \t]+CLING_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${CLING_INCLUDE_DIR}/Interpreter.h" CLING_VERSION_PATCH_LINE REGEX "^#define[ \t]+CLING_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+CLING_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" CLING_VERSION_MAJOR "${CLING_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+CLING_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" CLING_VERSION_MINOR "${CLING_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+CLING_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" CLING_VERSION_PATCH "${CLING_VERSION_PATCH_LINE}")
  set(CLING_VERSION_STRING ${CLING_VERSION_MAJOR}.${CLING_VERSION_MINOR}.${CLING_VERSION_PATCH})
  unset(CLING_VERSION_MAJOR_LINE)
  unset(CLING_VERSION_MINOR_LINE)
  unset(CLING_VERSION_PATCH_LINE)
  unset(CLING_VERSION_MAJOR)
  unset(CLING_VERSION_MINOR)
  unset(CLING_VERSION_PATCH)
endif()

set(CLING_LIBRARIES ${CLING_LIBRARY})
set(CLING_INCLUDE_DIRS "${CLING_INCLUDE_DIR}/../../")

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(cling
                                  REQUIRED_VARS CLING_LIBRARIES CLING_INCLUDE_DIRS
                                  VERSION_VAR CLING_VERSION_STRING)

# for backward compatibility
set(CLING_LIBRARY ${CLING_LIBRARIES})
set(CLING_INCLUDE_DIR ${CLING_INCLUDE_DIRS})
set(CLING_FOUND ${CLING_FOUND})

mark_as_advanced(CLING_LIBRARY CLING_INCLUDE_DIR)
