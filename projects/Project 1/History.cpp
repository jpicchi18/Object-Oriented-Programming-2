
//
//  HIstory.cpp
//  Project 1
//
//  Created by Joseph Picchi on 4/4/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "History.h"
#include "Arena.h"
#include "globals.h"

History::History(int nRows, int nCols) : m_row(nRows), m_col(nCols)
{
    m_arena = new Arena(nRows, nCols);
    
    //initialize the array values to 0 for both member arrays
    for (int i = 1; i <= MAXROWS; i++)
    {
        m_rowPositions[i] = 0;
    }
    for (int i = 1; i <= MAXCOLS; i++)
    {
        m_colPositions[i] = 0;
    }
}

bool History::record(int r, int c)
{
    if ((r >= 1 && r <= m_row) && (c >= 1 && c <= m_col))
    {
        //returns false if point is out of bounds
        return false;
    }
    //otherwise...
    //record the row and column of the player's position
    for (int i = 1; i <= MAXROWS; i++)
    {
        if (i == r)
        {
            m_rowPositions[i]++;
        }
    }
    for (int i = 1; i <= MAXCOLS; i++)
    {
        if (i == c)
        {
            m_colPositions[i]++;
        }
    }
    
    return true;
}
