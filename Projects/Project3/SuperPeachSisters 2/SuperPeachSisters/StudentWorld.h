#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>

class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    bool isBlockingObject(int x, int y, Actor* &p);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
private:
    std::list<Actor*> objects;
    Actor* m_peach;
};

#endif // STUDENTWORLD_H_
