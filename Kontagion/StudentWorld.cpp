#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
    return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    m_playerPtr = new Socrates(this);
    
    //initialize pits
    for(int i=0; i<getLevel(); i++){
        while(true){
            double a = randInt(0, 359);
            double r = 120*sqrt(randInt(0, 10000)/10000.0);
            double x = r*cos(a*3.14159265/180)+128;
            double y = r*sin(a*3.14159265/180)+128;
            if(!checkPitOverlap(x, y)){
                li.push_back(new Pit(x,y,this));
                break;
            }
        }
    }
    
    //initialize food
    int numFood = min(5*getLevel(), 25);
    for(int i=0; i<numFood; i++){
        while(true){
            double a = randInt(0, 359);
            double r = 120*sqrt(randInt(0, 10000)/10000.0);
            double x = r*cos(a*3.14159265/180)+128;
            double y = r*sin(a*3.14159265/180)+128;
            if(!checkCreateFoodOverlap(x, y)){
                li.push_back(new Food(x, y, this));
                break;
            }
        }
    }
    
    //initialize dirt objects
    int numDirt = max(180-20*getLevel(), 20);
    for(int i=0; i<numDirt; i++){
        while(true){
            double a = randInt(0, 359);
            double r = 120*sqrt(randInt(0, 10000)/10000.0);
            double x = r*cos(a*3.14159265/180)+128;
            double y = r*sin(a*3.14159265/180)+128;
            if(!checkCreateDirtOverlap(x, y)){
                li.push_back(new Dirt(x, y, this));
                break;
            }
        }
    }


    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    if(!m_playerPtr->isDead()){
        m_playerPtr->doSomething();
    }
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if(!(*it)->isDead()){
            //if not dead, do something
            (*it)->doSomething();
        }
        it++;
    }
    //delete dead actors
    it = li.begin();
    while(it!=li.end()){
        if((*it)->isDead()){
            delete (*it);
            li.erase(it);
        }
        it++;
    }
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::checkFoodOverlap(double x, double y){
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if((*it)->isFood()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
            if(dist<=SPRITE_RADIUS*2){
                (*it)->setDead();
                return true;
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::checkCreateFoodOverlap(double x, double y){
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if((*it)->isFood() || (*it)->isPit()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
            if(dist<=SPRITE_RADIUS*2){
                (*it)->setDead();
                return true;
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::checkProjOverlap(double x, double y, int dmg){
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        double xc = (*it)->getX();
        double yc = (*it)->getY();
        double dist = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
        if(dist<=(SPRITE_RADIUS*2) && (*it)->isDamagable()){
            if((*it)->hasHP()){
                //decrement hp
                (*it)->decHP(dmg);
                return true;
            }
            else if(!(*it)->hasHP()){  //OR HP IS LESS THAN OR EQUAL TO 0
                (*it)->setDead();
                return true;
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::checkSocratesOverlap(double x, double y){
    double xc = m_playerPtr->getX();
    double yc = m_playerPtr->getY();
    double dist = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
    if(dist<=(SPRITE_RADIUS*2)){
        return true;
    }
    return false;
}

bool StudentWorld::canBacteriaMoveForward(double x, double y, int dir, int dist){
    x+=dist*cos(dir*3.14159265/180);
    y+=dist*sin(dir*3.14159265/180);
    double d = sqrt(((VIEW_WIDTH/2)-x)*((VIEW_WIDTH/2)-x)+((VIEW_HEIGHT/2)-y)*((VIEW_HEIGHT/2)-y));
    if(d>=VIEW_RADIUS){
        return false;
    }
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if((*it)->isDirt()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((xc-x)*(xc-x)+(yc-y)*(yc-y));
            if(dist<=SPRITE_WIDTH/2){
                return false;
            }
        }
        it++;
    }
    return true;
}

bool StudentWorld::getClosestFoodAngle(double x, double y, int &dir){
 
    //WRONG
    //WRONG
    //WRONG
    
    list<Actor*>::iterator it = li.begin();
    bool flag = false;
    double minDist = 128;
    while(it!=li.end()){
        if((*it)->isFood()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
            if(dist<=minDist){
                double degrees;
                flag = true;
                degrees = atan2((yc-(y)),(xc-(x)))*(180/3.14159265);
                dir = degrees;
                return flag;
            }
        }
        it++;
    }
    return flag;
}

void StudentWorld::restorePlayerHealth(){
    m_playerPtr->setHP(100);
}

void StudentWorld::hurtPlayerHealth(int num)
{
    m_playerPtr->setHP(m_playerPtr->getHP()-num);
}

void StudentWorld::addSpray(double x, double y, int dir)
{
    double xc = 2*SPRITE_RADIUS*cos(dir*3.14159265/180);
    double yc = 2*SPRITE_RADIUS*sin(dir*3.14159265/180);
    li.push_back(new Spray(x+xc, y+yc, dir, this));
}

void StudentWorld::addFlames(double x, double y, int dir){
    int newDir = dir;
    for(int i=0; i<16; i++){
        double xc = 2*SPRITE_RADIUS*cos(newDir*3.14159265/180);
        double yc = 2*SPRITE_RADIUS*sin(newDir*3.14159265/180);
        li.push_back(new Flame(x+xc, y+yc, newDir, this));
        newDir+=22;
    }
}

void StudentWorld::addPlayerFlame(){
    m_playerPtr->addFlame();
}

void StudentWorld::addBacteria(Actor* ptr){
    li.push_back(ptr);
}

double StudentWorld::getDistanceAndDirFromPlayer(double x, double y, int& dir){
    double px = m_playerPtr->getX();
    double py = m_playerPtr->getY();
    double degrees = atan2((py-(y)),(px-(x)))*(180/3.14159265);
    dir = degrees;
    double dist = sqrt((x-px)*(x-px)+(y-py)*(y-py));
    return dist;
}

bool StudentWorld::checkPitOverlap(double x, double y){
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if((*it)->isPit()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
            if(dist<=SPRITE_WIDTH){
                return true;
            }
        }
        it++;
    }
    return false;
}

bool StudentWorld::checkCreateDirtOverlap(double x, double y){
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        if((*it)->isFood() || (*it)->isPit()){
            double xc = (*it)->getX();
            double yc = (*it)->getY();
            double dist = sqrt((x-xc)*(x-xc)+(y-yc)*(y-yc));
            if(dist<=SPRITE_WIDTH){
                return true;
            }
        }
        it++;
    }
    return false;
}


void StudentWorld::cleanUp()
{
    delete m_playerPtr;
    list<Actor*>::iterator it = li.begin();
    while(it!=li.end()){
        delete (*it);
        it++;
    }
}

StudentWorld::~StudentWorld(){
    cleanUp();
}
