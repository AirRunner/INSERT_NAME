# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

#.rst:
# Findentt
# -------------
#
# Locate entt library
#
# This module defines:
#
# ::
#
# ENTT_LIBRARIES, the name of the library to link against
# ENTT_INCLUDE_DIRS, where to find the headers
# ENTT_FOUND, if false, do not try to link against
# ENTT_VERSION_STRING - human-readable string containing the
# version of entt
#
#
#
# For backward compatibility the following variables are also set:
#
# ::
#
# ENTTIMAGE_LIBRARY (same value as ENTT_LIBRARIES)
# ENTTIMAGE_INCLUDE_DIR (same value as ENTT_INCLUDE_DIRS)
# ENTTIMAGE_FOUND (same value as ENTT_FOUND)
#
#
#
# $SDLDIR is an environment variable that would correspond to the
# ./configure --prefix=$SDLDIR used in building SDL.
#
# Created by Eric Wing. This was influenced by the FindSDL.cmake
# module, but with modifications to recognize OS X frameworks and
# additional Unix paths (FreeBSD, etc).

find_path(ENTT_INCLUDE_DIR entt.hpp
  HINTS
    ENV ENTTDIR
    ${ENTT_DIR}
  PATH_SUFFIXES ENTT
                # path suffixes to search inside ENV{ENTTDIR}
                include/entt include
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

if(ENTT_INCLUDE_DIR AND EXISTS "${ENTT_INCLUDE_DIR}/entt.hpp")
  file(STRINGS "${ENTT_INCLUDE_DIR}/entt.hpp" ENTT_VERSION_MAJOR_LINE REGEX "^#define[ \t]+ENTT_MAJOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${ENTT_INCLUDE_DIR}/entt.hpp" ENTT_VERSION_MINOR_LINE REGEX "^#define[ \t]+ENTT_MINOR_VERSION[ \t]+[0-9]+$")
  file(STRINGS "${ENTT_INCLUDE_DIR}/entt.hpp" ENTT_VERSION_PATCH_LINE REGEX "^#define[ \t]+ENTT_PATCHLEVEL[ \t]+[0-9]+$")
  string(REGEX REPLACE "^#define[ \t]+ENTT_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" ENTT_VERSION_MAJOR "${ENTT_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+ENTT_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" ENTT_VERSION_MINOR "${ENTT_VERSION_MINOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+ENTT_PATCHLEVEL[ \t]+([0-9]+)$" "\\1" ENTT_VERSION_PATCH "${ENTT_VERSION_PATCH_LINE}")
  set(ENTT_VERSION_STRING ${ENTT_VERSION_MAJOR}.${ENTT_VERSION_MINOR}.${ENTT_VERSION_PATCH})
  unset(ENTT_VERSION_MAJOR_LINE)
  unset(ENTT_VERSION_MINOR_LINE)
  unset(ENTT_VERSION_PATCH_LINE)
  unset(ENTT_VERSION_MAJOR)
  unset(ENTT_VERSION_MINOR)
  unset(ENTT_VERSION_PATCH)
endif()

set(ENTT_LIBRARIES ${ENTT_LIBRARY})
set(ENTT_INCLUDE_DIRS ${ENTT_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(entt
                                  REQUIRED_VARS ENTT_LIBRARIES ENTT_INCLUDE_DIRS
                                  VERSION_VAR ENTT_VERSION_STRING)

# for backward compatibility
set(ENTT_LIBRARY ${ENTT_LIBRARIES})
set(ENTT_INCLUDE_DIR ${ENTT_INCLUDE_DIRS})
set(ENTT_FOUND ${ENTT_FOUND})

mark_as_advanced(ENTT_LIBRARY ENTT_INCLUDE_DIR)
