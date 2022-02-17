
#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    Level lev(assetPath());
    string level_file = "level01.txt";
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
        cerr << "Could not find level01.txt data file" << endl;
    else if (result == Level::load_fail_bad_format)
        cerr << "level01.txt is improperly formatted" << endl;
    else if (result == Level::load_success)
    {
        cerr << "Successfully loaded level" << endl;
        Level::GridEntry ge;
        for (int i = 0; i!=32; i++)
        {
            for (int j = 0; j!=32; j++)
            {
                ge = lev.getContentsOf(i, j); // x=5, y=10
                switch (ge)
                {
                    case Level::empty:
                        cout << "Location 5,10 is empty" << endl;
                        break;
                    case Level::koopa:
                        cout << "Location 5,10 starts with a koopa" << endl;
                        break;
                    case Level::goomba:
                        cout << "Location 5,10 starts with a goomba" << endl;
                        break;
                    case Level::peach:
                        cout << "Location 5,10 is where Peach starts" << endl;
                        break;
                    case Level::flag:
                        cout << "Location 5,10 is where a flag is" << endl;
                        break;
                    case Level::block:
                        objects.push_back(new Block(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT));
                        cout << "Location 5,10 holds a regular block" << endl;
                        break;
                    case Level::star_goodie_block:
                        cout << "Location 5,10 has a star goodie block" << endl;
                        break;
                        // etc…
                }
            }
            
        }
    }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    list<Actor*>::iterator it;
    it = objects.begin();
    while (it!=objects.end())
        delete *it;
}
