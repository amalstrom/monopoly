//
//  game.h
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#ifndef __monopoly__game__
#define __monopoly__game__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "player.h"
#include "property.h"
using namespace std;

struct Game {
    Board board;
    vector<Player *> players;
    
    vector<string> community_chest;
    vector<string> chance;
    vector<string> community_discard;
    vector<string> chance_discard;
    
    vector<int> jail_count;
};

void game_init ( Game *game );

void chance_init ( Game *game );

void community_init ( Game *game );

bool valid_num_players ( int num );

int roll();

int determine_order ( Game *game );

bool game_over ( Game *game );

void take_turn ( Game *game, int &current_index );

void list_positions ( Game *game );

void print_turn_options1 ();

void print_turn_options2 ();

pair<int, int> roll_dice ( Token current_token );

void end_turn ( Game *game, int &current_index );

void print_purchase_opts ();

void buy_property ( Game *game, int &current_index );

void pass_property ( Game *game, int &current_index );

void pay_rent ( Game *game, int &current_index, int dice_roll );

int get_rent( Game *game, int &current_index, int dice_roll );

void update_monopoly ( Game *game, Space* recent_purchase );

string draw_chance ( Game *game );

void execute_chance ( Game *game, string chance_card, int current_index );

void offer_property ( Game *game, int current_index );

void pay_twice_rent ( Game *game, int current_index );

void move_token ( Game *game, int current_index, int current_location, int new_location, int dice_roll );

void pass_go ( Game *game, int current_index );

void list_accounts ( Game *game );

void list_properties ( Game *game );

bool passes_go ( int current_location, int new_location );

string draw_community ( Game *game );

void execute_community ( Game *game, string cc_card, int current_index );

void pay_for_buildings ( Game *game, int current_index, int housePrice, int hotelPrice );

void manage_properties ( Game *game, int current_index );

void print_manage_opts();

void mortgage ( Game *game, int current_index );

void mortgage_property ( Game *game, int mortgage_index );

void unmortgage_property ( Game *game, int unmortgage_index );

void build_property( Game *game, int build_index );

void trade ( Game *game, int current_index );

void trade_companions ( Game *game, int current_index );

void initialize_trade ( Game *game, int current_index, int trade_index );

void compose_trade ( Game *game, int current_index, int trade_index );

void make_offer ( Game *game, int current_index, int trade_index, vector<Space *> take_prop, vector<Space *> offer_prop, int take_money, int offer_money, bool cc_take, bool cc_offer, bool chance_take, bool chance_offer );

void execute_trade ( Game *game, int current_index, int trade_index, vector<Space *> take_prop, vector<Space *> offer_prop, int take_money, int offer_money, bool cc_take, bool cc_offer, bool chance_take, bool chance_offer );

bool check_cash_flow ( int cost, int cash );

void broke_player ( Game *game, int current_index );

void print_broke_opts();

void get_out_of_jail ( Game *game, int current_index, string method );

void in_jail ( Game *game, int current_index );

#endif /* defined(__monopoly__game__) */




















































