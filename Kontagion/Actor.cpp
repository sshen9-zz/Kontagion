#include "Actor.h"
#include "StudentWorld.h"
#include "GameConstants.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


Actor::Actor(int imageID, int startX, int startY, Direction startDirection, int depth)
:GraphObject(imageID, startX, startY, startDirection, depth)
{
    
}

Dirt::Dirt(int imageID, int startX, int startY, Direction startDirection, int depth)
:Actor(imageID, startX, startY, startDirection, depth)
{
    
}
