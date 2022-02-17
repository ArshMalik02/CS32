#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Level.h"
#include <string>
#include <list>

class Actor;

//// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
//class Twinkler;
//
//class StudentWorld : public GameWorld
//{
//public:
//  StudentWorld(std::string assetPath);
//  virtual int init();
//  virtual int move();
//  virtual void cleanUp();
//
//private:
//  Twinkler* m_stella;
//};

class StudentWorld : public GameWorld
{
public:
  StudentWorld(std::string assetPath);
  virtual int init();
  virtual int move();
  virtual void cleanUp();

private:
    std::list<Actor*> objects;
};

#endif // STUDENTWORLD_H_
