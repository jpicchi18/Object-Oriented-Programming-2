//
//  ScoreList.hpp
//  HW 1: Q 1-3
//
//  Created by Joseph Picchi on 4/14/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef ScoreList_hpp
#define ScoreList_hpp

#include "Sequence.h"
#include <limits>

const unsigned long NO_SCORE = std::numeric_limits<unsigned long>::max();

class ScoreList
{
public:
    ScoreList();       // Create an empty score list.
    
    bool add(unsigned long score);
    // If the score is valid (a value from 0 to 100) and the score list
    // has room for it, add it to the score list and return true.
    // Otherwise, leave the score list unchanged and return false.
    
    bool remove(unsigned long score);
    // Remove one instance of the specified score from the score list.
    // Return true if a score was removed; otherwise false.
    
    int size() const;  // Return the number of scores in the list.
    
    unsigned long minimum() const;
    // Return the lowest score in the score list.  If the list is
    // empty, return NO_SCORE.
    //may include "for" and "while"
    
    unsigned long maximum() const;
    // Return the highest score in the score list.  If the list is
    // empty, return NO_SCORE.
    //may include "for" and "while"
    
private:
    Sequence m_sequence;
};

#endif /* ScoreList_hpp */
