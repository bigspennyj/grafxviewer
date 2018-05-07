#min version

cmake_minimum_required(VERSION 2.8)

#name the proj

project(gfxv)

#set the directories

set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# copy resources
file(INSTALL ${PROJECT_SOURCE_DIR}/data/
    DESTINATION ${EXECUTABLE_OUTPUT_PATH}/data)

# copy resources
file(INSTALL ${PROJECT_SOURCE_DIR}/assets/
    DESTINATION ${EXECUTABLE_OUTPUT_PATH}/assets)
# add files to build
add_subdirectory(src)
#enable_testing()
#add_subdirectory(test)
