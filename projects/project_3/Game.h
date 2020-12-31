//
//  Game.hpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Board.h"
class Player;

class Game
{
public:
    Game(const Board& b, Player* south, Player* north);
    void display() const;
    void status(bool& over, bool& hasWinner, Side& winner) const;
    bool move();
    void play();
    int beans(Side s, int hole) const;
    
private:
    // a helper function for move that sows the board based on the hole choice of the chooseMove function of the player whose turn it is
    bool takeTurn();
    Player* m_northPlayer;
    Player* m_southPlayer;
    Board m_board;
    bool m_southTurn;
};

#endif /* Game_hpp */
