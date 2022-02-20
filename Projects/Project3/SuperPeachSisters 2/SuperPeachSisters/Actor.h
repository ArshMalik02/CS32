#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, int healthStatus);
    virtual void doSomething() = 0;
    virtual void bonk();
    virtual bool canBlock();
    // Accessors
    int getHealth();
    StudentWorld* getPtrToWorld();
private:
    StudentWorld* m_world;
    int health;
    bool hit;
};

class Object : public Actor
{
  public:
    Object(StudentWorld* s, int x, int y, int idnum);
    virtual void doSomething() = 0;
    virtual void bonk() = 0;
    bool cannotBeDamaged();
    bool canBlock();
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
private:
    int remainingJumpDistance;
    bool jumpInitiated;
};


#endif // ACTOR_H_

