//
//  Side.h
//  Project3
//
//  Created by Joseph Picchi on 5/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Side_h
#define Side_h

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}

// It may contain additional types, constants, and non-member function declarations you find useful to add.


#endif /* Side_h */
