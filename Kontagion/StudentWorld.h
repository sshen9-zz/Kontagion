#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <list>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
class Socrates;
class Actor;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    virtual ~StudentWorld();
    void addSpray(double x, double y, int dir);
    void addFlames(double x, double y, int dir);
private:
    Socrates* m_playerPtr;
    std::list<Actor*> li;
};

#endif // STUDENTWORLD_H_
