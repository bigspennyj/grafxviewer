file(GLOB TEST_SOURCE "./*.cpp")

include_directories(${TEST_SOURCE_DIR}/src)

add_executable(gfxv-test ${TEST_SOURCE})
target_link_libraries(libgfxvmatrix)
