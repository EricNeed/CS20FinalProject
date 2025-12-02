cmake_minimum_required(VERSION 3.28)
project(camke_test VERSION 0.1.0 LANGUAGES C CXX)

if(EXISTS "${CMAKE_SOURCE_DIR}/LocalPaths.cmake")
    include("${CMAKE_SOURCE_DIR}/LocalPaths.cmake")
endif()


add_executable(sdl3_test
 src/main.cpp
 src/server_scripts/client_handler.cpp
 src/server_scripts/tick_server_main.cpp
 src/script_storge/entitie_scripts/sprite.cpp
 src/script_storge/entitie_scripts/player.cpp
)

find_package(SDL3 REQUIRED PATHS ${SDL3_DIR})
find_package(SDL3_image REQUIRED PATHS ${SDL3_image_DIR})

target_include_directories(sdl3_test PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(sdl3_test PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)