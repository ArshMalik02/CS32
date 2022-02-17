#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, bool lifeStatus);
    virtual void doSomething() = 0;
private:
    StudentWorld* m_world;
    bool alive;
    bool hit;
};


class Block : public Actor
{
public:
    Block(StudentWorld* s, int x, int y);
    virtual void doSomething();
};


#endif // ACTOR_H_

//#ifndef ACTOR_H_
//#define ACTOR_H_
//
//#include "GraphObject.h"
//#include "StudentWorld.h"
//
//class Twinkler : public GraphObject
//{
//  public:
//    Twinkler(StudentWorld* sw, int x, int y);
//    virtual void doSomething();
//
//  private:
//    StudentWorld* m_world;
//};
//
//#endif // ACTOR_H_

