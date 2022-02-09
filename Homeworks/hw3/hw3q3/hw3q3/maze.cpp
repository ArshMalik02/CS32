
#include <iostream>
using namespace std;

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



bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);


int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X.X..X...X",
        "X....XXX.X",
        "X.XXXX.X.X",
        "X......XXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 1,1, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc]  = '#';
    // West
    if (maze[sr][sc-1] == '.' && pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
        return true;
    //South
    if (maze[sr+1][sc] == '.' && pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
        return true;
    //East
    if (maze[sr][sc+1] == '.' && pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
        return true;
    //North
    if (maze[sr-1][sc] == '.' && pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
        return true;
    return false;
}
