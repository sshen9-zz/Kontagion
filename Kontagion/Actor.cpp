#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <cmath>

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

void Actor::doSomething(){
    return;
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
    int ch;
    double PI = 3.14159265;
    if(getWorld()->getKey(ch)){
        switch (ch) {
            case KEY_PRESS_LEFT:
                //move clockwise
                setDirection(getDirection()+5);
                moveTo(128*cos((getDirection()+180)*1.0 / 360 * 2 * PI)+128, 128*sin((getDirection()+180)*1.0 / 360 * 2 * PI)+128);
                break;
            case KEY_PRESS_RIGHT:
                //MOVE COUNTERCLOCKWISE
                setDirection(getDirection()-5);
                moveTo(128*cos((getDirection()+180)*1.0 / 360 * 2 * PI)+128, 128*sin((getDirection()+180)*1.0 / 360 * 2 * PI)+128);
                break;
//            case KEY_PRESS_ENTER:
//                //flamethrower
//                if(m_flameCount>0){
//                    //add 16 flame objects
//                    m_flameCount-=1;
//                    //playsound
//                }
//                break;
//            case KEY_PRESS_SPACE:
//                if(m_sprayCount>0){
//                    //add spray object
//                    m_sprayCount-=1;
//                    //playsound
//                }
//                break;
            default:
                break;
        }
    }
    
    //replenish spray
    if(m_sprayCount<20){
        m_sprayCount+=1;
    }
    return;
}

Socrates::~Socrates(){
    ;
}

//FLAME PROJECTILE
//Flame::Flame(int startX, int startY, StudentWorld* ptr)
//:Actor(IID_FLAME, startX, startY, 0, 1, 0, ptr)
//{
//    
//}

//SPRAY PROJECTILE
Spray::Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr)
:Actor(IID_SPRAY, startX, startY, startDirection, 1, 0, ptr)
{
    
}

//FOOD
//


Food::Food(int startX, int startY, StudentWorld* ptr)
:Actor(IID_FOOD, startX, startY, 90, 1, 0, ptr)
{
    
}



