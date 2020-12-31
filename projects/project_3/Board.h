//
//  Board.hpp
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include "Side.h"
#include <vector>

class Board
{
public:
    Board(int nHoles, int nInitialBeansPerHole);
    int holes() const;
    int beans(Side s, int hole) const;
    int beansInPlay(Side s) const;
    int totalBeans() const;
    bool sow(Side s, int hole, Side& endSide, int& endHole);
    bool moveToPot(Side s, int hole, Side potOwner);
    bool setBeans(Side s, int hole, int beans);
    Board(const Board& other);
    ~Board();
    
private:
    int*    m_north;
    int*    m_south;
    int     m_nHolesIncludingPot;
};

#endif /* Board_hpp */
