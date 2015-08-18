//
//  player.cpp
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#include "player.h"

void player_init ( Player* player, Token token ) {
    player->token = token;
    player->free = true;
    player->cashOnHand = 1500;
    player->location_index = 0;
    player->chance_jail = false;
    player->cc_jail = false;
    
    fill_n(player->ownership, 40, false);
}

string print_token ( Token token ) {
    if (token == WHEELBARROW) {
        return "Wheelbarrow";
    } else if (token == BATTLESHIP) {
        return "Battleship";
    } else if (token == RACECAR) {
        return "Racecar";
    } else if (token == THIMBLE) {
        return "Thimble";
    } else if (token == SHOE) {
        return "Shoe";
    } else if (token == DOG) {
        return "Scottie Dog";
    } else if (token == TOPHAT) {
        return "Top Hat";
    } else if (token == CAT) {
        return "Cat";
    }
    
    return "Invalid";
};

Token string_token ( string st ) {
    if (st == "Wheelbarrow") {
        return WHEELBARROW;
    } else if (st == "Battleship") {
        return BATTLESHIP;
    } else if (st == "Racecar") {
        return RACECAR;
    } else if (st == "Thimble") {
        return THIMBLE;
    } else if (st == "Shoe") {
        return SHOE;
    } else if (st == "Scottie Dog") {
        return DOG;
    } else if (st == "Top Hat") {
        return TOPHAT;
    } else if (st == "Cat") {
        return CAT;
    }
    
    return INVALID;
};
































