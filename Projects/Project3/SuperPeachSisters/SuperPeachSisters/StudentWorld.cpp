
#include "StudentWorld.h"
#include "Actor.h"
#include "GameConstants.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath), gameStatus(false), nextLevel(false)
{
}

void StudentWorld::changeLevelStatus(bool x)
{
    gameStatus = x;
}

void StudentWorld::addActor(Actor* p)
{
    objects.push_back(p);
}

int StudentWorld::init()
{
    Level lev(assetPath());
    int k = getLevel();
    ostringstream oss;
    oss.fill('0');
    oss << "level" << setw(2) << k << ".txt";
    cerr << oss.str() << endl;
    string level_file = oss.str();
    Level::LoadResult result = lev.loadLevel(level_file);
    if (result == Level::load_fail_file_not_found)
    {
        cerr << "Could not find level01.txt data file" << endl;
        gameStatus = false;
        return GWSTATUS_LEVEL_ERROR;
    }
    
    else if (result == Level::load_fail_bad_format)
    {
        cerr << "level01.txt is improperly formatted" << endl;
        gameStatus = false;
        return GWSTATUS_LEVEL_ERROR;
    }
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
//                        cout << "Location 5,10 is empty" << endl;
                        break;
                    case Level::koopa:
                        cout << "Location "<<i<<","<<j<<" starts with a koopa" << endl;
                        objects.push_front(new Koopa(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT));
                        break;
                    case Level::goomba:
                        objects.push_front(new Goomba(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT));
                        cout << "Location "<<i<<","<<j<<" starts with a goomba" << endl;
                        break;
                    case Level::peach:
                        cout << "Location "<<i<<","<<j<<" is where Peach starts" << endl;
                        m_peach = new Peach(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT);
                        break;
                    case Level::block:
                        objects.push_front(new Block(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 0));
                        cout << "Location "<<i<<","<<j<<" holds a regular block" << endl;
                        break;
                    case Level::star_goodie_block:
                        cout << "Location "<<i<<","<<j<<" has a star goodie block" << endl;
                        objects.push_front(new Block(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 3));
                        break;
                    case Level::flower_goodie_block:
                        cout << "Location "<<i<<","<<j<<" has a flower goodie block" << endl;
                        objects.push_front(new Block(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 1));
                        break;
                    case Level::mushroom_goodie_block:
                        cout << "Location "<<i<<","<<j<<" has a mushroom goodie block" << endl;
                        objects.push_front(new Block(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT, 2));
                        break;
                    case  Level::pipe:
                        objects.push_front(new Pipe(this, i*SPRITE_WIDTH, j*SPRITE_HEIGHT));
                        break;
                    case Level::flag:
                        objects.push_front(new Flag(this, 10*SPRITE_WIDTH, 2*SPRITE_HEIGHT));
                        cout << "Location "<<i<<","<<j<<" is where a flag is" << endl;
                        break;
                }
            }
            
        }
    }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    if (m_peach->getHealth()!=0)
        m_peach->doSomething();
    list<Actor*>::iterator it;
    it = objects.begin();
    while (it!=objects.end())
    {
        if ((*it)->getHealth()!=0)
        {
            (*it)->doSomething();
            if ((m_peach->getHealth() == 0 && gameStatus==false)|| getLives()==0)
            {
                playSound(SOUND_PLAYER_DIE);
                return GWSTATUS_PLAYER_DIED;
            }
            if (gameStatus)
            {
                playSound(SOUND_FINISHED_LEVEL);
                return GWSTATUS_FINISHED_LEVEL;
            }
        }
        it++;
    }
    
    // Remove dead game objects
    if (getLives()==0)
        delete m_peach;
    list<Actor*>::iterator t;
    t = objects.begin();
    for ( ; t != objects.end(); )
    {  // notice: no it++
        if ((*t)->getHealth() == 0)
        {
            delete *t;
            t = objects.erase(t);
        }
        else
            t++;
    }
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    // deleting peach
    delete m_peach;
    // deleting rest of the actors
    list<Actor*>::iterator it;
    it = objects.begin();
    while (it!=objects.end())
    {
        delete *it;
        objects.erase(it);
        it++;
    }
    changeLevelStatus(false);
}

Peach* StudentWorld::getPeach()
{
    return m_peach;
}

bool StudentWorld::isBlockingObject(int x, int y, Actor* &p)
{
    // iterating through all the objects
    list<Actor*>::iterator it;
    it = objects.begin();
    while (it!=objects.end())
    {
        if ((*it)->canBlock())
        {
            int coordX = (*it)->getX();
            int coordY = (*it)->getY();
            if (((coordX<=x) && (x<=coordX+SPRITE_WIDTH-1)) || ((coordX>=x)&&(coordX<=x+SPRITE_WIDTH-1)))
            {
                if (((coordY<=y) && (y<=coordY+SPRITE_HEIGHT-1)) || ((coordY>=y)&&(coordY<=y+SPRITE_HEIGHT-1)))
                {
                    p = *it;
                    return true;
                }
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::koopagoombaoverlap(int x, int y, Actor* &p)
{
    // iterating through all the objects
    list<Actor*>::iterator it;
    it = objects.begin();
    while (it!=objects.end())
    {
        if (!(*it)->canBlock() && (*it)->isDamageable())
        {
            int coordX = (*it)->getX();
            int coordY = (*it)->getY();
            if (((coordX<=x) && (x<=coordX+SPRITE_WIDTH-1)) || ((coordX>=x)&&(coordX<=x+SPRITE_WIDTH-1)))
            {
                if (((coordY<=y) && (y<=coordY+SPRITE_HEIGHT-1)) || ((coordY>=y)&&(coordY<=y+SPRITE_HEIGHT-1)))
                {
                    p = *it;
                    return true;
                }
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::peachOverlap(int x, int y, Actor* &p)
{
    int coordX = (m_peach)->getX();
    int coordY = (m_peach)->getY();
    if (((coordX<=x) && (x<=coordX+SPRITE_WIDTH-1)) || ((coordX>=x)&&(coordX<=x+SPRITE_WIDTH-1)))
    {
        if (((coordY<=y) && (y<=coordY+SPRITE_HEIGHT-1)) || ((coordY>=y)&&(coordY<=y+SPRITE_HEIGHT-1)))
        {
            p = m_peach;
            return true;
        }
    }
    return false;
}

StudentWorld::~StudentWorld()
{
    if (gameStatus)
        cleanUp();
}
