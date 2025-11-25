cmake_minimum_required(VERSION 3.10.0)
project(camke_test VERSION 0.1.0 LANGUAGES C CXX)

add_executable(sdl3_test
 src/main.cpp
 src/server_scripts/client_handler.cpp
 src/server_scripts/entitie_scripts/sprite.cpp
 src/server_scripts/tick_server_main.cpp
)

set(SDL3_DIR "M:/code/libraries/SDL3-3.2.26/x86_64-w64-mingw32/lib/cmake/SDL3")
find_package(SDL3 REQUIRED)

set(SDL3_image_DIR "M:/code/libraries/SDL3_image-3.2.4/x86_64-w64-mingw32/lib/cmake/SDL3_image")
find_package(SDL3_image REQUIRED)

target_include_directories(sdl3_test PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(sdl3_test PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)