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

bool Actor::hasHP(){
    return false;
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

bool Dirt::isDamagable(){
    return true;
}

Dirt::~Dirt(){
    ;
}

LivingActor::LivingActor(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int hp)
:Actor(imageID, startX, startY, startDirection, depth, ptr)
{
    m_HP = hp;
}

bool LivingActor::hasHP(){
    return true;
}

int LivingActor::getHP(){
    return m_HP;
}

void LivingActor::setHP(int num){
    m_HP = num;
}

Socrates::Socrates(StudentWorld* ptr)
:LivingActor(IID_PLAYER, 0, 128, 0, 0, ptr, 100)
{
    m_sprayCount = 20;
    m_flameCount = 5;
}

bool Socrates::isDamagable(){
    return true;
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
    }else if(m_sprayCount<20){
        m_sprayCount+=1;
    }
    return;
}

void Socrates::addFlame(){
    m_flameCount+=5;
}

Socrates::~Socrates(){
    ;
}

Projectile::Projectile(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int travelDistance, int damage)
:Actor(imageID, startX, startY, startDirection, depth, ptr)
{
    m_damage = damage;
    m_maxTravel = travelDistance;
    m_distTraveled = 0;
}

bool Projectile::isDamagable(){
    return false;
}

int Projectile::getDamage() const{
    return m_damage;
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
    if(getWorld()->checkActorOverlap(getX(), getY())){
        setDead();
        return;
    }
    moveTo(getX()+x, getY()+y);
    increaseDist(SPRITE_RADIUS*2);
    if(getDist()>=getMaxTravel()){
        setDead();
    }
    
}

//FLAME PROJECTILE
Flame::Flame(int startX, int startY, Direction startDirection, StudentWorld* ptr)
:Projectile(IID_FLAME, startX, startY, startDirection, 1, ptr, 32, 5)
{
    
}


//SPRAY PROJECTILE
Spray::Spray(int startX, int startY, Direction startDirection, StudentWorld* ptr)
:Projectile(IID_SPRAY, startX, startY, startDirection, 1, ptr, 112, 2)
{
    
}

//GOODIES

Goodie::Goodie(int imageID, int startX, int startY, StudentWorld* ptr)
:Actor(imageID, startX, startY, 0, 1, ptr)
{
    m_lifespan = std::max(rand()%(300-10*getWorld()->getLevel()), 50);
}

bool Goodie::isDamagable(){
    return false;
}

int Goodie::getLifespan(){
    return m_lifespan;
}

void Goodie::decreaseLife(){
    m_lifespan-=1;
}


//RESTORE HEALTH GOODIE

RestoreHealth::RestoreHealth(int startX, int startY, StudentWorld* ptr)
:Goodie(IID_RESTORE_HEALTH_GOODIE, startX, startY, ptr)
{
    
}

void RestoreHealth::doSomething(){
    if(isDead()){
        return;
    }
    
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        //increase points by 250
        getWorld()->increaseScore(250);
        setDead();
        //play sound
        //restore health
        getWorld()->restoreHealth();
        return;
    }
    
    if(getLifespan()<=0){
        setDead();
    }
    
    decreaseLife();
}

//FLAME GOODIE

FlameGoodie::FlameGoodie(int startX, int startY, StudentWorld* ptr)
:Goodie(IID_FLAME_THROWER_GOODIE, startX, startY, ptr)
{
    
}

void FlameGoodie::doSomething(){
    if(isDead()){
        return;
    }
    
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->increaseScore(300);
        setDead();
        //play sound
        getWorld()->addPlayerFlame();
        return;
    }
    
    if(getLifespan()<=0){
        setDead();
    }
    
    decreaseLife();
}



