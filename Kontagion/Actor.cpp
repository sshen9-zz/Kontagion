#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//ACTOR CLASS
Actor::Actor(int imageID, int startX, int startY, Direction startDirection, int depth, int hp, StudentWorld* ptr)
:GraphObject(imageID, startX, startY, startDirection, depth)
{
    m_HP = hp;
    m_isAlive = true;
    m_worldPtr = ptr;
}

Actor::~Actor(){
    ;
}

bool Actor::isAlive(){
    return m_isAlive;
}

void Actor::setDead(){
    m_isAlive = false;
}

int Actor::getHP(){
    return m_HP;
}

void Actor::setHP(int hp){
    m_HP = hp;
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

bool Dirt::doSomething(){
    return true;
}

Socrates::Socrates(StudentWorld* ptr)
:Actor(IID_PLAYER, 0, 128, 0, 0, 100, ptr)
{
    m_sprayCount = 20;
    m_flameCount = 5;
}

bool Socrates::doSomething(){
    if(!isAlive()){
        return false;
    }
    return true;
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

bool Food::doSomething(){
    return true;
}
