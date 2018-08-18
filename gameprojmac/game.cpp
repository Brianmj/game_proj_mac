//
//  game.cpp
//  gameprojmac
//
//  Created by Brian Jones on 8/17/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "game.hpp"

Game::Game() :
window(nullptr, SDL_DestroyWindow),
renderer(nullptr, SDL_DestroyRenderer),
is_running(true)
{
}

bool Game::initialize() {
    int result = SDL_Init(SDL_INIT_VIDEO);
    
    if (0 != result) {
        SDL_Log("Unable to initialize sdl: %s", SDL_GetError());
        
        return false;
    }
    
    window = std::move(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(
                                                                                 SDL_CreateWindow("Game Programming in C++ (Chapter 1)",
                                                                                                  100,
                                                                                                  100,
                                                                                                  1024,
                                                                                                  768,
                                                                                                  0),
                                                                                 SDL_DestroyWindow));
    
    if (!window)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        
        return false;
    }
    
    renderer = std::move(std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>(
                                                                                       SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
                                                                                       SDL_DestroyRenderer
                                                                                       ));
    
    if (!renderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        
        return false;
    }
    
    return true;
}

void Game::run_loop() {
    while (is_running) {
        process_input();
        update_game();
        generate_output();
    }
}

void Game::shutdown() {
    window.reset(nullptr);    // close the window
    SDL_Quit();                // shutdown sdl
}

void Game::process_input() {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: is_running = false; break;
                
        }
        
    }
    
    const Uint8 *scan_keys = SDL_GetKeyboardState(nullptr);
    
    if (scan_keys[SDL_SCANCODE_ESCAPE])
        is_running = false;
}

void Game::update_game() {
    
}

void Game::generate_output() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 170, 255, 255);
    SDL_RenderClear(renderer.get());
    
    
    SDL_RenderPresent(renderer.get());
    
}

