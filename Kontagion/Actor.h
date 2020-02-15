#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction startDirection, int depth, int hp);
    virtual ~Actor();
    virtual bool doSomething() = 0;
    bool isAlive();
    void setDead();
    int getHP();
    void setHP(int hp);
    
private:
    bool m_isAlive;
    int m_HP;
};

class Dirt: public Actor
{
public:
    Dirt(int startX, int startY);
    virtual ~Dirt();
    virtual bool doSomething();
    
private:
};

class Socrates: public Actor
{
public:
    Socrates();
    virtual ~Socrates();
    virtual bool doSomething();
private:
    int m_sprayCount;
    int m_flameCount;
};

class Food: public Actor
{
public:
    Food(int startX, int startY);
    virtual bool doSomething();
private:
};
#endif // ACTOR_H_
