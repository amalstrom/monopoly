//
//  board.cpp
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#include "board.h"

void board_init (Board &board) {
    
    Space* go = new Space();
    SpaceInit(go, GO, BLACK, "Go", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[0] = go;
    
    Space* mediterranean = new Space();
    SpaceInit(mediterranean, PROPERTY, BROWN, "Mediterranean Avenue", 60, 2, 10, 30, 90, 160, 250, 50);
    board.board[1] = mediterranean;
    
    Space* cc = new Space();
    SpaceInit(cc, COMMUNITY, BLACK, "Community Chest", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[2] = cc;
    
    Space* baltic = new Space();
    SpaceInit(baltic, PROPERTY, BROWN, "Baltic Avenue", 60, 4, 20, 60, 180, 320, 450, 50);
    board.board[3] = baltic;
    
    Space* itax = new Space();
    SpaceInit(itax, INCOME, BLACK, "Income Tax", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[4] = itax;
    
    Space* reading = new Space();
    SpaceInit(reading, PROPERTY, RAILROAD, "Reading Railroad", 200, 25, 50, 100, 200, -1, -1, -1);
    board.board[5] = reading;
    
    Space* oriental = new Space();
    SpaceInit(oriental, PROPERTY, LIGHTBLUE, "Oriental Avenue", 100, 6, 30, 90, 270, 400, 550, 50);
    board.board[6] = oriental;
    
    Space* chance = new Space();
    SpaceInit(chance, CHANCE, BLACK, "Chance", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[7] = chance;
    
    Space* vermont = new Space();
    SpaceInit(vermont, PROPERTY, LIGHTBLUE, "Vermont Avenue", 100, 6, 30, 90, 270, 400, 550, 50);
    board.board[8] = vermont;
    
    Space* connecticut = new Space();
    SpaceInit(connecticut, PROPERTY, LIGHTBLUE, "Connecticut Avenue", 120, 8, 40, 100, 300, 450, 600, 50);
    board.board[9] = connecticut;
    
    Space* jail = new Space();
    SpaceInit(jail, JAIL, BLACK, "Jail", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[10] = jail;
    
    Space* stcharles = new Space();
    SpaceInit(stcharles, PROPERTY, PINK, "St. Charles Place", 140, 10, 50, 150, 450, 625, 750, 100);
    board.board[11] = stcharles;
    
    Space* electric = new Space();
    SpaceInit(electric, PROPERTY, UTILITY, "Electric Company", 150, -1, -1, -1, -1, -1, -1, -1);
    board.board[12] = electric;
    
    Space* states = new Space();
    SpaceInit(states, PROPERTY, PINK, "States Avenue", 140, 10, 50, 150, 450, 625, 750, 100);
    board.board[13] = states;
    
    Space* virginia = new Space();
    SpaceInit(virginia, PROPERTY, PINK, "Virginia Avenue", 160, 12, 60, 180, 500, 700, 900, 100);
    board.board[14] = virginia;
    
    Space* pennsylvania = new Space();
    SpaceInit(pennsylvania, PROPERTY, RAILROAD, "Pennsylvania Railroad", 200, 25, 50, 100, 200, -1, -1, -1);
    board.board[15] = pennsylvania;
    
    Space* stjames = new Space();
    SpaceInit(stjames, PROPERTY, ORANGE, "St. James Place", 180, 14, 70, 200, 550, 750, 950, 100);
    board.board[16] = stjames;
    
    board.board[17] = cc;
    
    Space* tennessee = new Space();
    SpaceInit(tennessee, PROPERTY, ORANGE, "Tennessee Avenue", 180, 14, 70, 200, 550, 750, 950, 100);
    board.board[18] = tennessee;
    
    Space* newyork = new Space();
    SpaceInit(newyork, PROPERTY, ORANGE, "New York Avenue", 200, 16, 80, 220, 600, 800, 1000, 100);
    board.board[19] = newyork;
    
    Space* freepark = new Space();
    SpaceInit(freepark, FREEPARK, BLACK, "Free Parking", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[20] = freepark;
    
    Space* kentucky = new Space();
    SpaceInit(kentucky, PROPERTY, RED, "Kentucky Avenue", 220, 18, 90, 250, 700, 875, 1050, 150);
    board.board[21] = kentucky;
    
    board.board[22] = chance;
    
    Space* indiana = new Space();
    SpaceInit(indiana, PROPERTY, RED, "Indiana Avenue", 220, 18, 90, 250, 700, 875, 1050, 150);
    board.board[23] = indiana;
    
    Space* illinois = new Space();
    SpaceInit(illinois, PROPERTY, RED, "Illinois Avenue", 240, 20, 100, 300, 750, 925, 1100, 150);
    board.board[24] = illinois;
    
    Space* bo = new Space();
    SpaceInit(bo, PROPERTY, RAILROAD, "B&O Railroad", 200, 25, 50, 100, 200, -1, -1, -1);
    board.board[25] = bo;
    
    Space* atlantic = new Space();
    SpaceInit(atlantic, PROPERTY, YELLOW, "Atlantic Avenue", 260, 22, 110, 330, 800, 975, 1150, 150);
    board.board[26] = atlantic;
    
    Space* ventnor = new Space();
    SpaceInit(ventnor, PROPERTY, YELLOW, "Ventnor Avenue", 260, 22, 110, 330, 800, 975, 1150, 150);
    board.board[27] = ventnor;
    
    Space* water = new Space();
    SpaceInit(water, PROPERTY, UTILITY, "Water Works", 150, -1, -1, -1, -1, -1, -1, -1);
    board.board[28] = water;
    
    Space* marvin = new Space();
    SpaceInit(marvin, PROPERTY, YELLOW, "Marvin Gardens", 280, 24, 120, 360, 850, 1025, 1200, 150);
    board.board[29] = marvin;
    
    Space* gotojail = new Space();
    SpaceInit(gotojail, GOTOJAIL, BLACK, "Go To Jail", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[30] = gotojail;
    
    Space* pacific = new Space();
    SpaceInit(pacific, PROPERTY, GREEN, "Pacific Avenue", 300, 26, 130, 390, 900, 1100, 1275, 200);
    board.board[31] = pacific;
    
    Space* northcarolina = new Space();
    SpaceInit(northcarolina, PROPERTY, GREEN, "North Carolina Avenue", 300, 26, 130, 390, 900, 1100, 1275, 200);
    board.board[32] = northcarolina;
    
    board.board[33] = cc;
    
    Space* pennsylvaniaAve = new Space();
    SpaceInit(pennsylvaniaAve, PROPERTY, GREEN, "Pennsylvania Avenue", 320, 28, 150, 450, 1000, 1200, 1400, 200);
    board.board[34] = pennsylvaniaAve;
    
    Space* shortline = new Space();
    SpaceInit(shortline, PROPERTY, RAILROAD, "Short Line", 200, 25, 50, 100, 200, -1, -1, -1);
    board.board[35] = shortline;
    
    board.board[36] = chance;
    
    Space* park = new Space();
    SpaceInit(park, PROPERTY, DARKBLUE, "Park Place", 350, 35, 175, 500, 1100, 1300, 1500, 200);
    board.board[37] = park;
    
    Space* luxury = new Space();
    SpaceInit(luxury, LUXURY, BLACK, "Luxury Tax", -1, -1, -1, -1, -1, -1, -1, -1);
    board.board[38] = luxury;
    
    Space* boardwalk = new Space();
    SpaceInit(boardwalk, PROPERTY, DARKBLUE, "Boardwalk", 400, 50, 200, 600, 1400, 1700, 2000, 200);
    board.board[39] = boardwalk;
    
}



















































