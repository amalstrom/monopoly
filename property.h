//
//  property.h
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#ifndef __monopoly__property__
#define __monopoly__property__

#include <stdio.h>
#include <string>
#include "player.h"
using namespace std;

enum SpaceType { PROPERTY, GO, INCOME, LUXURY, CHANCE, COMMUNITY, FREEPARK, JAIL, GOTOJAIL };

enum Color { BROWN, LIGHTBLUE, PINK, ORANGE, RED, YELLOW, GREEN, DARKBLUE, RAILROAD, UTILITY, BLACK };

struct Space {
    SpaceType type;
    Color color;
    string name;
    
    int price;
    
    bool monopoly;
    
    int rent;
    int rent1;
    int rent2;
    int rent3;
    int rent4;
    int rentH;
    
    int numHouses;
    int houseCost;
    
    bool mortgaged;
    
    Player *owner;
};

void SpaceInit (Space *space, SpaceType type, Color color, string name, int price, int rent, int rent1, int rent2, int rent3, int rent4, int rentH, int houseCost);

#endif /* defined(__monopoly__property__) */
