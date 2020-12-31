//
//  Zombies.hpp
//  Project 1
//
//  Created by Joseph Picchi on 4/4/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Zombies_hpp
#define Zombies_hpp

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Zombie declaration.

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Zombies_hpp */
