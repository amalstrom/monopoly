//
//  player.h
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#ifndef __monopoly__player__
#define __monopoly__player__

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

enum Token { WHEELBARROW, BATTLESHIP, RACECAR, THIMBLE, SHOE, DOG, TOPHAT, CAT, INVALID };

struct Player {
    Token token;
    
    int cashOnHand;
    
    bool free;
    
    int location_index;
    
    bool ownership[40];
    
    bool cc_jail;
    bool chance_jail;
};

void player_init ( Player* player, Token token );

string print_token ( Token token );

Token string_token ( string st );

#endif /* defined(__monopoly__player__) */
