file(GLOB_RECURSE game_SOURCES src/*.cpp)
file(GLOB_RECURSE glew_SOURCES src/glew/*.c)
file(GLOB_RECURSE game_HEADERS src/*.h)

include_directories(src/)

add_executable(Game ${game_SOURCES} ${game_HEADERS} ${glew_SOURCES})

target_link_libraries(Game MLD45Glfw ${GL_LIBRARIES} ${GLFW_LIBRARIES})
