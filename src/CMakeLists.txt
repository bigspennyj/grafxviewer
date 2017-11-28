set(EXTRA_LIBS ${EXTRA_LIBS} SDL2 SDL2_image)
file(GLOB SOURCES "*.cpp")

add_executable(gfxv ${SOURCES})
target_link_libraries(gfxv ${EXTRA_LIBS})
