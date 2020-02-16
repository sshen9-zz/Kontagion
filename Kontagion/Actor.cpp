#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"
#include <cmath>

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

//ACTOR CLASS
Actor::Actor(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr)
:GraphObject(imageID, startX, startY, startDirection, depth)
{
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

StudentWorld* Actor::getWorld() const{
    return m_worldPtr;
}

//DIRT
//

Dirt::Dirt(int startX, int startY, StudentWorld* ptr)
:Actor(IID_DIRT, startX, startY, 0, 1, ptr)
{
    
}

Dirt::~Dirt(){
    ;
}


Socrates::Socrates(StudentWorld* ptr)
:Actor(IID_PLAYER, 0, 128, 0, 0, ptr)
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
            case KEY_PRESS_ENTER:
                //flamethrower
                if(m_flameCount>0){
                    //add 16 flame objects
                    getWorld()->addFlames(getX(), getY(), getDirection());
//                    m_flameCount-=1;
                    //playsound
                }
                break;
            case KEY_PRESS_SPACE:
                if(m_sprayCount>0){
                    getWorld()->addSpray(getX(), getY(), getDirection());
                    m_sprayCount-=1;
                    //playsound
                }
                break;
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

Projectile::Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int travelDistance)
:Actor(imageID, startX, startY, startDirection, depth, ptr)
{
    m_maxTravel = travelDistance;
    m_distTraveled = 0;
}

int Projectile::getDist() const{
    return m_distTraveled;
}

int Projectile::getMaxTravel() const{
    return m_maxTravel;
}

void Projectile::increaseDist(int dist){
    m_distTraveled+=dist;
}

void Projectile::doSomething(){
    if(isDead()){
        return;
    }
    double x = SPRITE_RADIUS*2*cos(getDirection()*3.14159265/180);
    double y = SPRITE_RADIUS*2*sin(getDirection()*3.14159265/180);
    moveTo(getX()+x, getY()+y);
    increaseDist(SPRITE_RADIUS*2);
    if(getDist()>=getMaxTravel()){
        setDead();
    }
}

//FLAME PROJECTILE
Flame::Flame(int startX, int startY, Direction startDirection, StudentWorld* ptr)
:Projectile(IID_FLAME, startX, startY, startDirection, 1, ptr, 32)
{
    
}


//SPRAY PROJECTILE
Spray::Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr)
:Projectile(IID_SPRAY, startX, startY, startDirection, 1, ptr, 112)
{
    
}





