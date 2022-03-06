#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include <string>
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus);
    virtual ~Actor();
    virtual void addShell();
    virtual void doSomething() = 0;
    virtual void bonk();
    virtual bool canBlock();
    virtual bool isDamageable();
    // Accessors
    int getHealth();
    bool hitStatus();
    // Modifiers
    void setHitStatus(bool x);
    void setHealth(int x);
    StudentWorld* getPtrToWorld();
private:
    StudentWorld* m_world;
    int health;
    bool hit;
};

class Goodie : public Actor
{
public:
    Goodie(StudentWorld* s, int x, int y, int idnum);
    void goodieMove(StudentWorld* &ptrToWorld, int curX, int curY);
    void bonk();
};

class Projectile : public Actor
{
public:
    Projectile(StudentWorld* s, int x, int y, int idnum, int dir);
    virtual void doSomething() = 0;
    virtual void bonk();
    void doSomethingCommon(StudentWorld* &ptrToWorld, int curX, int curY);
};

class piranhaFireball : public Projectile
{
public:
    piranhaFireball(StudentWorld* s, int x, int y, int dir);
    virtual void doSomething();
};

class Shell : public Projectile
{
public:
    Shell(StudentWorld* s, int x, int y, int peachDir);
    virtual void doSomething();
};

class Fireball : public Projectile
{
public:
    Fireball(StudentWorld* s, int x, int y, int peachDir);
    virtual void doSomething();
};

class Flower : public Goodie
{
public:
    Flower(StudentWorld* s, int x, int y);
    virtual void doSomething();
};

class Mushroom : public Goodie
{
public:
    Mushroom(StudentWorld* s, int x, int y);
    virtual void doSomething();
};

class Star : public Goodie
{
public:
    Star(StudentWorld* s, int x, int y);
    virtual void doSomething();
};

class Enemy : public Actor
{
public:
    Enemy(StudentWorld* s, int x, int y, int idnum, int d, double size);
    void moveEnemy();
    bool checkPeachOverlap();
    virtual void doSomething() = 0;
    bool canBlock();
    virtual bool isDamageable();
    virtual void addShell();
};

class Piranha : public Enemy
{
public:
    Piranha(StudentWorld* s, int x, int y);
    virtual void doSomething();
private:
    int firingDelay;
};

class Goomba : public Enemy
{
public:
    Goomba(StudentWorld* s, int x, int y);
    virtual void doSomething();
};

class Koopa : public Enemy
{
public:
    Koopa(StudentWorld* s, int x, int y);
    virtual void doSomething();
    virtual void addShell();
};

class LevelEnder : public Actor
{
public:
    LevelEnder(StudentWorld* s, int x, int y, int idnum);
    virtual void doSomething() = 0;
    virtual bool canBlock();
    virtual void bonk();
    bool possiblePeachOverlap();
};

class Mario : public LevelEnder
{
public:
    Mario(StudentWorld*s , int x, int y);
    virtual void doSomething();
};

class Flag : public LevelEnder
{
public:
    Flag(StudentWorld*s , int x, int y);
    virtual void doSomething();
};

class Object : public Actor
{
  public:
    Object(StudentWorld* s, int x, int y, int idnum, int d, double size);
    virtual void doSomething() = 0;
    virtual void bonk() = 0;
    bool cannotBeDamaged();
    virtual bool canBlock();
};

class Block : public Object
{
public:
    Block(StudentWorld* s, int x, int y, int goodieType);
    virtual void doSomething();
    virtual void bonk();
private:
    int m_Goodie; // 0 = No Goodie, 1 == Flower Goodie, 2 == Mushroom, 3 == star
};

class Pipe : public Object
{
public:
    Pipe(StudentWorld* s, int x, int y);
    virtual void doSomething();
    virtual void bonk();
};

class Peach : public Actor
{
public:
    Peach(StudentWorld* s, int x, int y);
    virtual void doSomething();
    virtual void bonk();
    void getCurrentCoord(int &x, int &y);
    bool fireballPowerStatus();
    int getRechargeTime();
    bool getStarPowerStatus();
    bool getJumpPowerStatus();
    bool getShootPowerStatus();
    void setStarPowerTime(int time);
    void setRechargeTime(int t);
    void setDead();
    void setShootingPower(bool b);
    void setJumpPower(bool b);
    void setStarPowerStatus(bool b);
private:
    bool m_shootingPower;
    bool m_jumpPower;
    bool m_starPower;
    int m_remainingStarPower;
    int hitpts;
    int remainingJumpDistance;
    bool jumpInitiated;
    int m_tempInvincibility;
    int m_time_to_recharge_before_next_fire;
    
};


#endif // ACTOR_H_

