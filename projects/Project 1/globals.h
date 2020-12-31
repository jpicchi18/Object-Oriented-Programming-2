//
//  Globals.h
//  Project 1
//
//  Created by Joseph Picchi on 4/4/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#ifndef Globals_h
#define Globals_h

const int MAXROWS = 20;              // max number of rows in the arena
const int MAXCOLS = 30;              // max number of columns in the arena
const int MAXZOMBIES = 150;          // max number of zombies allowed
const int INITIAL_ZOMBIE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

int randInt(int min, int max);
void clearScreen();

#endif /* Globals_h */
