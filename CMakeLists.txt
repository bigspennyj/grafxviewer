#min version

cmake_minimum_required(VERSION 2.8)

#name the proj

project(gfxv)

#set the directories

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

file(GLOB SOURCES "src/*.cpp")

include_directories("${PROJECT_SOURCE_DIR}/src")

set(EXTRA_LIBS ${EXTRA_LIBS} SDL2 SDL2_image)

add_executable(gfxv ${SOURCES})
target_link_libraries(gfxv ${EXTRA_LIBS})
