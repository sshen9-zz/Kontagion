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

bool Actor::isDamagable(){
    return true;
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

bool Actor::isFood(){
    return false;
}

bool Actor::isDirt(){
    return false;
}

bool Actor::isPit(){
    return false;
}

void Actor::decHP(int dmg){
    return;
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

bool Dirt::isDirt(){
    return true;
}

Dirt::~Dirt(){
    ;
}

Food::Food(int startX, int startY, StudentWorld* ptr)
:Actor(IID_FOOD, startX, startY, 90, 1, ptr)
{
}

bool Food::isDamagable(){
    return false;
}

bool Food::isFood(){
    return true;
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

void LivingActor::decHP(int dmg){
    m_HP-=dmg;
    if(m_HP<=0){
        if(isPlayer()){
            getWorld()->decLives();
        }
        turnIntoFood();
        setDead();
        playSoundDie();
    }else{
        playSoundHurt();
    }
}

void LivingActor::turnIntoFood(){
    return;
}

bool LivingActor::isPlayer(){
    return false;
}

Socrates::Socrates(StudentWorld* ptr)
:LivingActor(IID_PLAYER, 0, VIEW_HEIGHT/2, 0, 0, ptr, 100)
{
    m_sprayCount = 20;
    m_flameCount = 5;
}

int Socrates::getSprays(){
    return m_sprayCount;
}

int Socrates::getFlames(){
    return m_flameCount;
}

bool Socrates::isPlayer(){
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
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
//                    m_flameCount-=1;
                    //playsound
                }
                break;
            case KEY_PRESS_SPACE:
                if(m_sprayCount>0){
                    getWorld()->addSpray(getX(), getY(), getDirection());
                    getWorld()->playSound(SOUND_PLAYER_SPRAY);
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

void Socrates::playSoundHurt(){
    getWorld()->playSound(SOUND_PLAYER_HURT);
}

void Socrates::playSoundDie(){
    getWorld()->playSound(SOUND_PLAYER_DIE);
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
    if(getWorld()->checkProjOverlap(getX(), getY(), getDamage())){
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
        getWorld()->increaseScore(250);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        //restore health
        getWorld()->restorePlayerHealth();
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
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->addPlayerFlame();
        return;
    }
    
    if(getLifespan()<=0){
        setDead();
    }
    
    decreaseLife();
}

//CHANGE HERE

ExtraLifeGoodie::ExtraLifeGoodie(int startX, int startY, StudentWorld* ptr)
:Goodie(IID_EXTRA_LIFE_GOODIE, startX, startY, ptr)
{

}

void ExtraLifeGoodie::doSomething(){
    if(isDead()){
        return;
    }
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->increaseScore(500);
        setDead();
        getWorld()->playSound(SOUND_GOT_GOODIE);
        getWorld()->incLives();
        return;
    }
    if(getLifespan()<=0){
        setDead();
    }

    decreaseLife();
}

Fungus::Fungus(int startX, int startY, StudentWorld* ptr)
:Goodie(IID_FUNGUS, startX, startY, ptr)
{
    
}

void Fungus::doSomething(){
    if(isDead()){
        return;
    }
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->increaseScore(-50);
        setDead();
        getWorld()->hurtPlayerHealth(20);
        return;
    }

    if(getLifespan()<=0){
        setDead();
    }

    decreaseLife();
    return;
}


Bacteria::Bacteria(int imageID, int startX, int startY, Direction startDirection, int depth, StudentWorld* ptr, int hp, int mpDist)
:LivingActor(imageID, startX, startY, startDirection, depth, ptr, hp)
{
    getWorld()->playSound(SOUND_BACTERIUM_BORN);
    m_foodCount = 0;
    m_mpDist = mpDist;
}

int Bacteria::getFoodCount(){
    return m_foodCount;
}

void Bacteria::resetFoodCount(){
    m_foodCount = 0;
}

void Bacteria::incFoodCount(){
    m_foodCount+=1;
}

int Bacteria::getMpDist(){
    return m_mpDist;
}

void Bacteria::decMpDist(){
    m_mpDist-=1;
}

void Bacteria::setMpDist(){
    m_mpDist = 10;
}

void Bacteria::turnIntoFood(){
    int num = randInt(1, 2);
    if(num == 1){
        getWorld()->addActor(new Food(getX(), getY(), getWorld()));
    }
}

Salmonella::Salmonella(int startX, int startY, StudentWorld* ptr)
:Bacteria(IID_SALMONELLA, startX, startY, 90, 0, ptr, 4, 0)
{
    
}

void Salmonella::playSoundHurt(){
    getWorld()->playSound(SOUND_SALMONELLA_HURT);
}

void Salmonella::playSoundDie(){
    getWorld()->playSound(SOUND_SALMONELLA_DIE);
}

void Salmonella::MPdistOrGetFoodAngle(){
    //FUNCTION TO HELP SIMPLY STEPS 6 AND 7 BECAUSE IT IS REPETITIVE
    
    if(getMpDist()>0){
        decMpDist();
        if(getWorld()->canBacteriaMoveForward(getX(), getY(), getDirection(), 3)){
            double x = getX()+ 3*cos(getDirection()*3.14159265/180);
            double y = getY()+ 3*sin(getDirection()*3.14159265/180);
            moveTo(x, y);
        }else{
            setDirection(randInt(0, 359));
            setMpDist();
        }
        return;
    }else{
        int dir;
        if(getWorld()->getClosestFoodAngle(getX(), getY(), dir)){
            setDirection(dir);
            if(getWorld()->canBacteriaMoveForward(getX(), getY(), dir, 3)){
                double x = getX()+ 3*cos(getDirection()*3.14159265/180);
                double y = getY()+ 3*sin(getDirection()*3.14159265/180);
                moveTo(x, y);
                return;
            }else{
                setDirection(randInt(0, 359));
                setMpDist();
                return;
            }
        }else{
            setDirection(randInt(0, 359));
            setMpDist();
            return;
        }
    }
}

void Salmonella::doSomething(){
    if(isDead()){
        return;
    }
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->hurtPlayerHealth(1);
    }else if(getFoodCount()==3){
        double newx = getX();
        double newy = getY();
        if(getX()<VIEW_WIDTH/2){
            newx = getX()+SPRITE_RADIUS;
        }else if(getX()>VIEW_WIDTH/2){
            newx = getX()-SPRITE_RADIUS;
        }
        if(getY()<VIEW_HEIGHT/2){
            newy = getY()+SPRITE_RADIUS;
        }else if(getY()>VIEW_HEIGHT/2){
            newy = getY()-SPRITE_RADIUS;
        }
        //add new salmonella at coordinate
        getWorld()->addActor(new Salmonella(newx, newy, getWorld()));
        resetFoodCount();
    }else if(getWorld()->checkFoodOverlap(getX(), getY())){
        incFoodCount();
    }
    
    MPdistOrGetFoodAngle();
}

AggressiveSalmonella::AggressiveSalmonella(int startX, int startY, StudentWorld* ptr)
:Salmonella(startX, startY, ptr)
{
    //aggressive salmonella starts out with 10hp instead of 4
    setHP(10);
}

void AggressiveSalmonella::doSomething()
{
    if(isDead()){
        return;
    }
    
    int dir;
    double distance = getWorld()->getDistanceAndDirFromPlayer(getX(), getY(), dir);
    if(distance<=72){
        //move IN THE DIRECTION OF PLAYER
        if(getWorld()->canBacteriaMoveForward(getX(), getY(), dir, 3)){
            //if it can move forward, move forward
            setDirection(dir);
            double x = getX()+ 3*cos(getDirection()*3.14159265/180);
            double y = getY()+ 3*sin(getDirection()*3.14159265/180);
            moveTo(x, y);
        }
        if(getWorld()->checkSocratesOverlap(getX(), getY())){
            getWorld()->hurtPlayerHealth(2);
            return;
        }
        
        //check if ate 3 food
        if(getFoodCount() == 3){
            double newx = getX();
            double newy = getY();
            if(getX()<VIEW_WIDTH/2){
                newx = getX()+SPRITE_RADIUS;
            }else if(getX()>VIEW_WIDTH/2){
                newx = getX()-SPRITE_RADIUS;
            }
            if(getY()<VIEW_HEIGHT/2){
                newy = getY()+SPRITE_RADIUS;
            }else if(getY()>VIEW_HEIGHT/2){
                newy = getY()-SPRITE_RADIUS;
            }
            getWorld()->addActor(new AggressiveSalmonella(newx, newy, getWorld()));
            resetFoodCount();
            return;
        }
        
        //check food overlap
        if(getWorld()->checkFoodOverlap(getX(), getY())){
            incFoodCount();
        }
        return;
    }
    
    //DONE WITH 2
    
    //if distance is not less than 72:
    
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->hurtPlayerHealth(2);
        MPdistOrGetFoodAngle();
    }
    
    //STEP 4
    if(getFoodCount() == 3){
        double newx = getX();
        double newy = getY();
        if(getX()<VIEW_WIDTH/2){
            newx = getX()+SPRITE_RADIUS;
        }else if(getX()>VIEW_WIDTH/2){
            newx = getX()-SPRITE_RADIUS;
        }
        if(getY()<VIEW_HEIGHT/2){
            newy = getY()+SPRITE_RADIUS;
        }else if(getY()>VIEW_HEIGHT/2){
            newy = getY()-SPRITE_RADIUS;
        }
        getWorld()->addActor(new AggressiveSalmonella(newx, newy, getWorld()));
        resetFoodCount();
        
        //Then skip to step 6 (unless instructed not to by step 2c, in which case just return immediately).
        MPdistOrGetFoodAngle();
    }
    
    //STEP 5
    if(getWorld()->checkFoodOverlap(getX(), getY())){
        incFoodCount();
    }
    
    //STEP 6
    MPdistOrGetFoodAngle();
}

//ECOLI

Ecoli::Ecoli(int startX, int startY, StudentWorld* ptr)
:Bacteria(IID_ECOLI, startX, startY, 90, 0, ptr, 5, 0)
{
    
}

void Ecoli::playSoundHurt(){
    getWorld()->playSound(SOUND_ECOLI_HURT);
}

void Ecoli::playSoundDie(){
    getWorld()->playSound(SOUND_ECOLI_DIE);
}

void Ecoli::EcoliChasePlayer(double x, double y){
    int dir;
    double dist = getWorld()->getDistanceAndDirFromPlayer(x, y, dir);
    if(dist<=256){
        for(int i=0; i<10; i++){
            if(getWorld()->canBacteriaMoveForward(x, y, dir, 2)){
                setDirection(dir);
                double x = getX()+ 2*cos(getDirection()*3.14159265/180);
                double y = getY()+ 2*sin(getDirection()*3.14159265/180);
                moveTo(x, y);
                return;
            }else{
                dir+=10;
                if(dir>=360){
                    dir-=360;
                }
            }
        }
    }
}

void Ecoli::doSomething(){
    if(isDead()){
        return;
    }
    
    if(getWorld()->checkSocratesOverlap(getX(), getY())){
        getWorld()->hurtPlayerHealth(4);
        //skip to step 5
        EcoliChasePlayer(getX(), getY());
        return;
    }
    
    if(getFoodCount() == 3){
        double newx = getX();
        double newy = getY();
        if(getX()<VIEW_WIDTH/2){
            newx = getX()+SPRITE_RADIUS;
        }else if(getX()>VIEW_WIDTH/2){
            newx = getX()-SPRITE_RADIUS;
        }
        if(getY()<VIEW_HEIGHT/2){
            newy = getY()+SPRITE_RADIUS;
        }else if(getY()>VIEW_HEIGHT/2){
            newy = getY()-SPRITE_RADIUS;
        }
        getWorld()->addActor(new Ecoli(newx, newy, getWorld()));
        resetFoodCount();
        //skip to step 5
        EcoliChasePlayer(getX(), getY());
        return;
    }
    
    if(getWorld()->checkFoodOverlap(getX(), getY())){
        incFoodCount();
    }
    
    EcoliChasePlayer(getX(), getY());
}

Pit::Pit(int startX, int startY, StudentWorld* ptr)
:Actor(IID_PIT, startX, startY, 0, 1, ptr)
{
    m_EcoliLeft = 2;
    m_SalmonellaLeft = 5;
    m_AggressiveSalmonellaLeft = 3;
    m_sumBacteria = 10;
}

bool Pit::isPit(){
    return true;
}

bool Pit::isDamagable(){
    return false;
}

int Pit::getEcoli(){
    return m_EcoliLeft;
}

int Pit::getSalmonella(){
    return m_SalmonellaLeft;
}

int Pit::getAggressiveSalmonella(){
    return m_AggressiveSalmonellaLeft;
}

int Pit::getSum(){
    return m_sumBacteria;
}

bool Pit::emittedAll(){
    return (getSum() == 0);
}

void Pit::decEcoli(){
    m_EcoliLeft-=1;
}

void Pit::decSalmonella(){
    m_SalmonellaLeft-=1;
}

void Pit::decAggressiveSalmonella(){
    m_AggressiveSalmonellaLeft-=1;
}

void Pit::decSum(){
    m_sumBacteria-=1;
}

void Pit::doSomething(){
    if(emittedAll()){
        //inform studentworld
        setDead();
    }else{
        int num = randInt(1, 50);
        //1 in 50 chance
        if(num == 25){
            //PLAY SOUNDS
            while(true){
                int n = randInt(1, 3);
                if(n == 1 && getEcoli()!=0){
                    //create new ecoli
                    getWorld()->addActor(new Ecoli(getX(), getY(), getWorld()));
                    decEcoli();
                    decSum();
                    return;
                }else if(n==2 && getSalmonella()!=0){
                    //create salmonella
                    getWorld()->addActor(new Salmonella(getX(), getY(), getWorld()));
                    decSalmonella();
                    decSum();
                    return;
                }else if(n==3 && getAggressiveSalmonella()!=0){
                    //create aggressive
                    getWorld()->addActor(new AggressiveSalmonella(getX(), getY(), getWorld()));
                    decAggressiveSalmonella();
                    decSum();
                    return;
                }
            }
        }
    }
    
}



