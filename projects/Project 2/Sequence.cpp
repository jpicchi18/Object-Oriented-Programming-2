//
//  Sequence.cpp
//  CS 32 Project 2
//
//  Created by Joseph Picchi on 4/19/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include "Sequence.h"
#include <iostream>

Sequence::Sequence()    // default constructor creates an empty list with a dummy node
: m_size(0)
{
    head = new Node();
    
    // dummy pointer points to itself because the list is empty
    head->m_next = head;
    head->m_prev = head;
}



bool Sequence::empty() const
{
    return (m_size == 0);
}



int Sequence::size() const
{
    return m_size;
}


void Sequence::uncheckedInsert(int pos, const ItemType& value)      // assumes the position is valid
{
    // make a pointer "temp" and point it to the Node before the desired position
    Node* temp = head;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->m_next;
    }
    
    // allocate and fill a new node for the item
    Node* newest = new Node;
    newest->m_data = value;
    
    // alter the new node's next and previous pointers
    newest->m_next = temp->m_next;
    newest->m_prev = temp;
    
    // alter the following node's prev pointer
    newest->m_next->m_prev = newest;
    
    // alter the previous node's next pointer
    temp->m_next = newest;
    
    // increment the size because we added an item
    m_size++;
}



int Sequence::insert(int pos, const ItemType& value)
{
    int result = -1;
    
    // insert value if pos is valid
    if (pos >= 0 && pos <= m_size)
    {
        uncheckedInsert(pos, value);
        result = pos;
    }
    
    return result;
}


int Sequence::insert(const ItemType& value)
{
    int p = m_size;
    
    // find the first index where value <= to the item at that index
    // set p to that index
    int index = 0;
    
    for (Node* temp = head->m_next; temp != head; temp = temp->m_next)
    {
        if (value <= temp->m_data)
        {
            p = index;
            break;
        }
        
        index++;
    }
    
    // insert value at p
    uncheckedInsert(p, value);
    
    return p;
}

bool Sequence::erase(int pos)
{
    bool result = false;
    
    // make sure the position is valid
    if (pos >= 0 && pos < m_size)
    {
        // create a pointer to the node just before the deletion point
        Node* beforePos = head;
        for (int i = 0; i < pos; i++)
        {
            beforePos = beforePos->m_next;
        }
        
        //create a pointer to the node at the deletion point
        Node* killMe = beforePos->m_next;
        
        // alter the following Node's prev pointer
        killMe->m_next->m_prev = beforePos;
        
        // alter the previous Node's next pointer
        beforePos->m_next = killMe->m_next;
        
        // deallocate the Node at the deletion point
        delete killMe;
        
        // decrement the size because we removed an item
        m_size--;
        result = true;
    }
    
    
    return result;
}



int Sequence::remove(const ItemType& value)
{
    int count = 0;
    int pos = 0;
    
    // loop through every element of the list with a temp pointer
    Node* temp = head->m_next;
    while (temp != head)
    {
        // if a match is found, delete that node and increment the count;
        // otherwise, move on
        if (temp->m_data == value)
        {
            temp = temp->m_next;
            erase(pos);
            count++;
        }
        else
        {
            temp = temp->m_next;
            pos++;
        }
    }
    
    return count;
}



bool Sequence::get(int pos, ItemType& value) const
{
    bool result = false;
    
    // make sure the position is valid
    if (pos >= 0 && pos < m_size)
    {
        // create a pointer to the desired item and set value to it
        Node* temp = head->m_next;
        for (int i = 0; i < pos; i++)
        {
            temp = temp->m_next;
        }
        
        value = temp->m_data;
        
        result = true;
    }
    
    return result;
}



bool Sequence::set(int pos, const ItemType& value)
{
    // if position is invalid, return false
    if (pos < 0 || pos >= m_size)
        return false;
    
    // create a pointer to the desired item and set it to value
    Node* temp = head->m_next;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->m_next;
    }
    
    temp->m_data = value;
    
    return true;
}



int Sequence::find(const ItemType& value) const
{
    int p = -1;
    
    // loop through the list until you find an index such that item == value
    // set p to that index
    int index = 0;
    for (Node* temp = head->m_next; temp != head; temp = temp->m_next)
    {
        if (temp->m_data == value)
        {
            p = index;
            break;
        }
        
        index++;
    }
    
    return p;
}


void Sequence::swap(Sequence& other)
{
    // swap the positions the heads point to
    Node* temp = head;
    head = other.head;
    other.head = temp;
    
    // swap the sizes:
    int tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
}



Sequence::~Sequence()
{
    // loop through and delete every node until you reach the dummy node
    Node* temp = head->m_next;
    while (temp != head)
    {
        Node* nextNode = temp->m_next;
        delete temp;
        temp = nextNode;
    }
    
    // delete the dummy node
    delete temp;
}



Sequence::Sequence(const Sequence& other)
: m_size(other.m_size)
{
    
    // create a dummy node for the new sequence, and initialize its pointers
    head = new Node;
    head->m_next = head;
    head->m_prev = head;

    // make the necessary number of nodes, link them, and copy the values over
    ceateAndFillNodes(other);
}
// When a brand new Sequence is created as a copy of an existing Sequence,
// enough new nodes must be allocated to hold a duplicate of the original list.



Sequence& Sequence::operator = (const Sequence& other)
{
    // check for aliasing:
    if (head == other.head)
        return *this;
    
    // create a temporary copy of "other" and swap it with "this"
    Sequence temp(other);
    swap(temp);
    
    return *this;
}
// When an existing Sequence (the left-hand side) is assigned the value of another Sequence
// (the right-hand side), the result must be that the left-hand side object is a duplicate of
// the right-hand side object, with no memory leak of list nodes (i.e. no list node
// from the old value of the left-hand side should be still allocated yet inaccessible).


void Sequence::ceateAndFillNodes(const Sequence& other)
{
    // create the necessary number of nodes and link them:
    Node* previous = head;
    Node* current = nullptr;
    for (int i = 0; i < m_size; i++)
    {
        current = new Node;
        current->m_next = head;
        current->m_prev = previous;
        head->m_prev = current;
        previous->m_next = current;
        
        previous = current;
    }
    
    // copy the data from other to this
    Node* tempThis = head->m_next;
    Node* tempOther = other.head->m_next;
    
    while (tempThis != head && tempOther != other.head)
    {
        tempThis->m_data = tempOther->m_data;
        tempThis = tempThis->m_next;
        tempOther = tempOther->m_next;
    }
}




void Sequence::dump() const
{
    // print the size
    std::cerr << "SEQUENCE PROPERTIES:" << std::endl;
    std::cerr << "Size: " << m_size << std::endl;
    std::cerr << "Elements: ";
    
    Node* temp = head->m_next;
    
    if (head->m_prev == head)
    {
        std::cerr << "empty" << std::endl;
    }
    else
    {
        for (int i = 0; i < m_size; i++)
        {
            std::cerr << temp->m_data << ", ";
            temp = temp->m_next;
        }
    }
    
    std::cerr << std::endl;
}




// NON-MEMBER FUNCTIONS:

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    // make sure seq1 and seq2 are valid
    if (seq1.empty() || seq2.empty())
        return -1;
    
    // get the first value of seq2
    ItemType initial2;
    seq2.get(0, initial2);
    
    // index where seq2 first appears in seq1:
    int matchIndex = -1;
    
    // loop through seq1 to find a match with the first item of seq2
    ItemType temp1;
    for (int i = 0; i < seq1.size(); i++)
    {
        seq1.get(i, temp1);
        
        // if a match is found, record the index of the match
        if (temp1 == initial2)
        {
            matchIndex = i;
            
            // loop through seq 2 to see if the rest of its items appear in seq1
            ItemType temp2;
            for (int k = 0; k < seq2.size(); k++)
            {
                if (k > 0)
                    i++;
                
                // quit looping if an item doesn't match...
                // if everything matches, return the index of the first matching item
                seq2.get(k, temp2);
                seq1.get(i, temp1);
                if (temp1 != temp2)
                    break;
                else if (k == seq2.size()-1)
                    return matchIndex;
            }
        }
    }
    
    return -1;
}


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    // Copy seq1 and seq2 in case of aliasing
    Sequence newSeq1(seq1);
    Sequence newSeq2(seq2);
    
    // remove all elements from result
    int resultSize = result.size();
    for (int i = 0; i < resultSize; i++)
    {
        result.erase(0);
    }
    
    // record the largest size between seq1 and seq2
    int larger = 0;
    if (newSeq1.size() >= newSeq2.size())
        larger = newSeq1.size();
    else
        larger = newSeq2.size();
    
    // add the required items to result
    int resultIndex = 0;
    
    for (int i = 0; i < larger; i++)
    {
        ItemType temp;
        if (i < newSeq1.size())
        {
            newSeq1.get(i, temp);
            result.insert(resultIndex, temp);
            resultIndex++;
        }
        
        if (i < newSeq2.size())
        {
            newSeq2.get(i, temp);
            result.insert(resultIndex, temp);
            resultIndex++;
        }
    }
}

