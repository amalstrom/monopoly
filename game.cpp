//
//  game.cpp
//  monopoly
//
//  Created by Alec Malstrom on 7/21/15.
//  Copyright (c) 2015 Alec Malstrom. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "game.h"
using namespace std;

void game_init ( Game *game ) {
    Board gameboard;
    board_init(gameboard);
    
    chance_init(game);
    community_init(game);
    
    vector<Player *> players;
    
    /* GET NUMBER OF PLAYERS */
    string in_numPlayers;
    
    cout << "How many players will be playing?" << endl;
    getline(cin, in_numPlayers);
    
    int numPlayers;
    numPlayers = stoi(in_numPlayers);
    
    while (!valid_num_players(numPlayers)) {
        if (numPlayers < 1) {
            cout << "Then who's typing?\nThere must be at least 2 players.  Try again:" << endl;
        } else if (numPlayers < 2) {
            cout << "Sorry, you can only play if you have friends.\nThere must be at least 2 players.  Try again:" << endl;
        } else if (numPlayers > 8) {
            cout << "Whoa there!\nOnly 8 people can play at a time.  Try again:" << endl;
        }
        getline(cin, in_numPlayers);
    }
    
    
    /* SELECT PLAYER TOKENS */
    vector<Token> pieces = { WHEELBARROW, BATTLESHIP, RACECAR, THIMBLE, SHOE, DOG, TOPHAT, CAT };
    
    for (int i = 0; i < numPlayers; i++) {
        game->jail_count.push_back(0);
        string choice;
        
        //lists choices and takes input
        cout << "Okay Player " << i+1 << ", you can play as ";
        if (pieces.size() > 1) {
            for (int i = 0; i < pieces.size()-1; i++) {
                cout << print_token(pieces[i]) << ", ";
            }
            cout << "or " << print_token(pieces[pieces.size()-1]) << ".  Please enter your choice:" << endl;
            getline(cin, choice);
        } else {
            cout << print_token(pieces[0]) << ".  Please enter your choice:" << endl;
            getline(cin, choice);
        }
        
        //ensures valid choice
        bool valid_choice = false;
        for (int j = 0; j < pieces.size(); j++) {
            if (string_token(choice) == pieces[j]) {
                valid_choice = true;
                break;
            }
        }
        
        //corrects if invalid
        while (!valid_choice) {
            cout << "Invalid Choice.  Please enter your choice again:" << endl;
            getline(cin, choice);
                
            for (int j = 0; j < pieces.size(); j++) {
                if (string_token(choice) == pieces[j]) {
                    valid_choice = true;
                    break;
                }
            }
        }
        
        //initializes player and adds to vector
        Player *player = new Player();
        player_init(player, string_token(choice));
            
        Token choiceToken = string_token(choice);
            
        bool notFound = true;
        for (int i = 0; i < pieces.size(); i++) {
            if (pieces[i] == choiceToken) {
                notFound = false;
            }
            if (notFound == true) {
                continue;
            }
            
            pieces[i] = pieces[i+1];
        }
        
        pieces.pop_back();
        players.push_back(player);
    }
    game->board = gameboard;
    game->players = players;
}

void chance_init ( Game *game ) {
    game->chance.push_back("Make general repairs on all your property.  For each house pay $25, for each hotel pay $100.");
    game->chance.push_back("Go to Jail.  Go directly to Jail, do not pass Go, do not collect $200.");
    game->chance.push_back("Speeding fine $15.");
    game->chance.push_back("Advance to the nearest railroad.  If unowned, you may buy it from the bank.  If owned, pay owner twice the rental to which they are otherwise entitled.");
    game->chance.push_back("Advance to the nearest railroad.  If unowned, you may buy it from the bank.  If owned, pay owner twice the rental to which they are otherwise entitled.");
    game->chance.push_back("Advance to Boardwalk.");
    game->chance.push_back("Take a trip to Reading Railroad.  If you pass Go, collect $200.");
    game->chance.push_back("You have been elected chairman of the board.  Pay each player $50.");
    game->chance.push_back("Get out of Jail free.  This card may be kept until needed or traded.");
    game->chance.push_back("Advance to St. Charles Place.  If you pass go, collect $200.");
    game->chance.push_back("Advance to the nearest utility.  If unowned, you may buy it from the bank.  If owned, throw dice and pay owner ten times the amount thrown.");
    game->chance.push_back("Go back three spaces.");
    game->chance.push_back("Advance to Go. (Collect $200)");
    game->chance.push_back("Advance to Illinois Avenue.  If you pass Go, collect $200.");
    game->chance.push_back("Bank pays you dividend of $50.");
    game->chance.push_back("Your building loan matures.  Collect $150.");
}

void community_init ( Game *game ) {
    game->community_chest.push_back("From sale of stock you get $50.");
    game->community_chest.push_back("School fees.  Pay $50.");
    game->community_chest.push_back("You have won second prize in a beauty contest.  Collect $10.");
    game->community_chest.push_back("You are assessed for street repairs: pay $40 per house and $115 per hotel you own.");
    game->community_chest.push_back("Hospital fees.  Pay $100.");
    game->community_chest.push_back("Go to Jail.  Go directly to Jail, do not pass Go, do not collect $200.");
    game->community_chest.push_back("You inherity $100.");
    game->community_chest.push_back("Receive $25 consultancy fee.");
    game->community_chest.push_back("Doctor's fees.  Pay $50.");
    game->community_chest.push_back("It is your birthday.  Collect $10 from every player.");
    game->community_chest.push_back("Get out of Jail free.  This card may be kept until needed or traded.");
    game->community_chest.push_back("Holiday fund matures.  Receive $100.");
    game->community_chest.push_back("Advance to Go. (Collect $200)");
    game->community_chest.push_back("Bank error in your favor.  Collect $200.");
    game->community_chest.push_back("Life insurance matures.  Collect $100.");
    game->community_chest.push_back("Income tax refund.  Collect $20.");
}

bool valid_num_players (int num) {
    if (num < 2) {
        return false;
    } else if (num >8) {
        return false;
    } else {
        return true;
    }
}

int roll () {
    int dice = (rand() % 6) + 1;
    return dice;
}

int determine_order (Game *game) {
    cout << "\nTo decide who goes first, each person will roll one of the die." << endl;
    
    vector<int> first_rolls;
    
    bool tie = true;
    int winner_index = 0;
    int winner_roll = 0;
    
    while (tie) {
        /* EVERYONE ROLLS */
        for (int i = 0; i < game->players.size(); i++) {
            cout << print_token(game->players[i]->token) << ", type 'Roll' to roll the die." << endl;
            string trash;
            getline(cin, trash);
            if (trash == "Roll") {
                int result = roll();
                cout << print_token(game->players[i]->token) << " got " << result << "!" << endl;
                
                first_rolls.push_back(result);
            } else {
                cout << "You're an idiot.  We're counting that as 1." << endl;
                
                first_rolls.push_back(1);
            }
        }
        
        /* DETERMINES IF WINNER IS TIED */
        tie = false;
        winner_index = -1;
        winner_roll = 0;
        
        for (int i = 0; i < first_rolls.size(); i++) {
            if (first_rolls[i] > winner_roll) {
                winner_index = i;
                winner_roll = first_rolls[i];
                tie = false;
            } else if (first_rolls[i] == winner_roll) {
                tie = true;
            }
        }
        
        /* INSTRUCTIONS IF TIED */
        if (tie) {
            cout << "For a tie, everyone has to roll again."  << endl;
            while (first_rolls.size()) {
                first_rolls.pop_back();
            }
        }
    }
    
    /* RETURNS THE WINNER'S INDEX */
    return winner_index;
}

bool game_over ( Game *game ) {
    if (game->players.size() == 1) {
        return true;
    }
    
    return false;
};

void list_positions ( Game *game ) {
    cout << "LOCATIONS: " << endl;
    for (int i = 0; i < game->players.size(); i++) {
        cout << print_token(game->players[i]->token) << " is on " << game->board.board[game->players[i]->location_index]->name << endl;
    }
    
    cout << endl;
}

void take_turn ( Game* game, int &current_index ) {
    bool active = true;
    bool doubs = true;
    
    list_positions(game);
    
    cout << print_token(game->players[current_index]->token) << " is starting its turn." << endl;
    
    while (active) {
        if ((!game->players[current_index]->free) && (doubs)) {
            in_jail(game, current_index);
            
            bool invalid_input = true;
            
            while (invalid_input) {
                string input;
                getline(cin, input);
                
                if ((input == "Roll for Doubles") && (game->jail_count[current_index] < 3)) {
                    doubs = false;
                    invalid_input = false;
                    pair<int, int> dice_roll = roll_dice(game->players[current_index]->token);
                    
                    if (dice_roll.first == dice_roll.second) {
                        cout << "Doubles!" << endl;
                        get_out_of_jail(game, current_index, "Doubles");
                        move_token(game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index+dice_roll.first+dice_roll.second, dice_roll.first+dice_roll.second);
                    }
                    
                    game->jail_count[current_index]++;
                    
                    if ((game->jail_count[current_index] == 3) && (!game->players[current_index]->free)) {
                        get_out_of_jail(game, current_index, "Cash");
                        move_token(game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index+dice_roll.first+dice_roll.second, dice_roll.first+dice_roll.second);
                    }
                    
                    continue;
                } else if ((input == "Use 'Get Out of Jail Free' Card") && (game->players[current_index]->cc_jail || game->players[current_index]->chance_jail)) {
                    doubs = false;
                    invalid_input = false;
                    get_out_of_jail(game, current_index, "Card");
                    
                    pair<int, int> dice_roll = roll_dice(game->players[current_index]->token);
                    
                    if (dice_roll.first == dice_roll.second) {
                        doubs = true;
                        cout << "Doubles!" << endl;
                    }
                    
                    move_token(game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index+dice_roll.first+dice_roll.second, dice_roll.first+dice_roll.second);
                    
                    continue;
                } else if (input == "Post $50 Bail") {
                    doubs = false;
                    invalid_input = false;
                    get_out_of_jail(game, current_index, "Cash");
                    
                    pair<int, int> dice_roll = roll_dice(game->players[current_index]->token);
                    
                    if (dice_roll.first == dice_roll.second) {
                        doubs = true;
                        cout << "Doubles!" << endl;
                    }
                    
                    move_token(game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index+dice_roll.first+dice_roll.second, dice_roll.first+dice_roll.second);
                    
                    continue;
                } else if (input == "Trade") {
                    invalid_input = false;
                    trade(game, current_index);
                    continue;
                } else if (input == "Manage Properties") {
                    invalid_input = false;
                    manage_properties(game, current_index);
                    continue;
                } else if (input == "List Accounts") {
                    invalid_input = false;
                    list_accounts(game);
                    continue;
                } else if (input == "List Properties") {
                    invalid_input = false;
                    list_properties(game);
                    continue;
                } else {
                    cout << "Invalid Input.  Please try again:" << endl;
                }
            }
        }
        
        
        
        if (doubs) {
            print_turn_options1();
        } else {
            print_turn_options2();
        }
        
        string input;
        getline(cin, input);
        
        if ((input == "Roll") && (doubs)) {
            doubs = false;
            pair<int, int> dice = roll_dice( game->players[current_index]->token );
            
            if (dice.first == dice.second) {
                doubs = true;
                cout << "Doubles!" << endl;
            }
            
            move_token (game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index+dice.first+dice.second, dice.first+dice.second);
        } else if (input == "Trade") {
            trade (game, current_index);
        } else if (input == "Manage Properties") {
            manage_properties (game, current_index);
        } else if (input == "List Accounts") {
            list_accounts (game);
        } else if (input == "List Properties") {
            list_properties (game);
        } else if ((input == "End Turn") && (!doubs)) {
            end_turn(game, current_index);
            active = false;
        } else {
            cout << "Invalid input.  Try again:" << endl;
        }
        
    }
}

void print_turn_options1 () {
    cout << "Options: " << endl;
    cout << "\tRoll" << endl;
    cout << "\tTrade" << endl;
    cout << "\tManage Properties" << endl;
    cout << "\tList Accounts" << endl;
    cout << "\tList Properties" << endl;
    cout << "Please select an option:" << endl;
}

void print_turn_options2 () {
    cout << "Options: " << endl;
    cout << "\tTrade" << endl;
    cout << "\tManage Properties" << endl;
    cout << "\tList Accounts" << endl;
    cout << "\tList Properties" << endl;
    cout << "\tEnd turn" << endl;
    cout << "Please select an option:" << endl;
}

pair<int, int> roll_dice ( Token current_token ) {
    int die1 = roll();
    int die2 = roll();
    
    cout << print_token(current_token) << " rolled a " << die1 << " and a " << die2 << endl;
    
    return make_pair(die1, die2);
}

void end_turn ( Game* game, int &current_index ) {
    cout << print_token(game->players[current_index]->token) << " has finished its turn.\n" << endl;
    current_index++;
    
    if (current_index == game->players.size()) {
        current_index = 0;
    }
}

void print_purchase_opts () {
    cout << "The property is for sale!  Would you like to buy it?  Enter 'Buy' or 'Pass'" << endl;
}

void buy_property ( Game *game, int &current_index ) {
    if (check_cash_flow(game->board.board[game->players[current_index]->location_index]->price, game->players[current_index]->cashOnHand)) {
        game->board.board[game->players[current_index]->location_index]->owner = game->players[current_index];
        game->players[current_index]->ownership[game->players[current_index]->location_index] = true;
        
        game->players[current_index]->cashOnHand -= game->board.board[game->players[current_index]->location_index]->price;
        
        cout << print_token(game->players[current_index]->token) << " has bought " << game->board.board[game->players[current_index]->location_index]->name << " from the bank for $" << game->board.board[game->players[current_index]->location_index]->price << "." << endl;
        
        update_monopoly(game, game->board.board[game->players[current_index]->location_index]);
    } else {
        broke_player(game, current_index);
    }
}

void pass_property ( Game *game, int &current_index ) {
    cout << "Property was passed on.  Nothing happens!" << endl;
}

void pay_rent ( Game *game, int &current_index, int dice_roll ) {
    if (check_cash_flow(get_rent(game, current_index, dice_roll), game->players[current_index]->cashOnHand)) {
        game->board.board[game->players[current_index]->location_index]->owner->cashOnHand += get_rent(game, current_index, dice_roll);
        game->players[current_index]->cashOnHand -= get_rent(game, current_index, dice_roll);
        
        cout << print_token(game->players[current_index]->token) << " paid " << print_token(game->board.board[game->players[current_index]->location_index]->owner->token) << " $" << get_rent(game, current_index, dice_roll) << " in rent." << endl;
    } else {
        broke_player(game, current_index);
    }
}

int get_rent( Game *game, int &current_index, int dice_roll ) {
    Space *temp = game->board.board[game->players[current_index]->location_index];
    if (temp->color == RAILROAD) {
        if (temp->numHouses == 1) {
            return 25;
        } else if (temp->numHouses == 2) {
            return 50;
        } else if (temp->numHouses == 3) {
            return 100;
        } else if (temp->numHouses == 4) {
            return 200;
        }
    } else if (temp->color == UTILITY) {
        if (temp->numHouses == 1) {
            return 4*dice_roll;
        } else if (temp->numHouses == 2) {
            return 10*dice_roll;
        }
    }
    
    
    
    if (temp->monopoly) {
        if (temp->numHouses == 0) {
            return 2*temp->rent;
        } else if (temp->numHouses == 1) {
            return temp->rent1;
        } else if (temp->numHouses == 2) {
            return temp->rent2;
        } else if (temp->numHouses == 3) {
            return temp->rent3;
        } else if (temp->numHouses == 4) {
            return temp->rent4;
        } else if (temp->numHouses == 5) {
            return temp->rentH;
        }
    } else {
        return temp->rent;
    }
    
    return 0;
}

void update_monopoly ( Game *game, Space* recent_purchase ) {
    if (recent_purchase->color == BROWN) {
        if (game->board.board[1]->owner == game->board.board[3]->owner) {
            game->board.board[1]->monopoly = game->board.board[3]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == LIGHTBLUE) {
        if ((game->board.board[6]->owner == game->board.board[8]->owner) && (game->board.board[8]->owner == game->board.board[9]->owner)) {
            game->board.board[6]->monopoly = game->board.board[8]->monopoly = game->board.board[9]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == PINK) {
        if ((game->board.board[11]->owner == game->board.board[13]->owner) && (game->board.board[13]->owner == game->board.board[14]->owner)) {
            game->board.board[11]->monopoly = game->board.board[13]->monopoly = game->board.board[14]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == ORANGE) {
        if ((game->board.board[16]->owner == game->board.board[18]->owner) && (game->board.board[18]->owner == game->board.board[19]->owner)) {
            game->board.board[16]->monopoly = game->board.board[18]->monopoly = game->board.board[19]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == RED) {
        if ((game->board.board[21]->owner == game->board.board[23]->owner) && (game->board.board[23]->owner == game->board.board[24]->owner)) {
            game->board.board[21]->monopoly = game->board.board[23]->monopoly = game->board.board[24]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == YELLOW) {
        if ((game->board.board[26]->owner == game->board.board[27]->owner) && (game->board.board[27]->owner == game->board.board[29]->owner)) {
            game->board.board[26]->monopoly = game->board.board[27]->monopoly = game->board.board[29]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == GREEN) {
        if ((game->board.board[31]->owner == game->board.board[32]->owner) && (game->board.board[32]->owner == game->board.board[34]->owner)) {
            game->board.board[31]->monopoly = game->board.board[32]->monopoly = game->board.board[34]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == DARKBLUE) {
        if (game->board.board[37]->owner == game->board.board[39]->owner) {
            game->board.board[37]->monopoly = game->board.board[39]->monopoly = true;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == RAILROAD) {
        int num_rr = 0;
        if (recent_purchase->owner->ownership[5]) {
            num_rr++;
        }
        if (recent_purchase->owner->ownership[15]) {
            num_rr++;
        }
        if (recent_purchase->owner->ownership[25]) {
            num_rr++;
        }
        if (recent_purchase->owner->ownership[35]) {
            num_rr++;
        }
        
        
        if (recent_purchase->owner->ownership[5]) {
            game->board.board[5]->numHouses = num_rr;
        }
        if (recent_purchase->owner->ownership[15]) {
            game->board.board[15]->numHouses = num_rr;
        }
        if (recent_purchase->owner->ownership[25]) {
            game->board.board[25]->numHouses = num_rr;
        }
        if (recent_purchase->owner->ownership[35]) {
            game->board.board[35]->numHouses = num_rr;
        }
        
        if (num_rr == 4) {
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        }
    } else if (recent_purchase->color == UTILITY) {
        if (game->board.board[12]->owner == game->board.board[28]->owner) {
            game->board.board[12]->numHouses = game->board.board[28]->numHouses = 2;
            
            cout << "YOU'VE COMPLETED A MONOPOLY!" << endl;
        } else {
            recent_purchase->numHouses = 1;
        }
    }
}

string draw_chance ( Game* game ) {
    string chance_card;
    if (game->community_chest.size() == 1) {
        chance_card = game->community_chest[0];
        
        game->community_chest.pop_back();
        
        for (int i = 0; i < game->community_discard.size(); i++) {
            game->community_chest.push_back(game->community_discard[game->community_discard.size()-1]);
            game->community_discard.pop_back();
        }
    } else {
        int draw_num = rand();
        draw_num = draw_num % game->chance.size();
    
        chance_card = game->chance[draw_num];
    
        for (int i = draw_num; i < game->chance.size()-1; i++) {
            game->chance[i] = game->chance[i+1];
        }
    }
    
    game->chance.pop_back();
    
    return chance_card;
}

void execute_chance ( Game* game, string chance_card, int current_index ) {
    if (chance_card == "Make general repairs on all your property.  For each house pay $25, for each hotel pay $100.") {
        pay_for_buildings(game, current_index, 25, 100);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Go to Jail.  Go directly to Jail, do not pass Go, do not collect $200.") {
        move_token(game, current_index, 40, 30, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Speeding fine $15.") {
        game->players[current_index]->cashOnHand -= 15;
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Advance to the nearest railroad.  If unowned, you may buy it from the bank.  If owned, pay owner twice the rental to which they are otherwise entitled.") {
        if (game->players[current_index]->location_index < 5) {
            game->players[current_index]->location_index = 5;
        } else if (game->players[current_index]->location_index < 15) {
            game->players[current_index]->location_index = 15;
        } else if (game->players[current_index]->location_index < 25) {
            game->players[current_index]->location_index = 25;
        } else if (game->players[current_index]->location_index < 35) {
            game->players[current_index]->location_index = 35;
        } else {
            game->players[current_index]->location_index = 5;
            game->players[current_index]->cashOnHand += 200;
        }
        
        if (game->board.board[game->players[current_index]->location_index]->owner == nullptr) {
            offer_property(game, current_index);
        } else {
            pay_twice_rent (game, current_index);
        }
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Advance to Boardwalk.") {
        move_token(game, current_index, game->players[current_index]->location_index, 39, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Take a trip to Reading Railroad.  If you pass Go, collect $200.") {
        move_token(game, current_index, game->players[current_index]->location_index, 5, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "You have been elected chairman of the board.  Pay each player $50.") {
        for (int i = 0; i < game->players.size(); i++) {
            if (i == current_index) {
                continue;
            }
            game->players[current_index]->cashOnHand -= 50;
            game->players[i]->cashOnHand += 50;
        }
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Get out of Jail free.  This card may be kept until needed or traded.") {
        game->players[current_index]->chance_jail = true;
    } else if (chance_card == "Advance to St. Charles Place.  If you pass go, collect $200.") {
        move_token(game, current_index, game->players[current_index]->location_index, 11, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Advance to the nearest utility.  If unowned, you may buy it from the bank.  If owned, throw dice and pay owner ten times the amount thrown.") {
        pair<int, int> dice = roll_dice( game->players[current_index]->token );
        
        if (game->players[current_index]->location_index < 12) {
            move_token(game, current_index, game->players[current_index]->location_index, 12, dice.first+dice.second);
        } else if (game->players[current_index]->location_index < 28) {
            move_token(game, current_index, game->players[current_index]->location_index, 28, dice.first+dice.second);
        } else {
            move_token(game, current_index, game->players[current_index]->location_index, 12, dice.first+dice.second);
        }
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Go back three spaces.") {
        move_token(game, current_index, game->players[current_index]->location_index, game->players[current_index]->location_index - 3, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Advance to Go. (Collect $200)") {
        move_token(game, current_index, game->players[current_index]->location_index, 0, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Advance to Illinois Avenue.  If you pass Go, collect $200.") {
        move_token(game, current_index, game->players[current_index]->location_index, 24, 0);
        
        game->chance_discard.push_back(chance_card);
    } else if (chance_card == "Bank pays you dividend of $50.") {
        game->players[current_index]->cashOnHand += 50;
        
        game->chance_discard.push_back(chance_card);
    } else if ("Your building loan matures.  Collect $150.") {
        game->players[current_index]->cashOnHand += 150;
        
        game->chance_discard.push_back(chance_card);
    }
}

void offer_property ( Game* game, int current_index ) {
    print_purchase_opts();
    
    bool invalid_input = true;
    
    while (invalid_input) {
        string buyPass;
        getline(cin, buyPass);
        
        if (buyPass == "Buy") {
            buy_property(game, current_index);
            invalid_input = false;
        } else if (buyPass == "Pass") {
            pass_property(game, current_index);
            invalid_input = false;
        } else {
            cout << "Invalid input.  Please try again:" << endl;
        }
    }
}

void pay_twice_rent ( Game* game, int current_index ) {
    game->board.board[game->players[current_index]->location_index]->owner->cashOnHand += 2* get_rent(game, current_index, 0);
    game->players[current_index]->cashOnHand -= 2* get_rent(game, current_index, 0);
}

void move_token ( Game *game, int current_index, int current_location, int new_location, int dice_roll ) {
    if (new_location > 39) {
        new_location -= 40;
    }
    
    if ((passes_go(current_location, new_location)) && game->players[current_index]->free){
        pass_go(game, current_index);
    }
    
    game->players[current_index]->location_index = new_location;
    
    if (game->board.board[game->players[current_index]->location_index]->type == PROPERTY) {
        cout << print_token(game->players[current_index]->token) << " has moved to " << game->board.board[new_location]->name << endl;
        
        if (game->board.board[game->players[current_index]->location_index]->owner == nullptr) {
            offer_property(game, current_index);
        } else {
            if (game->board.board[game->players[current_index]->location_index]->owner == game->players[current_index]) {
                cout << print_token(game->players[current_index]->token) << " owns this property." << endl;
            } else {
                pay_rent(game, current_index, dice_roll);
            }
        }
        
    } else if (game->board.board[game->players[current_index]->location_index]->type == GO) {
        cout << print_token(game->players[current_index]->token) << " landed on Go and collected $200!" << endl;
        game->players[current_index]->cashOnHand += 200;
    } else if (game->board.board[game->players[current_index]->location_index]->type == JAIL) {
        cout << print_token(game->players[current_index]->token) << " landed on Jail but is just visiting!" << endl;
    } else if (game->board.board[game->players[current_index]->location_index]->type == FREEPARK) {
        cout << print_token(game->players[current_index]->token) << " landed on Free Parking!" << endl;
    } else if (game->board.board[game->players[current_index]->location_index]->type == GOTOJAIL) {
        cout << print_token(game->players[current_index]->token) << " was sent to Jail." << endl;
        game->players[current_index]->free = false;
        game->players[current_index]->location_index = 10;
    } else if (game->board.board[game->players[current_index]->location_index]->type == CHANCE) {
        cout << print_token(game->players[current_index]->token) << " landed on Chance!" << endl;
        string chance_card = draw_chance(game);
        
        cout << "Chance: " << chance_card << endl;
        
        execute_chance(game, chance_card, current_index);
    } else if (game->board.board[game->players[current_index]->location_index]->type == COMMUNITY) {
        cout << print_token(game->players[current_index]->token) << " landed on Community Chest!" << endl;
        string cc_card = draw_community(game);
        
        cout << "Community Chest: " << cc_card << endl;
        
        execute_community(game, cc_card, current_index);
    } else if (game->board.board[game->players[current_index]->location_index]->type == INCOME) {
        game->players[current_index]->cashOnHand -= 200;
        cout << print_token(game->players[current_index]->token) << " landed on Income Tax and paid $200 to the bank." << endl;
    } else if (game->board.board[game->players[current_index]->location_index]->type == LUXURY) {
        game->players[current_index]->cashOnHand -= 100;
        cout << print_token(game->players[current_index]->token) << " landed on Luxury Tax and paid $100 to the bank." << endl;
    }
    
    
}

void pass_go ( Game *game, int current_index ) {
    cout << print_token(game->players[current_index]->token) << " has passed Go and collected $200." << endl;
    game->players[current_index]->cashOnHand += 200;
}

void list_accounts ( Game *game ) {
    for (int i = 0; i < game->players.size(); i++) {
        cout << print_token(game->players[i]->token) << " has $" << game->players[i]->cashOnHand << endl;
    }
    cout << endl;
}

void list_properties ( Game *game ) {
    for (int i = 0; i < game->players.size(); i++) {
        cout << print_token(game->players[i]->token) << "'s Properties:" << endl;
        
        for (int j = 0; j < 40; j++) {
            if (game->players[i]->ownership[j]) {
                cout << "\t" << game->board.board[j]->name << endl;
            }
        }
    }
    cout << endl;
}

bool passes_go ( int current_location, int new_location ) {
    if ((new_location - current_location < 0) && (new_location != 0)) {
        return true;
    } else {
        return false;
    }
}

string draw_community ( Game *game ) {
    string cc_card;
    if (game->community_chest.size() == 1) {
        cc_card = game->community_chest[0];
        
        game->community_chest.pop_back();
        
        for (int i = 0; i < game->community_discard.size(); i++) {
            game->community_chest.push_back(game->community_discard[game->community_discard.size()-1]);
            game->community_discard.pop_back();
        }
    } else {
        int draw_num = rand();
        draw_num = draw_num % game->community_chest.size();
    
        cc_card = game->community_chest[draw_num];
    
        for (int i = draw_num; i < game->community_chest.size() - 1; i++) {
            game->community_chest[i] = game->community_chest[i+1];
        }
        
        game->community_chest.pop_back();
    }
    
    return cc_card;
}

void execute_community ( Game *game, string cc_card, int current_index ) {
    if (cc_card == "From sale of stock you get $50.") {
        game->players[current_index]->cashOnHand += 50;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "School fees.  Pay $50.") {
        game->players[current_index]->cashOnHand -= 50;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "You have won second prize in a beauty contest.  Collect $10.") {
        game->players[current_index]->cashOnHand += 10;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "You are assessed for street repairs: pay $40 per house and $115 per hotel you own.") {
        pay_for_buildings(game, current_index, 40, 115);
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Hospital fees.  Pay $100.") {
        game->players[current_index]->cashOnHand -= 100;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Go to Jail.  Go directly to Jail, do not pass Go, do not collect $200.") {
        move_token(game, current_index, game->players[current_index]->location_index, 30, 0);
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "You inherit $100.") {
        game->players[current_index]->cashOnHand += 100;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Receive $25 consultancy fee.") {
        game->players[current_index]->cashOnHand += 25;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Doctor's fees.  Pay $50.") {
        game->players[current_index]->cashOnHand -= 50;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "It is your birthday.  Collect $10 from every player.") {
        for (int i = 0; i < game->players.size(); i++) {
            if (i == current_index) {
                continue;
            }
            
            game->players[i]->cashOnHand -= 10;
            game->players[current_index] += 10;
        }
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Get out of Jail free.  This card may be kept until needed or traded.") {
        game->players[current_index]->cc_jail = true;
    } else if (cc_card == "Holiday fund matures.  Receive $100.") {
        game->players[current_index]->cashOnHand += 100;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Advance to Go. (Collect $200)") {
        move_token(game, current_index, game->players[current_index]->location_index, 0, 0);
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Bank error in your favor.  Collect $200.") {
        game->players[current_index]->cashOnHand += 200;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Life insurance matures.  Collect $100.") {
        game->players[current_index]->cashOnHand += 100;
        
        game->community_discard.push_back(cc_card);
    } else if (cc_card == "Income tax refund.  Collect $20.") {
        game->players[current_index]->cashOnHand += 20;
        
        game->community_discard.push_back(cc_card);
    }
}

void pay_for_buildings ( Game *game, int current_index, int housePrice, int hotelPrice ) {
    int numHouses = 0;
    int numHotels = 0;
    
    for (int i = 0; i < 40; i++) {
        if (game->players[current_index]->ownership[i]) {
            if ((game->board.board[i]->color != RAILROAD) && (game->board.board[i]->color != UTILITY)) {
                if (game->board.board[i]->numHouses == 5) {
                    numHotels++;
                } else {
                    numHouses += game->board.board[i]->numHouses;
                }
            }
        }
    }
    
    int totalPrice = (numHouses*housePrice) + (numHotels*hotelPrice);
    
    game->players[current_index]->cashOnHand -= totalPrice;
}

void manage_properties ( Game *game, int current_index ) {
    print_manage_opts();
    
    bool invalid_input = true;
    
    while (invalid_input) {
        string input;
        getline(cin, input);
        
        if (input == "Mortgage Properties") {
            invalid_input = false;
            
            mortgage(game, current_index);
        } else if (input == "Unmortgage Properties") {
            invalid_input = false;
            
            bool prop_listed = false;
            int unmortgage_index = 0;
            
            cout << "Properties that can be unmortgaged:" << endl;
            for (int i = 0; i < 40; i++) {
                if ((game->players[current_index]->ownership[i]) && (game->board.board[i]->mortgaged)) {
                    prop_listed = true;
                    cout << "\t" << game->board.board[i]->name << endl;
                }
            }
            
            if (prop_listed) {
                bool invalid_input2 = true;
                
                while (invalid_input2) {
                    getline(cin, input);
                    
                    for (int i = 0; i < 40; i++) {
                        if (input == game->board.board[i]->name) {
                            invalid_input2 = false;
                            unmortgage_index = i;
                            break;
                        }
                    }
                    
                    if (unmortgage_index != 0) {
                        unmortgage_property(game, unmortgage_index);
                    } else {
                        cout << "No such property!  Try again: " << endl;
                    }
                }
            } else {
                cout << "Sorry!  No Properties to Unmortgage." << endl;
            }
            
            
        } else if (input == "Build Improvements") {
            invalid_input = false;
            
            int build_index = 0;
            
            cout << "Properties that can be built upon:" << endl;
            bool prop_listed = false;
            
            for (int i = 0; i < 40; i++) {
                if ((game->players[current_index]->ownership[i]) && (game->board.board[i]->monopoly)) {
                    prop_listed = true;
                    cout << "\t" << game->board.board[i]->name <<  endl;
                }
            }
            
            if (prop_listed) {
                bool invalid_input2 = true;
                
                while (invalid_input2) {
                    getline(cin, input);
                    
                    for (int i = 0; i < 40; i++) {
                        if (input == game->board.board[i]->name) {
                            invalid_input2 = false;
                            build_index = i;
                            break;
                        }
                    }
                    
                    if (build_index != 0) {
                        build_property(game, build_index);
                    } else {
                        cout << "No such property!  Try again: " << endl;
                    }
                }
            }
        } else if (input == "Cancel") {
            invalid_input = false;
        } else {
            cout << "Invalid Input.  Please try again: " << endl;
        }
    }
}

void print_manage_opts() {
    cout << "Manage Properties:" << endl;
    cout << "\tMortgage Properties" << endl;
    cout << "\tUnmortgage Properties" << endl;
    cout << "\tBuild Improvements" << endl;
    cout << "\tCancel" << endl;
    cout << "Please Enter:" << endl;
}

void mortgage ( Game *game, int current_index ) {
    bool prop_listed = false;
    int mortgage_index = 0;
    
    string input;
    
    cout << "Properties that can be mortgaged:" << endl;
    for (int i = 0; i < 40; i++) {
        if ((game->players[current_index]->ownership[i]) && (!game->board.board[i]->mortgaged)) {
            prop_listed = true;
            cout << "\t" << game->board.board[i]->name << endl;
        }
    }
    
    if (prop_listed) {
        bool invalid_input2 = true;
        
        cout << "Please Select the Property to Mortgage:" << endl;
        
        while (invalid_input2) {
            getline(cin, input);
            
            for (int i = 0; i < 40; i++) {
                if (input == game->board.board[i]->name) {
                    invalid_input2 = false;
                    mortgage_index = i;
                    break;
                }
            }
        }
        
        if (mortgage_index != 0) {
            mortgage_property(game, mortgage_index);
        } else {
            cout << "No such property!  Try again: " << endl;
        }
    } else {
        cout << "Sorry!  No Properties to Mortgage." << endl;
    }
}

void mortgage_property ( Game *game, int mortgage_index ) {
    game->board.board[mortgage_index]->mortgaged = true;
    
    game->board.board[mortgage_index]->owner->cashOnHand += game->board.board[mortgage_index]->price/2;
}

void unmortgage_property ( Game *game, int unmortgage_index ) {
    game->board.board[unmortgage_index]->mortgaged = false;
    
    game->board.board[unmortgage_index]->owner->cashOnHand -= game->board.board[unmortgage_index]->price/2;
}

void build_property( Game *game, int build_index ) {
    cout << "How many buildings would you like to build?" << endl;
    string st_input;
    
    getline(cin, st_input);
    
    int input = stoi(st_input);
    
    game->board.board[build_index]->numHouses += input;
    
    game->board.board[build_index]->owner->cashOnHand -= input*game->board.board[build_index]->houseCost;
}

void trade ( Game *game, int current_index ) {
    trade_companions (game, current_index);
}

void trade_companions ( Game *game, int current_index ) {
    cout << "Trade with:" << endl;
    for (int i = 0; i < game->players.size(); i++) {
        if (current_index == i) {
            continue;
        }
        cout << "\t" << print_token(game->players[i]->token) << endl;
    }
    
    cout << "Who do you want to trade with?" << endl;
    
    bool invalid_input = true;
    
    while(invalid_input) {
        string input;
        getline(cin, input);
        
        int trade_index = -1;
        
        for (int i = 0; i < game->players.size(); i++) {
            if (input == print_token(game->players[i]->token)) {
                invalid_input = false;
                trade_index = i;
                
            }
        }
        
        if (trade_index != -1) {
            initialize_trade (game, current_index, trade_index);
        } else {
            cout << "Invalid input.  Try Again: " << endl;
        }
    }

}

void initialize_trade ( Game *game, int current_index, int trade_index ) {
    cout << "The properties you have:" << endl;
    for (int i = 0; i < 40; i++) {
        if (game->players[current_index]->ownership[i]) {
            cout << "\t" << game->board.board[i]->name << endl;
        }
    }
    cout << "You have $" << game->players[current_index]->cashOnHand;
    if (game->players[current_index]->cc_jail || game->players[current_index]->chance_jail) {
        if (game->players[current_index]->cc_jail && game->players[current_index]->chance_jail) {
            cout << "You also have 2 'Get out of Jail Free' Cards" << endl;
        } else {
            cout << "You also have 1 'Get out of Jail Free' Card" << endl;
        }
    }
    
    cout << "The properties " << print_token(game->players[trade_index]->token) << " has:" << endl;
    for (int i = 0; i < 40; i++) {
        if (game->players[trade_index]->ownership[i]) {
            cout << "\t" << game->board.board[i]->name << endl;
        }
    }
    cout << print_token(game->players[trade_index]->token) << " has $" << game->players[trade_index]->cashOnHand << endl;
    if (game->players[trade_index]->cc_jail || game->players[trade_index]->chance_jail) {
        if (game->players[trade_index]->cc_jail && game->players[trade_index]->chance_jail) {
            cout << print_token(game->players[trade_index]->token) << " also has 2 'Get out of Jail Free' Cards" << endl;
        } else {
            cout << print_token(game->players[trade_index]->token) << " also has 1 'Get out of Jail Free' Card" << endl;
        }
    }
    
    compose_trade(game, current_index, trade_index);
}

void compose_trade ( Game *game, int current_index, int trade_index ) {
    vector<Space *> take_prop;
    vector<Space *> offer_prop;
    int take_money = 0;
    int offer_money = 0;
    bool cc_take = false;
    bool cc_offer = false;
    bool chance_take = false;
    bool chance_offer = false;
    
    bool invalid_input = true;
    
    while (invalid_input) {
        cout << "Add Property from Opponent" << endl;
        cout << "Add Money from Opponent" << endl;
        cout << "Add 'Get out of Jail Free' Card from Opponent" <<  endl;
        cout << "Add Property to Offer" << endl;
        cout << "Add Money to Offer" << endl;
        cout << "Add 'Get out of Jail Free' Card to Offer" << endl;
        cout << "Make Offer" << endl;
        cout << "Cancel Offer" << endl;
        cout << "Please enter choice: " << endl;
        string input;
        getline(cin, input);
        
        if (input == "Add Property from Opponent") {
            cout << "Which property would you like to add?" << endl;
            
            bool invalid_input2 = true;
            
            while (invalid_input2) {
                getline(cin, input);
                for (int i = 0; i < 40; i++) {
                    if (input == game->board.board[i]->name) {
                        invalid_input2 = false;
                        take_prop.push_back(game->board.board[i]);
                    }
                }
                
                if (invalid_input2) {
                    cout << "That property is not available for trade.  Please try again:" << endl;
                }
            }
        } else if (input == "Add Money from Opponent") {
            cout << "How much money would you like?" << endl;
            string money_in;
            
            getline(cin, money_in);
            
            take_money = stoi(money_in);
        } else if (input == "Add 'Get out of Jail Free' Car from Opponent") {
            if (game->players[trade_index]->cc_jail || game->players[trade_index]->chance_jail) {
                if (game->players[trade_index]->cc_jail && game->players[trade_index]->chance_jail) {
                    cc_take = true;
                } else if (game->players[trade_index]->cc_jail) {
                    cc_take = true;
                } else {
                    chance_take = true;
                }
            } else {
                cout << "Sorry!  " << print_token(game->players[trade_index]->token) << " has no 'Get out of Jail Free' Cards." << endl;
            }
        } else if (input == "Add Property to Offer") {
            cout << "Which property would you like to add?" << endl;
            
            bool invalid_input2 = true;
            
            while (invalid_input2) {
                getline(cin, input);
                for (int i = 0; i < 40; i++) {
                    if (input == game->board.board[i]->name) {
                        invalid_input2 = false;
                        offer_prop.push_back(game->board.board[i]);
                    }
                }
                
                if (invalid_input2) {
                    cout << "That property is not available for trade.  Please try again:" << endl;
                }
            }
        } else if (input == "Add Money to Offer") {
            cout << "How much money would you like to offer?" << endl;
            
            string money_in;
            getline(cin, money_in);
            
            offer_money = stoi(money_in);
        } else if (input == "Add 'Get out of Jail Free' Card to Offer") {
            if (game->players[current_index]->cc_jail || game->players[current_index]->chance_jail) {
                if (game->players[current_index]->cc_jail && game->players[current_index]->chance_jail) {
                    cc_offer = true;
                } else if (game->players[current_index]->cc_jail) {
                    cc_offer = true;
                } else {
                    chance_offer = true;
                }
            } else {
                cout << "Sorry!  You do not have any 'Get out of Jail Free' Cards." << endl;
            }
        } else if (input == "Cancel Offer") {
            
        } else if (input == "Make Offer") {
            make_offer (game, current_index, trade_index, take_prop, offer_prop, take_money, offer_money, cc_take, cc_offer, chance_take, chance_offer);
            
            invalid_input = false;
        } else {
            cout << "Invalid input.  Please try again: " << endl;
        }
    }
}

void make_offer ( Game *game, int current_index, int trade_index, vector<Space *> take_prop, vector<Space *> offer_prop, int take_money, int offer_money, bool cc_take, bool cc_offer, bool chance_take, bool chance_offer ) {
    cout << print_token(game->players[trade_index]->token) << ", " << print_token(game->players[current_index]->token) << " would like to trade with you." << endl;
    cout << print_token(game->players[current_index]->token) << " is offering: " << endl;
    for (int i = 0; i < offer_prop.size(); i++) {
        cout << "\t" << offer_prop[i]->name << endl;
    }
    if (offer_money) {
        cout << "\t$" << offer_money << endl;
    }
    if (cc_offer || chance_offer) {
        if (cc_offer && chance_offer) {
            cout << "\t2 'Get out of Jail Free' Cards." << endl;
        } else {
            cout << "\t1 'Get out of Jail Free' Card≥." << endl;
        }
    }
    
    cout << "And in return, you will give up:" << endl;
    
    for (int i = 0; i < take_prop.size(); i++) {
        cout << "\t" << take_prop[i]->name << endl;
    }
    if (take_money) {
        cout << "\t$" << take_money << endl;
    }
    if (cc_take || chance_take) {
        if (cc_take && chance_take) {
            cout << "\t2 'Get out of Jail Free' Cards." << endl;
        } else {
            cout << "\t1 'Get out of Jail Free' Card." << endl;
        }
    }
    
    string input;
    cout << print_token(game->players[trade_index]->token) << ", would you like to accept this trade?  (Yes/No)" << endl;
    getline(cin, input);
    
    bool invalid_input = true;
    
    while (invalid_input) {
        if (input == "Yes") {
            invalid_input = false;
            
            execute_trade(game, current_index, trade_index, take_prop, offer_prop, take_money, offer_money, cc_take, cc_offer, chance_take, chance_offer);
        } else if (input == "No") {
            invalid_input = false;
            
            cout << "Sorry, " << print_token(game->players[current_index]->token) << " the deal is off!" << endl;
        } else {
            cout << "Invalid input.  Please try again:" << endl;
        }
    }
}

void execute_trade ( Game *game, int current_index, int trade_index, vector<Space *> take_prop, vector<Space *> offer_prop, int take_money, int offer_money, bool cc_take, bool cc_offer, bool chance_take, bool chance_offer ) {
    cout << "Trade went through!" << endl;
    
    for (int i = 0; i < take_prop.size(); i++) {
        take_prop[i]->owner = game->players[current_index];
        
        for (int j = 0; j < 40; j++) {
            if (game->board.board[j] == take_prop[i]) {
                game->players[current_index]->ownership[j] = true;
                game->players[trade_index]->ownership[j] = false;
            }
        }
        
        update_monopoly(game, take_prop[i]);
    }
    for (int i = 0; i < offer_prop.size(); i++) {
        offer_prop[i]->owner = game->players[trade_index];
        
        for (int j = 0; j < 40; j++) {
            if (game->board.board[j] == offer_prop[i]) {
                game->players[current_index]->ownership[j] = false;
                game->players[trade_index]->ownership[j] = true;
            }
        }
        
        update_monopoly(game, offer_prop[i]);
    }
    
    game->players[current_index]->cashOnHand += take_money;
    game->players[trade_index]->cashOnHand -= take_money;
    
    game->players[current_index]->cashOnHand -= offer_money;
    game->players[trade_index]->cashOnHand += offer_money;
    
    if (cc_offer) {
        game->players[current_index]->cc_jail = false;
        game->players[trade_index]->cc_jail = true;
    }
    if (chance_offer) {
        game->players[current_index]->chance_jail = false;
        game->players[trade_index]->chance_jail = true;
    }
    if (cc_take) {
        game->players[current_index]->cc_jail = true;
        game->players[trade_index]->cc_jail = false;
    }
    if (chance_take) {
        game->players[current_index]->chance_jail = true;
        game->players[trade_index]->chance_jail = false;
    }
}

bool check_cash_flow ( int cost, int cash ) {
    if (cost <= cash) {
        return true;
    } else {
        return false;
    }
}

void broke_player ( Game *game, int current_index ) {
    print_broke_opts();
    
    bool invalid_input = true;
    
    while (invalid_input) {
        string input;
        getline(cin, input);
        
        if (input == "Trade") {
            invalid_input = false;
            
            trade(game, current_index);
            buy_property(game, current_index);
        } else if (input == "Mortgage Properties") {
            invalid_input = false;
            
            mortgage(game, current_index);
            buy_property(game, current_index);
        } else if (input == "Pass on the Property") {
            invalid_input = false;
            
            cout << "Player passes.  Nothing happens yet!" << endl;
        } else {
            cout << "Invalid Input.  Please try again." << endl;
        }
    }
}

void print_broke_opts() {
    cout << "You do not have enough money.  What would you like to do?" << endl;
    cout << "\tTrade" << endl;
    cout << "\tMortgage Properties" << endl;
    cout << "\tPass on the Property." << endl;
}

void get_out_of_jail ( Game *game, int current_index, string method ) {
    if (method == "Doubles") {
        cout << print_token(game->players[current_index]->token) << " rolled doubles and was released from Jail." << endl;
        game->players[current_index]->free = true;
    } else if (method == "Card") {
        cout << print_token(game->players[current_index]->token) << " used a 'Get Out of Jail Free' Card." << endl;
        game->players[current_index]->free = true;
        
        if (game->players[current_index]->cc_jail) {
            game->players[current_index]->cc_jail = false;
            
            game->community_discard.push_back("Get out of Jail free.  This card may be kept until needed or traded.");
        } else {
            game->players[current_index]->chance_jail = false;
            
            game->chance_discard.push_back("Get out of Jail free.  This card may be kept until needed or traded.");
        }
    } else if (method == "Cash") {
        cout << print_token(game->players[current_index]->token) << " paid $50 and was released from Jail." << endl;
        game->players[current_index]->cashOnHand -= 50;
        game->players[current_index]->free = true;
    }
}

void in_jail ( Game *game, int current_index ) {
    cout << print_token(game->players[current_index]->token) << " is in jail.  Options: " << endl;
    if (game->jail_count[current_index] < 3) {
        cout << "\tRoll for Doubles" << endl;
    }
    if (game->players[current_index]->cc_jail || game->players[current_index]->chance_jail) {
        cout << "\tUse 'Get Out of Jail Free' Card" << endl;
    }
    cout << "\tPost $50 Bail" << endl;
    cout << "\tTrade" << endl;
    cout << "\tManage Properties" << endl;
    cout << "\tList Accounts" << endl;
    cout << "\tList Properties" << endl;
    cout << "Please select an option: " << endl;
}















































