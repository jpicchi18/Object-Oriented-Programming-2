//
//  Sequence.cpp
//  HW 1: Q 1-3
//
//  Created by Joseph Picchi on 4/11/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "newSequence.h"

#include <iostream>

Sequence::Sequence(int size)
: m_size(0), m_maxSize(size)
{
    if (size < 0)
    {
        std::cout << "size of the sequence cannot be negative" << std::endl;
        exit(1);
    }
    m_sequence = new ItemType[size];
}


bool Sequence::empty() const
{
    bool result = false;
    
    //return true if the size is 0, false otherwise
    if (m_size == 0)
    {
        result = true;
    }
    
    return result;
}

int Sequence::size() const
{
    return m_size;
}



int Sequence::insert(int pos, const ItemType& value)
{
    int returnVal = -1;
    
    //if value can be inserted, insert it at pos and return pos
    if (pos >= 0 && pos <= m_size && m_size < m_maxSize)
    {
        for (int i = m_size; i > pos; i--)
        {
            m_sequence[i] = m_sequence[i-1];
        }
        
        m_sequence[pos] = value;
        m_size++;
        
        returnVal = pos;
    }
    //otherwise, don't change anything and return -1
    return returnVal;
}




int Sequence::insert(const ItemType& value)
{
    int p = m_size;
    
    //make sure there is space for a new item
    if (m_size >= m_maxSize)
    {
        p = -1;
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            //find the first item such that value <= item
            if (value <= m_sequence[i])
            {
                //set p = that item's index
                p = i;
                break;
            }
        }
        
        //insert value into the sequence and push everything else back:
        this->insert(p, value);
    }
    
    return p;
}

bool Sequence::erase(int pos)
{
    bool result = false;
    
    //if pos is valid, shift each item after pos down 1
    if (pos >= 0 && pos < m_size)
    {
        for (int i = pos; i < m_size-1; i++)
        {
            m_sequence[i] = m_sequence[i+1];
            
            result = true;
        }
        
        //update the m_size if things have been changed
        m_size--;
    }
    
    return result;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    
    //check for a match and erase it if you find one
    for (int i = 0; i < m_size; i++)
    {
        if (value == m_sequence[i])
        {
            this->erase(i);
            count++;
            i--;
        }
    }
    
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    bool result = false;
    
    //copy the item at pos into value if you can
    if (pos >= 0 && pos < m_size)
    {
        value = m_sequence[pos];
        result = true;
    }
    
    return result;
}



bool Sequence::set(int pos, const ItemType& value)
{
    bool result = false;
    
    //if pos is valid, set the item at pos equal to value
    if (pos >= 0 && pos < m_size)
    {
        m_sequence[pos] = value;
        result = true;
    }
    
    return result;
}



int Sequence::find(const ItemType& value) const
{
    //default for p is -1
    int p = -1;
    
    //set p to the smallest index i at which the item at i equals "value"
    for (int i = 0; i < m_size; i++)
    {
        if (m_sequence[i] == value)
        {
            p = i;
            break;
        }
    }
    
    return p;
}



void Sequence::swap(Sequence& other)
{
    // deterime the larger of the two sequences
    // by default, choose "this"
    ItemType* tempa = m_sequence;
    m_sequence = other.m_sequence;
    other.m_sequence = tempa;
    
    //swap the sizes
    int temp  = m_size;
    m_size = other.m_size;
    other.m_size = temp;
    
    //swap the max sizes
    int newMax = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = newMax;
}



void Sequence::dump() const
{
    std::cerr << std::endl << std::endl << "items in the sequence are: ";
    for (int i = 0; i < m_size; i++)
    {
        if (i != 0)
        {
            std::cerr << ", ";
        }
        std::cerr << m_sequence[i];
    }
    
    std::cerr << std::endl;
    
    std::cerr << "The size is " << m_size << std::endl << std::endl;
}


Sequence::~Sequence()
{
    delete [] m_sequence;
}

Sequence::Sequence(const Sequence& other)
{
    m_size = other.m_size;
    m_maxSize = other.m_maxSize;
    
    // make a separate array for the new object
    m_sequence = new ItemType[m_maxSize];
    for (int i = 0; i < m_size; i++)
    {
        m_sequence[i] = other.m_sequence[i];
    }
}


Sequence& Sequence::operator = (const Sequence& other)
{
    Sequence temp(other);
    swap(temp);
    
    return *this;
}
