//
//  Game.cpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//
#include <cmath>
#include <iostream>
#include <string>
#include "Game.h"
#include "Player.h"
#include "Side.h"
#include <iostream>
using namespace std;

// Construct a Game to be played with the indicated players on a copy of the board b. The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north)
: m_board(b), m_southTurn(true)
{
    m_southPlayer = south;
    m_northPlayer = north;
}

// Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
void Game::display() const
{
    // print north player's name
    for (int i = 0; i < 5/2*m_board.holes()/2; i++) // centers the name
        cout << " ";
    cout << m_northPlayer->name() << endl;
    
    // print the holes in the north
    cout << "  ";
    for (int i = 1; i < m_board.holes() + 1; i++)
    {
        cout << m_board.beans(NORTH, i) << "  ";
    }
    cout << endl;
    
    // print the pots
    cout << m_board.beans(NORTH, 0);
    for (int i = 0; i < m_board.holes(); i++)
        cout << "   ";
    cout << m_board.beans(SOUTH, 0) << endl;
    
    // print the holes in the south
    cout << "  ";
    for (int i = 1; i < m_board.holes() + 1; i++)
    {
        cout << m_board.beans(SOUTH, i) << "  ";
    }
    cout << endl;
    
    // print south player's name
    for (int i = 0; i < 5/2*m_board.holes()/2; i++)   // centers the name
        cout << " ";
    cout << m_southPlayer->name() << endl;
}

// If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    // the game isnt over...
    if (m_board.beansInPlay(SOUTH) > 0 && m_board.beansInPlay(NORTH) > 0)
    {
        over = false;
        return;
    }
    
    // the game is over...
    over  = true;
    hasWinner = true;
    
    // set the winner of the game
    if (m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH) > m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH))
        winner = SOUTH;
    else if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) > m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
        winner = NORTH;
    else
        hasWinner = false;
    
    return;
}

// If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
bool Game::move()   // TODO
{
    bool result = takeTurn();
    
    // if the game is over, sweep up the beans
    if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)
    {
        // tell the player's you're gonna sweep them
        if (m_board.beansInPlay(SOUTH) > 0)
            cout << "Sweeping remaining beans into " << m_southPlayer->name() << "'s pot." << endl;
        else if (m_board.beansInPlay(NORTH) > 0)
            cout << "Sweeping remaining beans into " << m_northPlayer->name() << "'s pot." << endl;
    
        if (m_board.beansInPlay(SOUTH) > 0 || m_board.beansInPlay(NORTH) > 0)
        {
            // sweep in the remaining beans
            for (int i = 1; i < m_board.holes() + 1; i++)
            {
                m_board.moveToPot(NORTH, i, NORTH);
                m_board.moveToPot(SOUTH, i, SOUTH);
            }
            
            display();
        }
    }
    
    // if the game was already over when move was called, return false
    if (!result)
        return false;
    
    // change whose turn it is
    m_southTurn = !m_southTurn;
    
    return true;
}

// helper function for move()
bool Game::takeTurn()
{
    // return false if the game is over
    if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)
        return false;
    
    // see whose turn it is
    Player* playerMoving = nullptr;
    Side playerSide;
    Side opponentSide;
    if (m_southTurn)
    {
        playerMoving = m_southPlayer;
        playerSide = SOUTH;
        opponentSide = NORTH;
    }
    else
    {
        playerMoving = m_northPlayer;
        playerSide = NORTH;
        opponentSide = SOUTH;
    }
    
    // have the player make their move
    Side endSide = playerSide;
    int endHole = -1;
    
    // pick a hole and use it to sow the board
    int holeChoice = playerMoving->chooseMove(m_board, playerSide);
    cout << playerMoving->name() << " chooses hole " << holeChoice << endl;
    
    m_board.sow(playerSide, holeChoice, endSide, endHole);
    display();
    
    // check for another turn
    if (endSide == playerSide && endHole == 0 && m_board.beansInPlay(SOUTH) > 0 && m_board.beansInPlay(NORTH) > 0)
    {
        cout << playerMoving->name() << " gets another turn." << endl;
        takeTurn();
    }
    else if (endSide == playerSide && endHole != 0 && m_board.beans(playerSide, endHole) == 1 && m_board.beans(opponentSide, endHole) > 0) // check for a capture
    {
        // move the necessary beans to the player's pot: they've been captured
        m_board.moveToPot(playerSide, endHole, playerSide);
        m_board.moveToPot(opponentSide, endHole, playerSide);
    }
    
    return true;
}

// Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
void Game::play()
{
    // display the starting board
    display();
    
    // make moves until you can't
    string uselessStringForGetline;
    while (move())
    {
        if (!m_southPlayer->isInteractive() && !m_northPlayer->isInteractive() && m_board.beansInPlay(SOUTH) > 0 && m_board.beansInPlay(NORTH) > 0)
        {
            cout << "Press ENTER to continue";
            getline(cin, uselessStringForGetline);
        }
    }
    
    // prompt the user before announcing the winner
    if (!m_southPlayer->isInteractive() && !m_northPlayer->isInteractive())
    {
        cout << "Press ENTER to continue";
        getline(cin, uselessStringForGetline);
    }
    
    // see who won the game
    bool over, hasWinner;
    Side winner;
    status(over, hasWinner, winner);
    
    if (over)
    {
        if (hasWinner)
        {
            if (winner == NORTH)
                cout << "The winner is " << m_northPlayer->name() << "." << endl;
            else if (winner == SOUTH)
                cout << "The winner is " << m_southPlayer->name() << "." << endl;
        }
        else
            cout << "The game ended in a tie." << endl;
    }
    else    // impossible: throw an error!
        cerr << "error! the game is not over!" << endl;
}

// Return the number of beans in the indicated hole or pot of the game's board, or −1 if the hole number is invalid. This function exists so that we and you can more easily test your program.
int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}
