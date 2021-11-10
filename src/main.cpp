#include <iostream>
#include "game.h"

int main () {
    std::cout << "Welcome the Trading Game. \nGood Luck!" << std::endl;

    Game game;
    game.Run();
    std::cout << "Game Over!" << "\n";
    
    return 0;
}
