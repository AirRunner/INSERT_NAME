cmake_minimum_required(VERSION 3.5)

file(GLOB CONTROLLER_SOURCES "controller/*.cpp")
file(GLOB DATA_LAYER_SOURCES "data-layer/*.cpp")
file(GLOB RENDERING_SOURCES "rendering/*.cpp")
file(GLOB SCENES_SOURCES "scenes/*.cpp")

set(SOURCES ${CONTROLLER_SOURCES} ${DATA_LAYER_SOURCES} ${RENDERING_SOURCES} ${SCENES_SOURCES})

file(GLOB_RECURSE HEADERS "*.hpp")

set(OUTPUT "project")

set(OPT "-Wall -Werror -std=c++14 -g")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(SDL2_BUILDING_LIBRARY)

project(project)

#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_gfx REQUIRED)
find_package(EnTT REQUIRED)
find_package(Raylib REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPT}")

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
set_property(TARGET ${OUTPUT} PROPERTY CXX_STANDARD 14)

target_include_directories(${OUTPUT} PRIVATE ${INCLUDE_DIRS} #[[${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SDL2_GFX_INCLUDE_DIRS}]] ${ENTT_INCLUDE_DIRS} ${RAYLIB_INCLUDE_DIRS})

target_link_libraries(${OUTPUT} #[[${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SDL2_GFX_LIBRARIES}]] ${ENTT_LIBRARIES} ${RAYLIB_LIBRARIES})

