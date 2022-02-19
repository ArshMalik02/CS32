#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor base class implementation
Actor::Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus)
: GraphObject(ID, x, y, startDir, depth, size), m_world(p), health(healthStatus), hit(false)
{
}

bool Actor::canBlock()
{
    return false;
}

void Actor::bonk(){return;}

int Actor::getHealth(){return health;}
StudentWorld* Actor::getPtrToWorld(){return m_world;}

// Block implementations
Block::Block(StudentWorld* s, int x, int y)
: Actor(s, x, y, IID_BLOCK, 0, 2, 1, 0)
{}

bool Block::canBlock()
{
    return true;
}

void Block::bonk()
{
    StudentWorld* p = getPtrToWorld();
    p->playSound(SOUND_PLAYER_BONK);
}

void Block::doSomething(){};


// Peach implementations
Peach::Peach(StudentWorld* s, int x, int y)
: Actor(s, x, y, IID_PEACH, 0, 0, 1, 1)
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
        Actor* ptr = nullptr;
        switch(key)
        {
            case KEY_PRESS_LEFT:
            {
                setDirection(180);
                if (ptrToWorld->isBlockingObject(curX-8, curY, ptr))
                {
                    ptr->bonk();
                    break;
                }
                moveTo(curX-4, curY);
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(0);
                if (ptrToWorld->isBlockingObject(curX+8, curY, ptr))
                {
                    ptr->bonk();
                    break;
                }
                moveTo(curX+4, curY);
                break;
            }
            default:
                break;
        }
    }
}

