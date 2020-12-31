//
//  Game.hpp
//  Project 1
//
//  Created by Joseph Picchi on 4/4/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
};

#endif /* Game_hpp */
