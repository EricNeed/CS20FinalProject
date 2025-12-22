#include<iostream>
#include"client/tick_client.h"
#include"server/tick_server_main.h"
#include<SDL3/SDL.h>
#include<chrono>
#include<thread>

bool game_running = true;
auto frame_time = std::chrono::microseconds(16666);//how much microsecond is one game loop

void processSDLEvents(SDL_Event& sdl_event){
    //process all current SDL events
    while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type){
            //check if player has closed the program
            case SDL_EVENT_QUIT: game_running = false;
        default: break;
        }
    }
}

int main(){
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "The game is starting up...");

    TickClient tick_client;
    TickServer tick_server;
    SDL_Event sdl_event;

    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time;

    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Game loop running");
    while(game_running){
        begin_time = std::chrono::high_resolution_clock::now();

        tick_client.tick_client();
        tick_server.ticking();
        processSDLEvents(sdl_event);

        std::this_thread::sleep_for(frame_time - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin_time));
    }

    return 0;
}