#include <stack>
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
        "X.....sXXX",
        "X.XX.X...X",
        "X.X..X.X.X",
        "X.X.XXXX.X",
        "X.X...X..X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,6, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    while (!coordStack.empty())
    {
        Coord currCoord = coordStack.top();
        coordStack.pop();
        
        if (currCoord.r() == er && currCoord.c() == ec)
        {
            return true;
        }
        
        // West
        if (maze[currCoord.r()][currCoord.c()-1] != 'X' && maze[currCoord.r()][currCoord.c()-1] != '#')
        {
            maze[currCoord.r()][currCoord.c()-1] = '#';
            coordStack.push(Coord(currCoord.r(), currCoord.c()-1));
        }
        
        // South
        if (maze[currCoord.r()+1][currCoord.c()] != 'X' && maze[currCoord.r()+1][currCoord.c()] != '#')
        {
            maze[currCoord.r()+1][currCoord.c()] = '#';
            coordStack.push(Coord(currCoord.r()+1, currCoord.c()));
        }
        // East
        if (maze[currCoord.r()][currCoord.c()+1] != 'X' && maze[currCoord.r()][currCoord.c()+1] != '#')
        {
            maze[currCoord.r()][currCoord.c()+1] = '#';
            coordStack.push(Coord(currCoord.r(), currCoord.c()+1));
        }
        
        // North
        if (maze[currCoord.r()-1][currCoord.c()] != 'X' && maze[currCoord.r()-1][currCoord.c()] != '#')
        {
            maze[currCoord.r()-1][currCoord.c()] = '#';
            coordStack.push(Coord(currCoord.r()-1, currCoord.c()));
        }
        
    }
    return false;
}
