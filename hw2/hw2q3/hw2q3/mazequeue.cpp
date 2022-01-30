#include <queue>
#include <iostream>
#include <string>
using namespace std;

void dump(string m[], int r, int c)
{
    for (int i = 0; i < r ; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cerr<< m[i][j];
        }
        cerr << endl;
    }
}

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

//Push the starting coordinate (sr,sc) onto the coordinate stack and
//            update maze[sr][sc] to indicate that the algorithm has encountered
//            it (i.e., set maze[sr][sc] to have a value other than '.').
//        While the stack is not empty,
//        {   Pop the top coordinate off the stack. This gives you the current
//                (r,c) location that your algorithm is exploring.
//            If the current (r,c) coordinate is equal to the ending coordinate,
//                then we've solved the maze so return true!
//            Check each place you can move from the current cell as follows:
//                If you can move WEST and haven't encountered that cell yet,
//                    then push the coordinate (r,c-1) onto the stack and update
//                    maze[r][c-1] to indicate the algorithm has encountered it.
//                If you can move SOUTH and haven't encountered that cell yet,
//                    then push the coordinate (r+1,c) onto the stack and update
//                    maze[r+1][c] to indicate the algorithm has encountered it.
//                If you can move EAST and haven't encountered that cell yet,
//                    then push the coordinate (r,c+1) onto the stack and update
//                    maze[r][c+1] to indicate the algorithm has encountered it.
//                If you can move NORTH and haven't encountered that cell yet,
//                    then push the coordinate (r-1,c) onto the stack and update
//                    maze[r-1][c] to indicate the algorithm has encountered it.
//        }
//        There was no solution, so return false





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
    queue<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = '#';
    while (!coordStack.empty())
    {
        Coord currCoord = coordStack.front();
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

