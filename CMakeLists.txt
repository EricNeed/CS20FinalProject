cmake_minimum_required(VERSION 3.28)
project(camke_test VERSION 0.1.0 LANGUAGES C CXX)

if(EXISTS "${CMAKE_SOURCE_DIR}/LocalPaths.cmake")
    include("${CMAKE_SOURCE_DIR}/LocalPaths.cmake")
endif()

file(GLOB_RECURSE SERVER_SOURCES "src/*.cpp")

add_executable(sdl3_test src/main.cpp ${SERVER_SOURCES})

find_package(SDL3 REQUIRED PATHS ${SDL3_DIR})
find_package(SDL3_image REQUIRED PATHS ${SDL3_image_DIR})

target_include_directories(sdl3_test PUBLIC ${CMAKE_SOURCE_DIR})

target_link_libraries(sdl3_test PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

#"files.exclude": {
#        ".vscode": true,
#        ".gitattributes": true,
#        "build": true,
#        ".gitignore": true,
#        "LICENSE": true,
#        "LocalPaths.cmake":true,
#        "README.md":true
#    }
#}

# src/server_scripts/client_handler.cpp
# src/server_scripts/tick_server_main.cpp

# src/script_storge/entitie_scripts/sprite.cpp
# src/script_storge/entitie_scripts/player.cpp
 
# src/client_scripts/player_scripts/player_input.cpp
# src/client_scripts/tick_client.cpp
# src/client_scripts/rendering/rendering.cpp