#include "Direction.h"
#include <iostream>
#include "Game.h"

int main(void){
    Game *game = new Game();
    game->start();
    delete game;
    return 0 ;
}
