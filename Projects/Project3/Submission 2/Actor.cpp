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

bool Actor::isDamageable()
{
    return false;
}

void Actor::setHitStatus(bool x)
{
    hit = x;
}
bool Actor::hitStatus()
{
    return hit;
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
void Actor::addShell(){;}

void Actor::bonk(){return;}

int Actor::getHealth(){return health;}
StudentWorld* Actor::getPtrToWorld(){return m_world;}

// Enemy class encapsulates goomba and koopa

Enemy::Enemy(StudentWorld* s, int x, int y, int idnum, int depth, double size)
: Actor(s, x, y, idnum, randInt(0, 1)*180, depth, size, 1)
{}

bool Enemy::isDamageable()
{
    return true;
}

bool Enemy::canBlock(){return false;}

Goomba::Goomba(StudentWorld* s, int x, int y)
: Enemy(s, x, y, IID_GOOMBA, 0, 1)
{}

void Goomba::doSomething()
{
    if (getHealth()==0)
        return;
    if (Enemy::checkPeachOverlap())
        return;
    Enemy::moveEnemy();
}

Koopa::Koopa(StudentWorld* s, int x, int y)
: Enemy(s, x, y, IID_KOOPA, 0, 1)
{}

void Koopa::doSomething()
{
    if (getHealth()==0)
    {
        return;
    }
    if (Enemy::checkPeachOverlap())
        return;
    Enemy::moveEnemy();
}

void Enemy::addShell(){;}

void Koopa::addShell()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    int koopaDir = getDirection();
    int targetX; int targetY = getY();
    if (koopaDir == 0)
        targetX = getX()+8;
    else
        targetX = getX()-8;
    ptrToWorld->addActor(new Shell(ptrToWorld, targetX, targetY, koopaDir));
}

Piranha::Piranha(StudentWorld* s, int x, int y)
: Enemy(s, x, y, IID_PIRANHA, 0, 1), firingDelay(0)
{}

void Piranha::doSomething()
{
    if (getHealth()==0)
        return;
    increaseAnimationNumber();
    int curX = getX(); int curY = getY();
    StudentWorld* ptrToWorld = getPtrToWorld();
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (Enemy::checkPeachOverlap())
        return;
    if (!(ptrToPeach->getY() >= curY-SPRITE_HEIGHT && (ptrToPeach->getY() <= curY+1.5*SPRITE_HEIGHT)))
        return;
    if (ptrToPeach->getX()>=curX)
        setDirection(0);
    else
        setDirection(180);
    if (firingDelay>0)
    {
        firingDelay--;
        return;
    }
    if ((ptrToPeach->getX() >= curX - 8*SPRITE_WIDTH) && (ptrToPeach->getX() <= curX + 8*SPRITE_WIDTH))
    {
        if (getDirection()==0)
            ptrToWorld->addActor(new piranhaFireball(ptrToWorld, curX+8, curY, 0));
        else
            ptrToWorld->addActor(new piranhaFireball(ptrToWorld, curX-8, curY, 180));
        ptrToWorld->playSound(SOUND_PIRANHA_FIRE);
        firingDelay = 40;
    }
}

bool Enemy::checkPeachOverlap()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedActor = nullptr;   // this would be peach
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (ptrToWorld->peachOverlap(curX, curY, ptrToBonkedActor))
    {
        if (ptrToPeach->getStarPowerStatus())
        {
            ptrToWorld->playSound(SOUND_PLAYER_KICK);
            ptrToWorld->increaseScore(100);
            setHealth(0);
        }
        else
        {
            ptrToBonkedActor->bonk();
            return true;
        }
    }
    return false;
}

void Enemy::moveEnemy()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedActor = nullptr;
    if (getDirection()==0)
    {
        if (ptrToWorld->isBlockingObject(curX+1, curY, ptrToBonkedActor))
        {
            setDirection(180);
        }
        else if (!(ptrToWorld->isBlockingObject(curX+6, curY-1, ptrToBonkedActor)))
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
        else if (!(ptrToWorld->isBlockingObject(curX-6, curY-1, ptrToBonkedActor)))
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

//Level ender
LevelEnder::LevelEnder(StudentWorld* s, int x, int y, int idnum)
: Actor(s, x, y, idnum, 0, 1, 1, 1)
{}
void LevelEnder::bonk(){}
bool LevelEnder::canBlock(){return false;}

bool LevelEnder::possiblePeachOverlap()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    Peach* ptrToPeach = ptrToWorld->getPeach();
    Actor* ptrToBonkedObject = nullptr;
    int currX = getX();
    int currY = getY();
    if (ptrToWorld->peachOverlap(currX, currY, ptrToBonkedObject))
    {
        ptrToWorld->increaseScore(1000);
        ptrToPeach->setHealth(0);
        return true;
    }
    return false;
}

// Mario implementation
Mario::Mario(StudentWorld* s, int x, int y)
: LevelEnder(s, x, y, IID_MARIO)
{}

void Mario::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    if (getHealth()==0)
        return;
    if (LevelEnder::possiblePeachOverlap())
    {
        ptrToWorld->changeGameStatus(true);
    }
}

// Flag implementations
Flag::Flag(StudentWorld* s, int x, int y)
 : LevelEnder(s, x, y, IID_FLAG)
{}


void Flag::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    if (getHealth()==0)
        return;
    if (LevelEnder::possiblePeachOverlap())
    {
        ptrToWorld->changeLevelStatus(true);
    }
}

// Projectile superclass implementation
Projectile::Projectile(StudentWorld* s, int x, int y, int idnum, int dir)
: Actor(s, x, y, idnum, dir, 1, 1, 1)
{}
void Projectile::bonk(){;}

void Projectile::doSomethingCommon(StudentWorld* &ptrToWorld, int curX, int curY)
{
    Actor* ptrToBonkedObject = nullptr;
    if (!(ptrToWorld->isBlockingObject(curX, curY-2, ptrToBonkedObject)))
    {
        moveTo(curX, curY-2);
        curX = getX();
        curY = getY();
    }
    if (getDirection()==0)
    {
        int targetX = curX+2;
        int TargetY = curY;
        if (ptrToWorld->isBlockingObject(targetX, TargetY, ptrToBonkedObject))
        {
            setHealth(0);
            return;
        }
        else
        {
            moveTo(targetX, TargetY);
        }
    }
    else if (getDirection()==180)
    {
        int targetX = curX-2;
        int TargetY = curY;
        if (ptrToWorld->isBlockingObject(targetX, TargetY, ptrToBonkedObject))
        {
            setHealth(0);
            return;
        }
        else
        {
            moveTo(targetX, TargetY);
        }
    }
}

// Piranha fireball implementation
piranhaFireball::piranhaFireball(StudentWorld* s, int x, int y, int dir)
: Projectile(s, x, y, IID_PIRANHA_FIRE, dir)
{}

void piranhaFireball::doSomething()
{
    int curX = getX(); int curY = getY();
    StudentWorld* ptrToWorld = getPtrToWorld();
    Actor* ptrToBonkedObject = nullptr;   // If overlap, then this would be peach
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (getPtrToWorld()->peachOverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToBonkedObject->setHitStatus(true);
        ptrToBonkedObject->bonk();
        ptrToPeach->setJumpPower(false);
        ptrToPeach->setStarPowerStatus(false);
        ptrToPeach->setShootingPower(false);
        setHealth(0);
        return;
    }
    else
        Projectile::doSomethingCommon(ptrToWorld, curX, curY);
}

// Fireball implementation

Fireball::Fireball(StudentWorld* s, int x, int y, int peachDir)
 : Projectile(s, x, y, IID_PEACH_FIRE, peachDir)
{}

void Fireball::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedObject = nullptr;
    if (ptrToWorld->koopagoombaoverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToWorld->increaseScore(100);
        ptrToBonkedObject->addShell();
        ptrToBonkedObject->setHitStatus(true);
        ptrToBonkedObject->setHealth(0);
        setHealth(0);
        return;
    }
    else
    {
        Projectile::doSomethingCommon(ptrToWorld, curX, curY);
    }
}

Shell::Shell(StudentWorld* s, int x, int y, int peachDir)
 : Projectile(s, x, y, IID_SHELL, peachDir)
{}

void Shell::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedObject = nullptr;
    if (ptrToWorld->koopagoombaoverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToBonkedObject->setHitStatus(true);
        ptrToBonkedObject->setHealth(0);
        ptrToWorld->increaseScore(100);
        //setHealth(0);
        return;
    }
    else
    {
        Projectile::doSomethingCommon(ptrToWorld, curX, curY);
    }
    
}
// Goodies implementations

Goodie::Goodie(StudentWorld* s, int x, int y, int idnum)
: Actor(s, x, y, idnum, 0, 1, 1, 1)
{}

void Goodie::bonk(){;}

void Goodie::goodieMove(StudentWorld* &ptrToWorld, int curX, int curY)
{
    Actor* ptrToBonkedObject = nullptr;
    if (!(ptrToWorld->isBlockingObject(curX, curY-2, ptrToBonkedObject)))
    {
        moveTo(curX, curY-2);
        curX = getX();
        curY = getY();
    }
    if (getDirection()==0)
    {
        int targetX = curX+2;
        int TargetY = curY;
        if (ptrToWorld->isBlockingObject(targetX, TargetY, ptrToBonkedObject))
        {
            setDirection(180);
            return;
        }
        else
        {
            moveTo(targetX, TargetY);
        }
    }
    else if (getDirection()==180)
    {
        int targetX = curX-2;
        int TargetY = curY;
        if (ptrToWorld->isBlockingObject(targetX, TargetY, ptrToBonkedObject))
        {
            setDirection(0);
            return;
        }
        else
        {
            moveTo(targetX, TargetY);
        }
    }
}

Star::Star(StudentWorld* s, int x, int y)
: Goodie(s, x, y, IID_STAR)
{}

void Star::doSomething()
{
    
    StudentWorld* ptrToWorld = getPtrToWorld();
    Actor* ptrToBonkedObject = nullptr;
    int curX = getX();
    int curY = getY();
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (ptrToWorld->peachOverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToWorld->increaseScore(100);
        ptrToPeach->setStarPowerStatus(true);
        ptrToPeach->setStarPowerTime(150);
        ptrToPeach->setHealth(2);
        setHealth(0);
        ptrToWorld->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else
        Goodie::goodieMove(ptrToWorld, curX, curY);
}

Mushroom::Mushroom(StudentWorld* s, int x, int y)
: Goodie(s, x, y, IID_MUSHROOM)
{}

void Mushroom::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    Actor* ptrToBonkedObject = nullptr;
    int curX = getX();
    int curY = getY();
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (ptrToWorld->peachOverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToWorld->increaseScore(75);
        ptrToPeach->setJumpPower(true);
        ptrToPeach->setHealth(2);
        setHealth(0);
        ptrToWorld->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else
        Goodie::goodieMove(ptrToWorld, curX, curY);
}

Flower::Flower(StudentWorld* s, int x, int y)
: Goodie(s, x, y, IID_FLOWER)
{}

void Flower::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    Actor* ptrToBonkedObject = nullptr;
    int curX = getX();
    int curY = getY();
    Peach* ptrToPeach = ptrToWorld->getPeach();
    if (ptrToWorld->peachOverlap(curX, curY, ptrToBonkedObject))
    {
        ptrToWorld->increaseScore(50);
        ptrToPeach->setShootingPower(true);
        ptrToPeach->setHealth(2);
        setHealth(0);
        ptrToWorld->playSound(SOUND_PLAYER_POWERUP);
        return;
    }
    else
        Goodie::goodieMove(ptrToWorld, curX, curY);
}

// Block implementations
Block::Block(StudentWorld* s, int x, int y, int goodieType)
: Object(s, x, y, IID_BLOCK, 2, 1), m_Goodie(goodieType)
{}

void Block::bonk()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    if (m_Goodie==0)
        ptrToWorld->playSound(SOUND_PLAYER_BONK);
    else if (m_Goodie==1)
    {
        if (!hitStatus())
        {
            int curBlockX = getX();
            int curBlockY = getY();
            ptrToWorld->playSound(SOUND_POWERUP_APPEARS);
            ptrToWorld->addActor(new Flower(ptrToWorld, curBlockX, curBlockY+8));
            setHitStatus(true);
        }
        else
            ptrToWorld->playSound(SOUND_PLAYER_BONK);
    }
    else if (m_Goodie==2)
    {
        if (!hitStatus())
        {
            int curBlockX = getX();
            int curBlockY = getY();
            ptrToWorld->playSound(SOUND_POWERUP_APPEARS);
            ptrToWorld->addActor(new Mushroom(ptrToWorld, curBlockX, curBlockY+8));
            setHitStatus(true);
        }
        else
            ptrToWorld->playSound(SOUND_PLAYER_BONK);
    }
    else if (m_Goodie==3)
    {
        if (!hitStatus())
        {
            int curBlockX = getX();
            int curBlockY = getY();
            ptrToWorld->playSound(SOUND_POWERUP_APPEARS);
            ptrToWorld->addActor(new Star(ptrToWorld, curBlockX, curBlockY+8));
            setHitStatus(true);
        }
        else
            ptrToWorld->playSound(SOUND_PLAYER_BONK);
    }
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
: Actor(s, x, y, IID_PEACH, 0, 0, 1, 1), remainingJumpDistance(0), jumpInitiated(false), m_tempInvincibility(0),hitpts(1), m_shootingPower(false), m_time_to_recharge_before_next_fire(0), m_jumpPower(false), m_remainingStarPower(0)
{}

void Peach::setStarPowerTime(int time)
{
    m_remainingStarPower = time;
}

bool Peach::getStarPowerStatus()
{
    return m_starPower;
}

bool Peach::getJumpPowerStatus()
{
    return m_jumpPower;
}

bool Peach::getShootPowerStatus()
{
    return m_shootingPower;
}

void Peach::setStarPowerStatus(bool b)
{
    m_starPower = b;
}
void Peach::setJumpPower(bool b)
{
    m_jumpPower = b;
}

int Peach::getRechargeTime()
{
    return m_time_to_recharge_before_next_fire;
}

void Peach::getCurrentCoord(int &x, int &y)
{
    x = getX();
    y = getY();
}
bool Peach::fireballPowerStatus()
{
    return m_shootingPower;
}

void Peach::setRechargeTime(int t)
{
    m_time_to_recharge_before_next_fire = t;
}

void Peach::setShootingPower(bool b)
{
    m_shootingPower = b;
}

void Peach::setDead()
{
    StudentWorld* p = getPtrToWorld();
    int lifesleft = p->getLives();
    for (int i = 0; i!=lifesleft; i++)
        p->decLives();
}

void Peach::bonk()
{
    if (m_tempInvincibility!=0 || m_starPower)
        return;
    cerr << "peach bonked" << endl;
    StudentWorld* ptrToWorld = getPtrToWorld();
    int curHealth = getHealth();
    setHealth(curHealth-1);
    m_tempInvincibility = 10;
    if (getHealth()>0)
    {
        ptrToWorld->playSound(SOUND_PLAYER_HURT);
    }
    else
    {
        ptrToWorld->decLives();
        setHealth(0);
    }
}

void Peach::doSomething()
{
    StudentWorld* ptrToWorld = getPtrToWorld();
    if (getHealth()==0)
    {
        ptrToWorld->decLives();
        return;
    }
    int key;
    int curX = getX();
    int curY = getY();
    Actor* ptrToBonkedActor = nullptr;
    
    if (m_remainingStarPower>0)
        m_remainingStarPower--;
    else
        m_starPower = false;
    
    if (m_tempInvincibility>0)
        m_tempInvincibility--;
    if (m_time_to_recharge_before_next_fire>0)
        m_time_to_recharge_before_next_fire--;
    
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
                    if (m_jumpPower)
                        remainingJumpDistance = 12;
                    else
                        remainingJumpDistance = 8;
                    jumpInitiated = true;
                    ptrToWorld->playSound(SOUND_PLAYER_JUMP);
                    break;
                }
                moveTo(curX, curY+4);
                break;
            }
            case KEY_PRESS_SPACE:
            {
                Peach* ptrToPeach = ptrToWorld->getPeach();
                if (!ptrToPeach->fireballPowerStatus())
                {
                    return;
                }
                if (ptrToPeach->getRechargeTime()>0)
                    return;
                ptrToWorld->playSound(SOUND_PLAYER_FIRE);
                ptrToPeach->setRechargeTime(8);
                int curPeachX = ptrToPeach->getX();
                int curPeachY = ptrToPeach->getY();
                int targetFireballX;
                int targetFireballY;
                int peachDir = ptrToPeach->getDirection();
                if (peachDir == 0)
                {
                    targetFireballX = curPeachX+4;
                    targetFireballY = curPeachY;
                }
                else
                {
                    targetFireballX = curPeachX-4;
                    targetFireballY = curPeachY;
                }
                ptrToWorld->addActor(new Fireball(ptrToWorld, targetFireballX, targetFireballY, peachDir));
                break;
            }
            default:
                break;
        }
    }
}

