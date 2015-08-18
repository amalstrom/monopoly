//
//  property.cpp
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#include "property.h"
using namespace std;

void SpaceInit (Space *space, SpaceType type, Color color, string name, int price, int rent, int rent1, int rent2, int rent3, int rent4, int rentH, int houseCost) {
    space->type = type;
    space->color = color;
    space->name = name;
    space->price = price;
    space->rent = rent;
    space->rent1 = rent1;
    space->rent2 = rent2;
    space->rent3 = rent3;
    space->rent4 = rent4;
    space->rentH = rentH;
    space->houseCost = houseCost;
    
    space->monopoly = false;
    space->numHouses = 0;
    space->owner = nullptr;
    space->mortgaged = false;
}
