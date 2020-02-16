#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class StudentWorld;

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr);
    virtual ~Actor();
    virtual void doSomething();
    virtual bool isDamagable() = 0;
    virtual bool hasHP() = 0;
    bool isDead() const;
    void setDead();
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
    virtual bool isDamagable();
    virtual bool hasHP();
    
private:
};

class Socrates: public Actor
{
public:
    Socrates(StudentWorld* ptr);
    virtual ~Socrates();
    virtual void doSomething();
    virtual bool isDamagable();
    virtual bool hasHP();
private:
    int m_sprayCount;
    int m_flameCount;
};

class Projectile: public Actor
{
public:
    Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int travelDistance, int damage);
    int getMaxTravel() const;
    int getDist() const;
    int getDamage() const;
    void increaseDist(int dist);
    virtual void doSomething();
    virtual bool isDamagable();
    virtual bool hasHP();
private:
    int m_damage;
    int m_maxTravel;
    int m_distTraveled;
    Direction m_direction;
};

class Flame: public Projectile
{
public:
    Flame(int startX, int startY, Direction startDirection, StudentWorld* ptr);
private:
};

class Spray: public Projectile
{
public:
    Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr);
private:
};


//GOODIES

class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, StudentWorld* ptr);
    virtual bool isDamagable();
    virtual bool hasHP();
    int getLifespan();
    void decreaseLife();
private:
    int m_lifespan;
};

class RestoreHealth: public Goodie
{
public:
    RestoreHealth(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
private:
};
#endif // ACTOR_H_
