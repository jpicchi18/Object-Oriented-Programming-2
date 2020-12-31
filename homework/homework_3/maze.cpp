//
//  main.cpp
//  HW3 Q3
//
//  Created by Joseph Picchi on 5/9/19.
//  Copyright © 2019 Joseph Picchi. All rights reserved.
//


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
    if (sr < 0  ||  sr > 9  ||  sc < 0  || sc > 9  ||
        er < 0  ||  er > 9  ||  ec < 0  || ec > 9  ||
        maze[sr][sc] != '.'  ||  maze[er][ec] != '.')
        return false;
//    If the start location is equal to the ending location, then we've
//    solved the maze, so return true.
    if (sr == er && sc == ec)
        return true;
    
//    Mark the start location as visted.
    maze[sr][sc] = 'A';
    
//    For each of the four directions
    if (maze[sr-1][sc] == '.')      // North
    {
        if (pathExists(maze, sr-1, sc, er, ec))
            return true;
    }
    
    if (maze[sr+1][sc] == '.')      // South
    {
        if (pathExists(maze, sr+1, sc, er, ec))
            return true;
    }
    
    if (maze[sr][sc+1] == '.')      // East
    {
        if (pathExists(maze, sr, sc+1, er, ec))
            return true;
    }
    
    if (maze[sr][sc-1] == '.')      // West
    {
        if (pathExists(maze, sr, sc-1, er, ec))
            return true;
    }
    
    return false;

}
