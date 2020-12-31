//
//  main.cpp
//  HW 2 Q 3
//
//  Created by Joseph Picchi on 4/27/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <queue>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
// includes:
//A 2-dimensional 10x10 character array of Xs and dots that represents the maze. Each 'X' represents a wall, and each '.' represents a walkway.
//The starting coordinates in the maze: sr, sc; the row number and column number range from 0 to 9.
//The ending coordinates in the maze: er, ec; the row number and column number range from 0 to 9.

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    // Push the starting coordinate (sr,sc) onto the coordinate queue and
    // update maze[sr][sc] to indicate that the algorithm has encountered
    // it (i.e., set maze[sr][sc] to have a value other than '.').
    queue<Coord> myQueue;
    myQueue.push(Coord(sr,sc));
    
    maze[sr][sc] = 'A';
    
    while (!myQueue.empty())    // While the queue is not empty
    {
        // Pop the top coordinate off the queue. This gives you the current
        // (r,c) location that your algorithm is exploring.
        Coord location = myQueue.front();
        myQueue.pop();
        
        // If the current (r,c) coordinate is equal to the ending coordinate,
        // then we've solved the maze so return true!
        int r = location.r();
        int c = location.c();
        
        if (r == er && c == ec)
            return true;
        
        // Check each place you can move from the current cell as follows:
        
        // If you can move SOUTH and haven't encountered that cell yet,
        if (maze[r + 1][c] == '.')
        {
            // then push the coordinate (r+1,c) onto the queue
            myQueue.push(Coord(r+1, c));
            // and update maze[r+1][c] to indicate the algorithm has encountered it.
            maze[r + 1][c] = 'A';
        }
        
        // WEST
        if (maze[r][c-1] == '.')
        {
            myQueue.push(Coord(r, c-1));
            maze[r][c-1] = 'A';
        }
        
        // NORTH
        if (maze[r-1][c] == '.')
        {
            myQueue.push(Coord(r-1, c));
            maze[r-1][c] = 'A';
        }
        
        // EAST
        if (maze[r][c+1] == '.')
        {
            myQueue.push(Coord(r, c+1));
            maze[r][c+1] = 'A';
        }
    }
    
    return false;
}
