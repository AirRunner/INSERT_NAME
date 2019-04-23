cmake_minimum_required(VERSION 3.5)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

file(GLOB CONTROLLER_SOURCES "controller/*.cpp")
file(GLOB DATA_LAYER_SOURCES "data-layer/*.cpp")
file(GLOB RENDERING_SOURCES "rendering/*.cpp")
file(GLOB SYSTEMS_SOURCES "systems/*.cpp")
file(GLOB_RECURSE SCENES_SOURCES "scenes/*.cpp")

set(SOURCES ${CONTROLLER_SOURCES} ${DATA_LAYER_SOURCES} ${RENDERING_SOURCES} ${SYSTEMS_SOURCES} ${SCENES_SOURCES})

file(GLOB_RECURSE HEADERS "*.hpp")

set(OUTPUT "project")

set(OPT "-Wall -Werror -std=c++17 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SDL2_BUILDING_LIBRARY)

project(project)

find_package(EnTT REQUIRED)
find_package(Raylib REQUIRED)
find_package(RJson REQUIRED)

IF(APPLE)
  find_library(COCOA_LIBRARY Cocoa)
  find_library(OPENGL_LIBRARY OpenGL)
  find_library(IOKIT_LIBRARY IOKit)
  find_library(COREVIDEO_LIBRARY CoreVideo)
ENDIF()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()


set(INCLUDE_DIRS "")
foreach (headerFile ${HEADERS})
	get_filename_component(dir ${headerFile} PATH)
	list (APPEND INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)


add_executable(${OUTPUT} ${SOURCES} ${HEADERS})
set_property(TARGET ${OUTPUT} PROPERTY CXX_STANDARD 17)

target_include_directories(${OUTPUT} PRIVATE ${INCLUDE_DIRS} ${ENTT_INCLUDE_DIRS} ${RAYLIB_INCLUDE_DIRS} ${RJSON_INCLUDE_DIRS})

target_link_libraries(${OUTPUT} ${RAYLIB_LIBRARIES})

IF(APPLE)
  target_link_libraries(${OUTPUT} ${COCOA_LIBRARY} ${OPENGL_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY})
ENDIF()
