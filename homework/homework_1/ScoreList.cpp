//
//  ScoreList.cpp
//  HW 1: Q 1-3
//
//  Created by Joseph Picchi on 4/14/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "ScoreList.h"
#include "Sequence.h"

ScoreList::ScoreList()
{
    
}



bool ScoreList::add(unsigned long score)
{
    bool result = false;
    
    //only return true if the score is valid and there is space
    if (score <= 100 && m_sequence.insert(score) != -1)
    {
        result = true;
    }
    
    return result;
}



bool ScoreList::remove(unsigned long score)
{
    bool result = false;
    
    int a = 0;
    a = m_sequence.find(score);
    
    if (a != -1)
    {
        result = m_sequence.erase(a);
    }
    
    return result;
}



int ScoreList::size() const
{
    return m_sequence.size();
}



unsigned long ScoreList::minimum() const
{
    unsigned long result = NO_SCORE;
    
    // find the minimum value if the list is not empty
    if (!m_sequence.empty())
    {
        unsigned long minimum;
        m_sequence.get(0, minimum);
        
        for (int i = 0; i < m_sequence.size(); i++)
        {
            unsigned long comparedVal;
            m_sequence.get(i, comparedVal);
            
            if (comparedVal < minimum)
            {
                minimum = comparedVal;
            }
        }
        
        result = minimum;
    }
    
    return result;
}



unsigned long ScoreList::maximum() const
{
    unsigned long result = NO_SCORE;
    
    //find the highest score if the list is not empty
    if (!m_sequence.empty())
    {
        unsigned long max;
        m_sequence.get(0, max);
        
        for (int i = 0; i < m_sequence.size(); i++)
        {
            unsigned long comp;
            m_sequence.get(i, comp);
            
            if (comp > max)
            {
                max = comp;
            }
        }
        
        result = max;
    }
    
    return result;
}
