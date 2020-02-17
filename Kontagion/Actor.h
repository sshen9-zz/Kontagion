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
    virtual bool isDamagable();
    virtual bool hasHP();
    bool isDead() const;
    void setDead();
    StudentWorld* getWorld() const;
    
private:
    bool m_dead;
    StudentWorld* m_worldPtr;
};

class LivingActor: public Actor
{
public:
    LivingActor(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int hp);
    virtual bool hasHP();
    int getHP();
    void setHP(int num);
    void checkDead();
private:
    int m_HP;
};

class Socrates: public LivingActor
{
public:
    Socrates(StudentWorld* ptr);
    virtual ~Socrates();
    virtual void doSomething();
    void addFlame();
private:
    int m_sprayCount;
    int m_flameCount;
};

class Dirt: public Actor
{
public:
    Dirt(int startX, int startY, StudentWorld* ptr);
    virtual ~Dirt();
    
private:
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

class FlameGoodie: public Goodie
{
public:
    FlameGoodie(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
private:
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
private:
};

class Fungus: public Goodie
{
public:
    Fungus(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
private:
};

class Bacteria: public LivingActor
{
public:
    Bacteria(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int hp, int mpDist);
private:
};

class Salmonella: public Bacteria
{
public:
    Salmonella(int imageID, int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
private:
};

#endif // ACTOR_H_
