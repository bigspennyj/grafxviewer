file(GLOB TEST_SOURCE "./*.cpp")

include_directories(${TEST_SOURCE_DIR}/src)

add_executable(gfxv-test ${TEST_SOURCE})
target_link_libraries(gfxv-test libgfxvmatrix)

add_test(NAME gfxv-matrix-test COMMAND gfxv-test "[matrix]")
add_test(NAME gfxv-trans-test COMMAND gfxv-test "[transformation]")
