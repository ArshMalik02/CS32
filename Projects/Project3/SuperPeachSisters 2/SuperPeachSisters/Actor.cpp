#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
using namespace std;

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

// Actor base class implementation
Actor::Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus)
: GraphObject(ID, x, y, startDir, depth, size), m_world(p), health(healthStatus), hit(false)
{
}

void Actor::setHealth(int x)
{
    health = x;
}
Actor::~Actor(){}

bool Actor::canBlock()
{
    return false;
}

void Actor::bonk(){return;}

int Actor::getHealth(){return health;}
StudentWorld* Actor::getPtrToWorld(){return m_world;}

// Enemy class encapsulates goomba and koopa

Enemy::Enemy(StudentWorld* s, int x, int y, int idnum, int depth, double size)
: Actor(s, x, y, idnum, randInt(0, 1)*180, depth, size, 1)
{}

bool Enemy::canBlock(){return false;}

Goomba::Goomba(StudentWorld* s, int x, int y)
: Enemy(s, x, y, IID_GOOMBA, 0, 1)
{}

Koopa::Koopa(StudentWorld* s, int x, int y)
: Enemy(s, x, y, IID_KOOPA, 0, 1)
{}

void Enemy::doSomething()
{
    if (getHealth()==0)
        return;
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedActor = nullptr;   // this would be peach
    if (ptrToWorld->enemyOverlap(curX, curY, ptrToBonkedActor))
    {
        cerr << "bonk" << endl;
        ptrToBonkedActor->bonk();
        return;
    }
    if (getDirection()==0)
    {
        if (ptrToWorld->isBlockingObject(curX+1, curY, ptrToBonkedActor))
        {
            setDirection(180);
        }
        else if (!(ptrToWorld->isBlockingObject(curX+4, curY-1, ptrToBonkedActor)))
        {
            setDirection(180);
        }
        else
        {
            int targetX = curX+1;
            int targetY = curY;
            if (ptrToWorld->isBlockingObject(targetX, targetY, ptrToBonkedActor))
                return;
            moveTo(targetX, targetY);
        }
    }
    else if (getDirection()==180)
    {
        if (ptrToWorld->isBlockingObject(curX-1, curY, ptrToBonkedActor))
        {
            setDirection(0);
        }
        else if (!(ptrToWorld->isBlockingObject(curX-4, curY-1, ptrToBonkedActor)))
        {
            setDirection(0);
        }
        else
        {
            int targetX = curX-1;
            int targetY = curY;
            if (ptrToWorld->isBlockingObject(targetX, targetY, ptrToBonkedActor))
                return;
            moveTo(targetX, targetY);
        }
    }
}
// Object encapsulates both block and pipe because they are very similar

Object::Object(StudentWorld* s, int x, int y, int idnum, int d, double size)
 : Actor(s, x, y, idnum, 0, d, size, 1)
{}

bool Object::cannotBeDamaged(){return true;}

bool Object::canBlock(){return true;}

// Flag implementations
Flag::Flag(StudentWorld* s, int x, int y)
 : Object(s, x, y, IID_FLAG, 1, 1)
{}

void Flag::bonk(){}
bool Flag::canBlock(){return false;}
void Flag::doSomething()
{
    if (getHealth()==0)
        return;
    StudentWorld* ptrToWorld = getPtrToWorld();
    Actor* ptrToPeach = ptrToWorld->getPeach();
    int currFlagX = getX();
    int currFlagY = getY();
    int peachX = ptrToPeach->getX();
    int peachY = ptrToPeach->getY();
    if (((currFlagX<=peachX) && (peachX<=currFlagX+SPRITE_WIDTH-1)) || ((currFlagX>=peachX)&&(currFlagX<=peachX+SPRITE_WIDTH-1)))
    {
        if (((currFlagY<=peachY) && (peachY<=currFlagY+SPRITE_HEIGHT-1)) || ((currFlagY>=peachY)&&(currFlagY<=peachY+SPRITE_HEIGHT-1)))
        {
            ptrToWorld->increaseScore(1000);
            int n = ptrToWorld->getLives();
            for (int i = 0; i!=n; i++)
                ptrToWorld->decLives();
            ptrToWorld->changeLevelStatus(true);
        }
    }
    
}

// Block implementations
Block::Block(StudentWorld* s, int x, int y)
: Object(s, x, y, IID_BLOCK, 2, 1)
{}

void Block::bonk()
{
    StudentWorld* p = getPtrToWorld();
    p->playSound(SOUND_PLAYER_BONK);
}

void Block::doSomething(){}

// Pipe Implementations

Pipe::Pipe(StudentWorld* s, int x, int y)
: Object(s, x, y, IID_PIPE, 2, 1)
{}
void Pipe::bonk(){}
void Pipe::doSomething(){}


// Peach implementations
Peach::Peach(StudentWorld* s, int x, int y)
: Actor(s, x, y, IID_PEACH, 0, 0, 1, 1), remainingJumpDistance(0), jumpInitiated(false), m_tempInvincibility(0)
{}

void Peach::setDead()
{
    StudentWorld* p = getPtrToWorld();
    int lifesleft = p->getLives();
    for (int i = 0; i!=lifesleft; i++)
        p->decLives();
}

void Peach::bonk()
{
    if (m_tempInvincibility!=0)
        return;
    cerr << "peach bonked" << endl;
    StudentWorld* ptrToWorld = getPtrToWorld();
    ptrToWorld->decLives();
    m_tempInvincibility = 10;
    if (ptrToWorld->getLives()!=0)
    {
        ptrToWorld->playSound(SOUND_PLAYER_HURT);
    }
    else
    {
        setDead();
    }
}

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
    if (m_tempInvincibility>0)
        m_tempInvincibility--;
}

