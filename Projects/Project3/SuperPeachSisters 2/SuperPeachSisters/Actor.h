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

class Block : public Actor
{
public:
    Block(StudentWorld* s, int x, int y);
    virtual void doSomething();
    virtual void bonk();
    virtual bool canBlock();
};

class Peach : public Actor
{
public:
    Peach(StudentWorld* s, int x, int y);
    virtual void doSomething();
};


#endif // ACTOR_H_

