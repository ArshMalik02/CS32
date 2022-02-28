#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>

class Peach;

class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~StudentWorld();
    void addActor(Actor* p);
    bool isBlockingObject(int x, int y, Actor* &p);
    bool peachOverlap(int x, int y, Actor* &p);
    bool koopagoombaoverlap(int x, int y, Actor* &p);
    Peach* getPeach();
    void changeLevelStatus(bool x);
    void changeGameStatus(bool x);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
private:
    std::list<Actor*> objects;
    Peach* m_peach;
    bool gameStatus;
    bool levelStatus;
};

#endif // STUDENTWORLD_H_
