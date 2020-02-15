#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction startDirection, int depth, int hp, StudentWorld* ptr);
    virtual ~Actor();
    virtual void doSomething();
    bool isDead() const;
    void setDead();
    int getHP() const;
    void setHP(int hp);
    StudentWorld* getWorld() const;
    
private:
    bool m_dead;
    int m_HP;
    StudentWorld* m_worldPtr;
};

class Dirt: public Actor
{
public:
    Dirt(int startX, int startY, StudentWorld* ptr);
    virtual ~Dirt();
    
private:
};

class Socrates: public Actor
{
public:
    Socrates(StudentWorld* ptr);
    virtual ~Socrates();
    virtual void doSomething();
private:
    int m_sprayCount;
    int m_flameCount;
};

//class Flame: public Actor
//{
//public:
//    Flame(int startX, int startY, StudentWorld* ptr);
//private:
//};

class Spray: public Actor
{
public:
    Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr);
private:
};

class Food: public Actor
{
public:
    Food(int startX, int startY, StudentWorld* ptr);
private:
};
#endif // ACTOR_H_
