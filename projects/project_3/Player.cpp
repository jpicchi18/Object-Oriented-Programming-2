//
//  Player.cpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//


// Place your Player member function implementations here, as well as those for HumanPlayer, BadPlayer, and SmartPlayer.

#include "Player.h"
#include "Board.h"
#include "Side.h"
#include <string>
#include <iostream>
#include <string>
using namespace std;


//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};



////////////////////////////////////////////////
///////////CHOOSEMOVE FUNCTIONS//////////////////
////////////////////////////////////////////////


int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    // check if a move is possible
    bool allHolesEmpty = true;
    for (int i = 1; i < b.holes() + 1; i++)
    {
        if (b.beans(s, i) > 0)
            allHolesEmpty = false;
    }
    
    // if all the holes on that side are empty...
    if (allHolesEmpty)
        return -1;
    
    // if theres a non-empty hole, prompt the user
    int hole = -1;
    while (hole < 1 || hole > b.holes() || b.beans(s, hole) < 1)
    {
        cout << "Select a hole, " << name() << ": ";
        cin >> hole;
        if (hole < 1 || hole > b.holes())
            cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        else if (b.beans(s, hole) < 1)
            cout << "There are no beans in that hole." << endl;
    }
    
    return hole;
}


// Arbitrary move: chooses the leftmost hole
int BadPlayer::chooseMove(const Board& b, Side s) const
{
    
    int result = -1;
    // choose the leftmost hole that has beans
    for (int i = 1; i < b.holes() + 1; i++)
    {
        if (b.beans(s, i) > 0) {
            result = i;
            break;
        }
    }
    
    // returns -1 if all the holes on side s are empty
    return result;
}


int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    AlarmClock ac(4900);
    int depth = 5; // decide how deep you want to search
    int bestHole = -1;
    int valueDoesntMatter;
    
    // find the best move
    findBestMove(ac, s, b, depth, bestHole, valueDoesntMatter);
    
    return bestHole;
}


// helper function for chooseMove
    // north player always wants max
    // south player always wants min
void SmartPlayer::findBestMove(AlarmClock& ac, Side playerSide, const Board& b, int depth, int& bestHole, int& value) const
{
    // IF NO MOVE FOR THE PLAYER EXISTS (i.e. THE GAME IS OVER)
    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
    {
        bestHole = -1;
        value = evaluatePosition(b);
        return;
    }
    
    // IF WE SHOULD NOT SEARCH BELOW THIS NODE
    if (ac.timedOut() || depth <= 0)
    {
        bestHole = -1;
        value = evaluatePosition(b);
        return;
    }
    
    // make sure the bestValueSoFar is always overriden by the first valid hole
    int bestValueSoFar = 0;
    if (playerSide == NORTH)
        bestValueSoFar = -9999;        // lowest possible value
    else if (playerSide == SOUTH)
        bestValueSoFar = 9999;         // highest possible value
    
    // give the opponent the opposite side
    Side opponentSide = opponent(playerSide);
    
    // FOR EVERY HOLE H THE PLAYER CAN CHOOSE
    for (int h = 1; h < b.holes()+1; h++)
    {
        // skip the hole if it's invalid
        if (b.beans(playerSide, h) == 0)
            continue;
        
        Side endSide;
        int endHole;
        int secondTurnHole, trashValue;
        
        // "MAKE" THE MOVE H:
        int hole2, value2;
        
        // sow a copy of the board
        Board copyBoard = b;
        copyBoard.sow(playerSide, h, endSide, endHole);
        
        // check for another turn
        while (endSide == playerSide && endHole == 0 && copyBoard.beansInPlay(SOUTH) > 0 && copyBoard.beansInPlay(NORTH) > 0)
        {
            // find the best second move
            findBestMove(ac, playerSide, copyBoard, depth-1, secondTurnHole, trashValue);
            
            if (secondTurnHole == -1)
                break;
            
            // apply the second move
            copyBoard.sow(playerSide, secondTurnHole, endSide, endHole);
        }
        
        // check for a capture
        if (endSide == playerSide && endHole != 0 && copyBoard.beans(playerSide, endHole) == 1 && copyBoard.beans(opponentSide, endHole) > 0)
        {
            copyBoard.moveToPot(playerSide, endHole, playerSide);
            copyBoard.moveToPot(opponentSide, endHole, playerSide);
        }
        
        
        // OPPONENT CHOOSES THEIR MOVE
        findBestMove(ac, opponentSide, copyBoard, depth-1, hole2, value2);
        
        
        // IF V2 IS BETTER FOR THE PLAYER THAN THE BEST SEEN SO FAR
        if (playerSide == NORTH)
        {
            // choose the max
            if (value2 > bestValueSoFar)
            {
                bestHole = h;
                value = value2;
                bestValueSoFar = value2;
            }
        }
        else if (playerSide == SOUTH)
        {
            // choose the min
            if (value2 < bestValueSoFar)
            {
                bestHole = h;
                value = value2;
                bestValueSoFar = value2;
            }
        }
    }
    
    return;
}

// helper function for findBestMove
int SmartPlayer::evaluatePosition(const Board& b) const
{
    int returnVal = -1;
    
    // north wants high differences, south wants low differences
    int difference = (b.beans(NORTH, 0) + b.beansInPlay(NORTH)) - (b.beans(SOUTH, 0) + b.beansInPlay(SOUTH));
    
    // if the game is over... check for the winner
    if (b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0)
    {
        if (difference > 0)     // north won
            returnVal = 1000;      // a really high number
        if (difference < 0)     // south won
            returnVal = -1000;     // a really low number
        if (difference == 0)
            return 0;
    }
    else    // the game is not over yet, but we still want to evaluate the board
    {
        returnVal = difference;
    }
    
    // if one side already has over half the beans, that side won!
    if (b.beans(NORTH, 0) >= b.totalBeans()/2)
        returnVal = 1000;
    else if (b.beans(SOUTH, 0) >= b.totalBeans()/2)
        returnVal = -1000;
    
    return returnVal;
}
