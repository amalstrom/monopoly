//
//  main.cpp
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "player.h"
#include "property.h"
using namespace std;

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    Game *game = new Game();
    game_init(game);
    
    int current_index;
    current_index = determine_order(game);
    
    cout << print_token(game->players[current_index]->token) << " is first!\n" << endl;
    
    while ( !game_over(game) ) {
        take_turn(game, current_index);
    }
}




































