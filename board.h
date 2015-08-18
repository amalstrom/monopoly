//
//  board.h
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#ifndef __monopoly__board__
#define __monopoly__board__

#include <stdio.h>
#include <vector>
#include "property.h"
using namespace std;


struct Board {
    Space *board[40];
};

void board_init (Board &board);

#endif /* defined(__monopoly__board__) */
