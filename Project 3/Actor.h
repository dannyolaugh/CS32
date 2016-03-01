#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <string>
using namespace std;


class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(int imageID, int startX, int startY, StudentWorld* s_world, Direction dir = none, int health = -1, bool alive = true)
    :GraphObject(imageID, startX, startY, dir), m_world(s_world), isAlive(alive),m_health(health)
    {
    }
    
    StudentWorld* getWorld()
    {
        return m_world;
    }
    virtual void doSomething() = 0;
    
    virtual bool blocksPath()
    {
        return true;
    }
    virtual bool blocksBullet()   //maybe change
    {
        return false;    //most things dont block bullets
    }
    
    bool stillAlive()
    {
        return isAlive;
    }
    
    void setDead()
    {
        isAlive = false;
    }
    
    void setHealth()
    {
        m_health = 20;
    }
    void decHealth()
    {
        m_health-=2;
    }
    
    double getHealth()
    {
        return m_health;
    }
    
    virtual bool isGoodie()    //this is in order for kleptobots to know if they are on the same space as a goodie
    {
        return false;
    }
    
    virtual void damage();
    
    virtual ~Actor()
    {}
    
    
    
private:
    StudentWorld* m_world;    //pointer to the world
    bool isAlive;
    double m_health;
};

class Bullet: public Actor
{
public:
    Bullet(int x, int y, StudentWorld* s_world, Direction dir)
    :Actor(IID_BULLET, x, y, s_world, dir)
    {
        setVisible(true);
    }
    
    virtual void doSomething();
    
    virtual void damage()
    {}
    
    
    virtual bool blocksPath()
    {
        return false;
    }
    
    virtual ~Bullet()
    {}
};

class Robot: public Actor
{
public:
    Robot(int IID_NUMBER, int x, int y, StudentWorld* s_world, Direction dir = right, int health = 10)
    :Actor(IID_NUMBER, x, y, s_world, dir, health)
    {
        setTicks();
    }
    
    void setTicks();
    
    bool ClearPath();
    
    virtual bool blocksBullet()
    {
        return true;
    }
    
    
    bool wait();
    
    virtual ~Robot()
    {}
    
private:
    int m_ticks;
};

class SnarlBot: public Robot
{
public:
    SnarlBot(int x, int y, StudentWorld* s_world, Direction dir = right, int health = 10)
    :Robot(IID_SNARLBOT, x, y, s_world, dir, health)
    {
        setVisible(true);
    }
    
    
    virtual void doSomething();
    
    virtual ~SnarlBot()
    {}
    
};

class KleptoBotFactory: public Actor     //does this block a bullet
{
public:
    KleptoBotFactory(int x, int y, StudentWorld* s_world, bool angry)
    :Actor(IID_ROBOT_FACTORY, x, y, s_world), m_isAngry(angry)
    {
        setVisible(true);
    }
    
    void CreateRobot();  //function that take in a bool to determine if kleptobot is normal or angry
    
    bool getAngry()                //allows you to access this private variable
    {
        return m_isAngry;
    }
    virtual void doSomething();
    
    virtual ~KleptoBotFactory()
    {}
private:
    bool m_isAngry;
};


class KleptoBot: public Robot
{
public:
    KleptoBot(int ID, int x, int y, StudentWorld* s_world, Direction dir = right)
    :Robot(ID, x, y, s_world), m_distance(0), m_hasGoodie(false), goodie_id(0)  //distance is initially 0 but gets set by distanceBeforeTurning
    {
        setVisible(true);
        
    }
    
    virtual void doSomething();
    
    virtual bool blocksBullet()
    {
        return true;
    }
    
    void distanceBeforeTurning();
    
    int getDistance()
    {
        return m_distance;
    }
    
    void decDistance()
    {
        m_distance--;
    }
    
    bool getHasGoodie()
    {
        return m_hasGoodie;
    }
    
    void setHasGoodie(bool has)
    {
        m_hasGoodie = has;
    }
    
    
    void blockedIn(char a);
    
    
    void setGoodieID(int ID)
    {
        goodie_id = ID;
    }
    
    virtual int getGoodieID()
    {
        return goodie_id;
    }
    
    virtual void damage();
    
    Direction setRandomDirection();
    
    
    virtual ~KleptoBot()
    {}
private:
    int goodie_id;
    int  m_distance;
    bool m_hasGoodie;
    string trapped;
    
};

class AngryKleptoBot: public KleptoBot
{
public:
    AngryKleptoBot(int x, int y, StudentWorld* s_world, Direction dir = right)
    :KleptoBot(IID_ANGRY_KLEPTOBOT, x, y, s_world)
    {
        setVisible(true);
    }
    
    virtual void doSomething();
    
    
    virtual bool blocksBullet()
    {
        return true;
    }
    
    virtual ~AngryKleptoBot()
    {}
};

class Item: public Actor
{
public:
    Item(int IID_ITEM, int x, int y, StudentWorld* s_world)
    :Actor(IID_ITEM, x , y, s_world)
    {}
    
    virtual void damage()
    {}
    
    virtual bool isGoodie()
    {
        return true;
    }
    
    virtual ~Item()
    {}
    
    // you shouldnt be able to make a thing of type "Item"
};

class Goodie: public Item
{
public:
    Goodie(int IID_GOODIE, int x, int y, StudentWorld* s_world)
    :Item(IID_GOODIE, x, y, s_world)
    {}
    
    virtual void doSomething() = 0;
    
    virtual ~Goodie()
    {}
    
    //you shouldnt be able to make something of just type "Goodie"
};

class ExtraLife: public Goodie
{
public:
    ExtraLife(int x, int y, StudentWorld* s_world)
    :Goodie(IID_EXTRA_LIFE, x, y, s_world)
    {
        setVisible(true);
    }
    
    virtual bool blocksPath()  //does not block the player's past but does it block a robots?
    {
        return false;
    }
    
    virtual void doSomething();
    
    virtual ~ExtraLife()
    {}
    
    
};

class RestoreHealth:public Goodie
{
public:
    RestoreHealth(int x, int y, StudentWorld* s_world)
    :Goodie(IID_RESTORE_HEALTH, x, y, s_world)
    {
        setVisible(true);
    }
    
    virtual bool blocksPath()
    {
        return false;
    }
    
    virtual void doSomething();
    
    virtual ~RestoreHealth()
    {}
    
};

class Ammo: public Goodie
{
public:
    Ammo(int x, int y, StudentWorld* s_world)
    :Goodie(IID_AMMO, x, y, s_world)
    {
        setVisible(true);
    }
    
    virtual bool blocksPath()
    {
        return false;
    }
    
    virtual void doSomething();
    
    virtual ~Ammo()
    {}
};

class Wall: public Actor
{
public:
    Wall(int x,int y, StudentWorld* s_world)
    :Actor(IID_WALL, x, y, s_world)
    {
        setVisible(true);         //make visible
    }
    
    virtual void doSomething()
    {}
    
    virtual bool blocksBullet()
    {
        return true;
    }
    virtual void damage()
    {}
    
    virtual ~Wall()
    {}
    
private:
};

class Boulder: public Actor
{
public:
    Boulder(int x, int y, StudentWorld* s_world, Direction dir= none, int health = 10)
    :Actor(IID_BOULDER, x, y, s_world, dir, health)
    {
        setVisible(true);
    }
    
    virtual void doSomething()
    {}
    
    virtual bool blocksBullet()
    {
        return true;
    }
    
    virtual ~Boulder()
    {}
    
};

class Hole: public Actor
{
public:
    Hole(int x, int y, StudentWorld* s_world)
    :Actor(IID_HOLE, x, y, s_world)
    {
        setVisible(true);
    }
    virtual void doSomething();
    
    virtual void damage()
    {}
    
    virtual ~Hole()
    {}
};

class Jewel: public Goodie
{
public:
    Jewel(int startX, int startY, StudentWorld* s_world)
    :Goodie(IID_JEWEL, startX, startY, s_world)  //Jewel doesnt have a direction
    {
        setVisible(true);
    }
    
    virtual bool blocksPath()  //do i need this
    {
        return false;
    }
    
    virtual void doSomething();
    
    virtual ~Jewel()
    {}
    
};

class Exit: public Actor
{
public:
    Exit(int x, int y, StudentWorld* s_world)
    :Actor(IID_EXIT, x, y, s_world)
    {
        setVisible(false);
    }
    
    virtual void doSomething();
    
    bool blocksPath()   //THIS DOESNT BLOCK THE PLAYERS PATH BUT IT DOES BLOCK THE ROBOTS SO FIX THIS
    {
        return false;
    }
    
    virtual void damage()
    {}
    
    virtual ~Exit()
    {}
    
};


class Player: public Actor
{
public:
    Player(int startX, int startY, StudentWorld* s_world, int health)
    : Actor(IID_PLAYER, startX, startY, s_world,  right, health), m_ammo(20)
    {
        setVisible(true);         //make visible
    }
    
    virtual void doSomething();
    
    virtual bool blocksBullet()
    {
        return true;
    }
    
    void incAmmo()
    {
        m_ammo += 20;
    }
    
    void decAmmo()
    {
        ;
    }
    
    int getAmmo();
    
    virtual ~Player()
    {}
    
    
    
private:
    int m_ammo;
};

#endif // ACTOR_H_



//change blocksplayey to blockspath cause everything needs to be blocked
