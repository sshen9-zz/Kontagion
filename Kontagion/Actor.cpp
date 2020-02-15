#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//ACTOR CLASS
Actor::Actor(int imageID, int startX, int startY, Direction startDirection, int depth, int hp, StudentWorld* ptr)
:GraphObject(imageID, startX, startY, startDirection, depth)
{
    m_HP = hp;
    m_dead = false;
    m_worldPtr = ptr;
}

Actor::~Actor(){
    ;
}

bool Actor::isDead() const{
    return m_dead;
}

void Actor::setDead(){
    m_dead = true;
}

int Actor::getHP() const{
    return m_HP;
}

void Actor::setHP(int hp){
    m_HP = hp;
}

StudentWorld* Actor::getWorld() const{
    return m_worldPtr;
}

//DIRT
//

Dirt::Dirt(int startX, int startY, StudentWorld* ptr)
:Actor(IID_DIRT, startX, startY, 0, 1, 0, ptr)
{
    
}

Dirt::~Dirt(){
    ;
}

void Dirt::doSomething(){
    return;
}

Socrates::Socrates(StudentWorld* ptr)
:Actor(IID_PLAYER, 0, 128, 0, 0, 100, ptr)
{
    m_sprayCount = 20;
    m_flameCount = 5;
}

void Socrates::doSomething(){
    if(isDead()){
        return;
    }
    return;
}

Socrates::~Socrates(){
    ;
}


//FOOD
//


Food::Food(int startX, int startY, StudentWorld* ptr)
:Actor(IID_FOOD, startX, startY, 90, 1, 0, ptr)
{
    
}


void Food::doSomething(){
    return;
}


