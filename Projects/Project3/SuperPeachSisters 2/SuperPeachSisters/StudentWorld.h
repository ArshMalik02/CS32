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
    bool enemyOverlap(int x, int y, Actor* &p);
    Actor* getPeach();
    void changeLevelStatus(bool x);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
private:
    std::list<Actor*> objects;
    Actor* m_peach;
    bool gameStatus;
    bool nextLevel;
};

#endif // STUDENTWORLD_H_
