//
//  Sequence.hpp
//  CS 32 Project 2
//
//  Created by Joseph Picchi on 4/19/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Sequence_hpp
#define Sequence_hpp

#include <string>

using ItemType = std::string;

class Sequence
{
public:
    Sequence();          // Create an empty sequence (i.e., one with no items)
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    int insert(int pos, const ItemType& value);
    // Insert value into the sequence so that it becomes the item at
    // position pos.  The original item at position pos and those that
    // follow it end up at positions one higher than they were at before.
    // Return pos if 0 <= pos <= size() and the value could be
    // inserted.  (It might not be, if the sequence has a fixed capacity,
    // e.g., because it's implemented using a fixed-size array.)  Otherwise,
    // leave the sequence unchanged and return -1.  Notice that
    // if pos is equal to size(), the value is inserted at the end.
    
    int insert(const ItemType& value);      // NEED TO FIX THIS!
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence; if no such item exists (i.e.,
    // value > all items in the sequence), let p be size().  Insert
    // value into the sequence so that it becomes the item at position
    // p.  The original item at position p and those that follow it end
    // up at positions one higher than before.  Return p.
    
    bool erase(int pos);
    // If 0 <= pos < size(), remove the item at position pos from
    // the sequence (so that all items that followed that item end up at
    // positions one lower than they were at before), and return true.
    // Otherwise, leave the sequence unchanged and return false.
    
    int remove(const ItemType& value);
    // Erase all items from the sequence that == value.  Return the
    // number of items removed (which will be 0 if no item == value).
    
    bool get(int pos, ItemType& value) const;
    // If 0 <= pos < size(), copy into value the item at position pos
    // of the sequence and return true.  Otherwise, leave value unchanged
    // and return false.
    
    bool set(int pos, const ItemType& value);
    // If 0 <= pos < size(), replace the item at position pos in the
    // sequence with value and return true.  Otherwise, leave the sequence
    // unchanged and return false.
    
    int find(const ItemType& value) const;
    // Let p be the smallest integer such that value == the item at
    // position p in the sequence; if no such item exists, let p be -1.
    // Return p.
    
    void swap(Sequence& other);
    // Exchange the contents of this sequence with the other one.
    
    ~Sequence();
    // When a Sequence is destroyed, the nodes in the linked list must be deallocated.
    
    Sequence(const Sequence& other);
    // When a brand new Sequence is created as a copy of an existing Sequence,
    // enough new nodes must be allocated to hold a duplicate of the original list.
    
    Sequence& operator = (const Sequence& other);
    // When an existing Sequence (the left-hand side) is assigned the value of another Sequence
    // (the right-hand side), the result must be that the left-hand side object is a duplicate of
    // the right-hand side object, with no memory leak of list nodes (i.e. no list node
    // from the old value of the left-hand side should be still allocated yet inaccessible).
    
    void dump() const;
    
private:
    struct Node
    {
        ItemType m_data;
        Node* m_next;
        Node* m_prev;
    };
    
    Node* head;
    int m_size;
        // At any time, the elements of m_data indexed from 0 to m_size-1
        // are in use.
    
    void uncheckedInsert(int pos, const ItemType& value);
        // Insert value at position pos.  Assume pos is valid.
    
    void ceateAndFillNodes(const Sequence& other);
        // creates m_size number of new nodes, links them together, and copies their data
        // values from other
};


int subsequence(const Sequence& seq1, const Sequence& seq2);


void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);



#endif /* Sequence_hpp */
