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
    
    //initialize dirt objects
    int numDirt = max(180-20*getLevel(), 20);
    for(int i=0; i<numDirt; i++){
        double a = randInt(0, 360);
        double r = 120*sqrt(randInt(0, 10000)/10000.0);
        double x = r*cos(a*3.14159265/180)+128;
        double y = r*sin(a*3.14159265/180)+128;
        li.push_back(new Dirt(x, y, this));
        li.back()->doSomething();
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    m_playerPtr->doSomething();
    
    
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
            //delete the actor and replace pointer with last pointer
            (*it) = li.back();
            li.pop_back();
            it--;
        }
        it++;
    }
    
    decLives();
    return GWSTATUS_CONTINUE_GAME;
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
    ;
}
