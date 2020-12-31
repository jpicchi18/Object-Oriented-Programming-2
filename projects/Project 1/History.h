
//
//  HIstory.hpp
//  Project 1
//
//  Created by Joseph Picchi on 4/4/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef HIstory_hpp
#define HIstory_hpp

#include "globals.h"

class Arena;

class History
{
public:
    History(int nRows, int nCols);
    ~History();
    bool record(int r, int c);
    void display() const;
    
private:
    Arena* m_arena;
    int m_row;
    int m_col;
    int m_rowPositions[MAXROWS];
    int m_colPositions[MAXCOLS];
};

#endif /* HIstory_hpp */
