//
//  Board.cpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "Board.h"
#include "Side.h"


// Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if (nHoles < 1)
        nHoles = 1;
    if (nInitialBeansPerHole < 0)
        nInitialBeansPerHole = 0;
    
    // record the number of holes
    m_nHolesIncludingPot = nHoles+1;
    
    // construct holes on both sides: leave room for the pot!
    m_north = new int[m_nHolesIncludingPot];
    m_south = new int[m_nHolesIncludingPot];
    
    // add beans to everything except for the pots
    for (int i = 1; i < nHoles+1; i++)
    {
        m_north[i] = nInitialBeansPerHole;
        m_south[i] = nInitialBeansPerHole;
    }
    
    // each pot starts with 0 beans
    *m_south = *m_north = 0;
}

// Return the number of holes on a side (not counting the pot).
int Board::holes() const
{
    return m_nHolesIncludingPot-1;
}

// Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
    // check if hole is valid
    if (hole < 0 || hole > m_nHolesIncludingPot-1)
        return -1;
    
    if (s == SOUTH)
        return m_south[hole];
    else if (s == NORTH)
        return m_north[hole];
    
    // impossible to reach this point, so return an error just in case
    return -1;
}

// Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
    int result = 0;
    
    if (s == SOUTH)
    {
        // skip the pot
        for (int i = 1; i < m_nHolesIncludingPot; i++)
        {
            result += m_south[i];
        }
    }
    // do the same for the north side
    else if (s == NORTH)
    {
        // skip the pot
        for (int i = 1; i < m_nHolesIncludingPot; i++)
        {
            result += m_north[i];
        }
    }
    
    return result;
}

// Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
    int result = 0;
    
    // add the beans in non-pot holes
    result += beansInPlay(SOUTH) + beansInPlay(NORTH);
    
    // add the beans in the holes
    result += *m_north + *m_south;
    
    return result;
}

// If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    // check if the hole is invalid or a pot
    if (hole < 1 || hole > m_nHolesIncludingPot-1)
        return false;
    // check if the hole is empty
    if ((s == SOUTH && m_south[hole] == 0) || (s == NORTH && m_north[hole] == 0))
        return false;
    
    // initialize a pointer to the starting hole
    int* temp = nullptr;
    if (s == SOUTH)
        temp = &m_south[hole];
    if (s == NORTH)
        temp = &m_north[hole];
    
    // track the number of beans left
    int distributableBeans = *temp;
    
    // track the ending hole and ending side
    endSide = s;
    endHole = hole;
    
    // sow the beans!
    *temp = 0;      // pick up the beans in the current hole
    while (distributableBeans > 0)
    {
        // relocate the pointer to its new location
        if (temp == &m_south[m_nHolesIncludingPot-1]) {
            temp = m_south;
            endHole = 0;
        }
        else if (temp == m_south) {
            temp = &m_north[m_nHolesIncludingPot-1];
            endHole = m_nHolesIncludingPot-1;
            endSide = NORTH;
        }
        else if (temp == m_north) {
            temp = m_south+1;
            endSide = SOUTH;
            endHole = 1;
        }
        else {
            if (endSide == SOUTH)
            {
                temp++;
                endHole++;
            }
            else if (endSide == NORTH)
            {
                temp--;
                endHole--;
            }
        }
        
        // skip the pot if its the other player's side
        if (s == SOUTH && temp == m_north) {
            temp = m_south+1;
            endSide = SOUTH;
            endHole = 1;
        }
        else if (s == NORTH && temp == m_south) {
            temp = &m_north[m_nHolesIncludingPot-1];
            endSide = NORTH;
            endHole = m_nHolesIncludingPot-1;
        }
        
        // distribute a bean and update the number of available beans
        (*temp)++;
        distributableBeans--;
    }
    
    // beans have been successfully sown!
    return true;
}


// If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    // check if the hole is invalid or a pot
    if (hole < 1 || hole > m_nHolesIncludingPot-1)
        return false;
    
    // take the beans out of the pot
    int transferredBeans = -1;
    if (s == SOUTH) {
        transferredBeans = m_south[hole];
        m_south[hole] = 0;
    }
    else if (s == NORTH) {
        transferredBeans = m_north[hole];
        m_north[hole] = 0;
    }
    
    // put the beans in the correct pot
    if (potOwner == NORTH)
    {
        m_north[0] += transferredBeans;
    }
    else if (potOwner == SOUTH)
    {
        m_south[0] += transferredBeans;
    }
    
    return true;
}

// If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
    // check if the hole and beans are valid
    if (hole < 0 || hole > m_nHolesIncludingPot-1 || beans < 0)
        return false;
    
    if (s == SOUTH)
        m_south[hole] = beans;
    else if (s == NORTH)
        m_north[hole] = beans;
    
    return true;
}

// copy constructor
Board::Board(const Board& other)
: m_nHolesIncludingPot(other.m_nHolesIncludingPot)
{
    m_north = new int[m_nHolesIncludingPot];
    m_south = new int[m_nHolesIncludingPot];
    
    // copy over the values
    for (int i = 0; i < m_nHolesIncludingPot; i++)
    {
        m_north[i] = other.m_north[i];
        m_south[i] = other.m_south[i];
    }
}

// Destruct the board
Board::~Board()
{
    delete [] m_north;
    delete [] m_south;
}
