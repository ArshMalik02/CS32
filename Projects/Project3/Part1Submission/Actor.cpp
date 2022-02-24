#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor base class implementation
Actor::Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus)
: GraphObject(ID, x, y, startDir, depth, size), m_world(p), health(healthStatus), hit(false)
{
}

Actor::~Actor(){}

bool Actor::canBlock()
{
    return false;
}

void Actor::bonk(){return;}

int Actor::getHealth(){return health;}
StudentWorld* Actor::getPtrToWorld(){return m_world;}

// Object encapsulates both block and pipe because they are very similar

Object::Object(StudentWorld* s, int x, int y, int idnum)
 : Actor(s, x, y, idnum, 0, 2, 1, 1)
{}

bool Object::cannotBeDamaged(){return true;}

bool Object::canBlock(){return true;}

// Block implementations
Block::Block(StudentWorld* s, int x, int y)
: Object(s, x, y, IID_BLOCK)
{}

void Block::bonk()
{
    StudentWorld* p = getPtrToWorld();
    p->playSound(SOUND_PLAYER_BONK);
}

void Block::doSomething(){}

// Pipe Implementations

Pipe::Pipe(StudentWorld* s, int x, int y)
: Object(s, x, y, IID_PIPE)
{}
void Pipe::bonk(){}
void Pipe::doSomething(){}


// Peach implementations
Peach::Peach(StudentWorld* s, int x, int y)
: Actor(s, x, y, IID_PEACH, 0, 0, 1, 1), remainingJumpDistance(0), jumpInitiated(false)
{}



void Peach::doSomething()
{
    if (getHealth()==0)
        return;
    int key;
    StudentWorld* ptrToWorld = getPtrToWorld();
    if (ptrToWorld->getKey(key))
    {
        int curX = getX();
        int curY = getY();
        Actor* ptrToBonkedActor = nullptr;
        switch(key)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(180);
                if (ptrToWorld->isBlockingObject(curX-4, curY, ptrToBonkedActor))
                {
                    ptrToBonkedActor->bonk();
                    break;
                }
                moveTo(curX-4, curY);
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                if (ptrToWorld->isBlockingObject(curX+4, curY, ptrToBonkedActor))
                {
                    ptrToBonkedActor->bonk();
                    break;
                }
                moveTo(curX+4, curY);
                break;
            }
            case KEY_PRESS_UP:
            {
                if (ptrToWorld->isBlockingObject(curX, curY+4, ptrToBonkedActor))
                {
                    ptrToBonkedActor->bonk();
                    break;
                }
                moveTo(curX, curY+4);
                break;
            }
            case KEY_PRESS_DOWN:
            {
                moveTo(curX, curY-4);
                break;
            }
            default:
                break;
        }
    }
}

