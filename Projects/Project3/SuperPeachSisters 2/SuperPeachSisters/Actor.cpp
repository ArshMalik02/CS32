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
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedActor = nullptr;
    
    // Jump implementation
    
    if (jumpInitiated==true && remainingJumpDistance>0)
    {
        int targetX = curX;
        int targetY = curY+4;
        if (ptrToWorld->isBlockingObject(targetX, targetY, ptrToBonkedActor))
        {
            ptrToBonkedActor->bonk();
            jumpInitiated = false;
            remainingJumpDistance = 0;
        }
        else
        {
            moveTo(targetX, targetY);
            remainingJumpDistance--;
        }
    }
    else
    {
        int flag = 0;
        for (int i = 0; i!=4; i++)
        {
            if (ptrToWorld->isBlockingObject(curX, curY-i, ptrToBonkedActor))
            {
                flag=1;
                break;
            }
        }
        if (flag==0)
        {
            moveTo(curX, curY-4);
        }
    }
    if (ptrToWorld->getKey(key))
    {
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
                if (ptrToWorld->isBlockingObject(curX, curY-1, ptrToBonkedActor))
                {
                    jumpInitiated = true;
                    remainingJumpDistance = 8;
                    ptrToWorld->playSound(SOUND_PLAYER_JUMP);
                    break;
                }
                moveTo(curX, curY+4);
                break;
            }
            default:
                break;
        }
    }
}

