#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus);
    virtual ~Actor();
    virtual void doSomething() = 0;
    virtual void bonk();
    virtual bool canBlock();
    // Accessors
    int getHealth();
    // Modifiers
    void setHealth(int x);
    StudentWorld* getPtrToWorld();
private:
    StudentWorld* m_world;
    int health;
    bool hit;
};

class Enemy : public Actor
{
public:
    Enemy(StudentWorld* s, int x, int y, int idnum, int d, double size);
    void doSomething();
    bool canBlock();
};

class Goomba : public Enemy
{
public:
    Goomba(StudentWorld* s, int x, int y);
};

class Koopa : public Enemy
{
public:
    Koopa(StudentWorld* s, int x, int y);
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

class Flag : public Object
{
public:
    Flag(StudentWorld*s , int x, int y);
    virtual void doSomething();
    virtual bool canBlock();
    virtual void bonk();
};

class Block : public Object
{
public:
    Block(StudentWorld* s, int x, int y);
    virtual void doSomething();
    virtual void bonk();
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
    void setDead();
private:
    int remainingJumpDistance;
    bool jumpInitiated;
    int m_tempInvincibility;
};


#endif // ACTOR_H_

