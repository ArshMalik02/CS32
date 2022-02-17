#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(StudentWorld* p, int x, int y, int ID, int startDir, int depth, double size, bool lifeStatus)
: GraphObject(ID, x, y, startDir, depth, size), m_world(p), alive(lifeStatus), hit(false)
{
}

Block::Block(StudentWorld* s, int x, int y)
: Actor(s, x, y, IID_BLOCK, 0, 2, 1, false)
{}

void Block::doSomething(){};




//#include "Actor.h"
//#include "StudentWorld.h"
//#include "GameConstants.h"
//
//
//Twinkler::Twinkler(StudentWorld* sw, int x, int y)
// : GraphObject(IID_STAR, x, y), m_world(sw)
//{
//}
//
//void Twinkler::doSomething()
//{
//    int key;
//    if (m_world->getKey(key))
//    {
//        switch (key)
//        {
//          case KEY_PRESS_SPACE:
//            m_world->playSound(SOUND_PLAYER_JUMP);
//            break;
//        }
//    }
//}

