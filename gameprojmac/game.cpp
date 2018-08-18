//
//  game.cpp
//  gameprojmac
//
//  Created by Brian Jones on 8/17/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#include "game.hpp"

const int THICKNESS = 15;
const float PADDLE_HEIGHT = 100.0f;

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
    
    paddle_pos = {10.0f, 768 / 2.f};
    ball_pos = {1024.0f / 2.0f, 768.0f / 2.f};
    
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
    
    // passing nullptr to SDL_GetkeyboardState returns an array of scan keys to test
    // if that key was pressed (it's true if it was pressed)
    const Uint8 *scan_keys = SDL_GetKeyboardState(nullptr);
    
    if (scan_keys[SDL_SCANCODE_ESCAPE])
        is_running = false;
}

void Game::update_game() {
    
}

void Game::generate_output() {
    SDL_SetRenderDrawColor(renderer.get(), 0, 170, 255, 255);
    SDL_RenderClear(renderer.get());
    
    SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
    
    SDL_Rect wall {0, 0, 1024, THICKNESS};
    SDL_RenderFillRect(renderer.get(), &wall);  // top wall
    
    wall.y = 768 - THICKNESS;
    SDL_RenderFillRect(renderer.get(), &wall);  // bottom wall
    
    wall.x = 1024 - THICKNESS;
    wall.y = 0;
    wall.w = THICKNESS;
    wall.h = 768;
    SDL_RenderFillRect(renderer.get(), &wall);  // right wall
    
    SDL_Rect ball { ((int)ball_pos.x) - (THICKNESS / 2),
        ((int)ball_pos.y) - (THICKNESS / 2),
        THICKNESS, THICKNESS
    };
    
    SDL_RenderFillRect(renderer.get(), &ball);      // draw the ball
    
    SDL_Rect paddle {(int)paddle_pos.x,
        ((int)paddle_pos.y) - static_cast<int>(PADDLE_HEIGHT / 2),
        THICKNESS,
        static_cast<int>(PADDLE_HEIGHT)
    };
    
    SDL_RenderFillRect(renderer.get(), &paddle);    // draw the paddle
    
    
    
    
    
    SDL_RenderPresent(renderer.get());
    
}

