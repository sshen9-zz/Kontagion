#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction startDirection, int depth);
    virtual bool doSomething() = 0;
    
private:
};

class Dirt: public Actor
{
public:
    Dirt(int imageID, int startX, int startY, Direction startDirection, int depth);
    
private:
};

#endif // ACTOR_H_
