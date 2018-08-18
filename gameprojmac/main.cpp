#include "game.hpp"

int main(int argc, char *argv[]) {
    
    Game game;
    
    bool success = game.initialize();
    
    if (success) {
        game.run_loop();
    }
    
    game.shutdown();
    return 0;
}
