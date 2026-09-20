cmake_minimum_required(VERSION 3.16)
project(main)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
# SDL core
add_subdirectory(SDL EXCLUDE_FROM_ALL)
add_subdirectory(SDL_image EXCLUDE_FROM_ALL)
add_subdirectory(SDL_mixer EXCLUDE_FROM_ALL)
add_executable(Jogo main.cpp src/Game.cpp src/State.cpp src/Sprite.cpp src/Music.cpp src/GameObject.cpp src/Component.cpp src/Rect.cpp src/Vec2.cpp src/SpriteRenderer.cpp src/Animation.cpp src/Zombie.cpp src/Animator.cpp)
target_include_directories(Jogo PRIVATE include)
target_link_libraries(Jogo PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
)

add_custom_command(TARGET Jogo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:Jogo>/resources
)