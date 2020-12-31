//
//  Player.hpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//


// Place your Player class definition here, as well as the definitions for the HumanPlayer, BadPlayer, and SmartPlayer classes.

#ifndef Player_hpp
#define Player_hpp

#include <string>
#include "Board.h"
class AlarmClock;

// Player is an abstract base class that defines a common interface that all kinds of players (human and various computer players) must implement. It must support these public member functions:
class Player
{
public:
    Player(std::string name) : m_name(name) {}
    std::string name() const { return m_name; }
    virtual bool isInteractive() const { return false; }
    virtual int chooseMove(const Board& b, Side s) const = 0;
    virtual ~Player() {}
    
private:
    std::string m_name;
};



class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name) : Player(name) {}
    virtual bool isInteractive() const { return true; }
    virtual int chooseMove(const Board& b, Side s) const;
};


class BadPlayer : public Player
{
public:
    BadPlayer(std::string name)  : Player(name) {}
    virtual int chooseMove(const Board& b, Side s) const;

};



class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name) : Player(name) {}
    virtual int chooseMove(const Board& b, Side s) const;

private:
    // a helper function for chooseMove that chooses the best hole to play, given a certain board configuration b:
    void findBestMove(AlarmClock& ac, Side playerSide, const Board& b, int depth, int& bestHole, int& value) const;
    // a helper function for findBestMove that applies the heuristics of the minimax algorithm to analyze how good a certain board configuration is
    int evaluatePosition(const Board& b) const;
};


#endif /* Player_hpp */
