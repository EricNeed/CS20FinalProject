#include<iostream>
#include"client/tick_client.h"
#include"server/tick_server_main.h"
#include<SDL3/SDL.h>
#include<chrono>
#include<thread>

bool game_running = true;
auto frame_time = std::chrono::microseconds(16666);//how much microsecond is one game loop

TickClient tick_client;
TickServer tick_server;
SDL_Event sdl_event;

void processSDLEvents(SDL_Event& sdl_event){
    //process all current SDL events
    while(SDL_PollEvent(&sdl_event)) {
        switch (sdl_event.type){
            //check if player has closed the program
            case SDL_EVENT_WINDOW_ENTER_FULLSCREEN: tick_client.toggleFullScreen(true);
            case SDL_EVENT_WINDOW_LEAVE_FULLSCREEN: tick_client.toggleFullScreen(false);
            case SDL_EVENT_QUIT: game_running = false;
        default: break;
        }
    }
}

int main(){  
    //sdl init config
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO);
    SDL_SetLogPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_DEBUG);
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Main]: The game is starting up...");

    std::chrono::time_point<std::chrono::high_resolution_clock> begin_time;

    //main game loop
    SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "[Main]: Game loop running");
    while(game_running){
        begin_time = std::chrono::high_resolution_clock::now();

        tick_client.tick_client();
        tick_server.ticking();
        processSDLEvents(sdl_event);

        
        //sleep to maintain frame rate
        std::chrono::duration sleep_time = frame_time - std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - begin_time);
        if (sleep_time.count() < 0){continue;}//if processing time exceeds frame time, skip sleep
        std::this_thread::sleep_for(sleep_time);
    }

    return 0;
}