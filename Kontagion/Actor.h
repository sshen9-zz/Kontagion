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
    virtual bool isPit();
    virtual void doSomething();
    virtual bool isDamagable();
    virtual bool isFood();
    virtual bool isDirt();
    virtual bool hasHP();
    virtual void decHP(int dmg);
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
    virtual ~LivingActor();
    virtual bool hasHP();
    int getHP();
    void setHP(int num);
    virtual void decHP(int dmg);
    virtual bool isPlayer();
    virtual void turnIntoFood();
    virtual void playSoundHurt() = 0;
    virtual void playSoundDie() = 0;
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
    int getSprays();
    int getFlames();
    virtual bool isPlayer();
    virtual void playSoundHurt();
    virtual void playSoundDie();
private:
    int m_sprayCount;
    int m_flameCount;
};

class Dirt: public Actor
{
public:
    Dirt(int startX, int startY, StudentWorld* ptr);
    virtual bool isDirt();
    virtual ~Dirt();
    
private:
};

class Food: public Actor
{
public:
    Food(int startX, int startY, StudentWorld* ptr);
    virtual bool isDamagable();
    virtual bool isFood();
    virtual ~Food();
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
    virtual ~Projectile();
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
    virtual ~Flame();
private:
};

class Spray: public Projectile
{
public:
    Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr);
    virtual ~Spray();
private:
};


//GOODIES

class Goodie: public Actor
{
public:
    Goodie(int imageID, int startX, int startY, StudentWorld* ptr);
    int getLifespan();
    void decreaseLife();
    virtual ~Goodie();
private:
    int m_lifespan;
};

class RestoreHealth: public Goodie
{
public:
    RestoreHealth(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    virtual ~RestoreHealth();
private:
};

class FlameGoodie: public Goodie
{
public:
    FlameGoodie(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    virtual ~FlameGoodie();
private:
};

class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    virtual ~ExtraLifeGoodie();
private:
};

class Fungus: public Goodie
{
public:
    Fungus(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    virtual ~Fungus();
private:
};

class Bacteria: public LivingActor
{
public:
    Bacteria(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int hp, int mpDist);
    int getFoodCount();
    void incFoodCount();
    void resetFoodCount();
    int getMpDist();
    void decMpDist();
    void setMpDist();
    virtual ~Bacteria();
    virtual void turnIntoFood();
private:
    int m_foodCount;
    int m_mpDist;
};

class Salmonella: public Bacteria
{
public:
    Salmonella(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    void MPdistOrGetFoodAngle();
    virtual ~Salmonella();
    virtual void playSoundHurt();
    virtual void playSoundDie();
private:
};

class AggressiveSalmonella: public Salmonella
{
public:
    AggressiveSalmonella(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    virtual ~AggressiveSalmonella();
private:
};

class Ecoli: public Bacteria
{
public:
    Ecoli(int startX, int startY, StudentWorld* ptr);
    virtual void doSomething();
    void EcoliChasePlayer(double x, double y);
    virtual ~Ecoli();
    virtual void playSoundHurt();
    virtual void playSoundDie();
private:
};

class Pit: public Actor
{
public:
    Pit(int startX, int startY, StudentWorld* ptr);
    virtual ~Pit();
    virtual void doSomething();
    virtual bool isPit();
    virtual bool isDamagable();
    bool emittedAll();
    int getSalmonella();
    int getAggressiveSalmonella();
    int getEcoli();
    int getSum();
    void decEcoli();
    void decSalmonella();
    void decAggressiveSalmonella();
    void decSum();
private:
    int m_SalmonellaLeft;
    int m_AggressiveSalmonellaLeft;
    int m_EcoliLeft;
    int m_sumBacteria;
    
};

#endif // ACTOR_H_
