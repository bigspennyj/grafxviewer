set(EXTRA_LIBS ${EXTRA_LIBS} SDL2 SDL2_image)
file(GLOB SOURCES "*.cpp")

add_library(libgfxvmatrix 3dvector.h matrix.h matrix.cpp)

add_executable(gfxv ${SOURCES})
target_link_libraries(gfxv ${EXTRA_LIBS} libgfxvmatrix)
