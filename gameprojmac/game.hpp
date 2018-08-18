//
//  game.hpp
//  gameprojmac
//
//  Created by Brian Jones on 8/17/18.
//  Copyright © 2018 Brian Jones. All rights reserved.
//

#ifndef game_h
#define game_h

#include <SDL2/SDL.h>
#include <memory>

struct V2 {
    float x;
    float y;
};
class Game {
public:
    Game();
    
    bool initialize();
    void run_loop();
    void shutdown();
    
private:
    void process_input();
    void update_game();
    void generate_output();
    
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window;
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer;
    V2 paddle_pos;
    V2 ball_pos;
    
    bool is_running;
    
};

#endif /* game_h */
