#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
using namespace std;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir), m_bonus(1000), finishLevel(false)
    {}
    
    ~StudentWorld()
    {
        cleanUp();
    }
    
    virtual int init();
    
    virtual int move();
    
    
    virtual void cleanUp();
    
    Actor* WhatsAtThisSpot(int x, int y);
    
    Actor* GoodieAtThisSpot(int x, int y);
    
    Actor* SpecificItem(int x, int y, int imageID);        //gets a specific actor at a specific location
    
    
    
    Player* getPlayer()
    {
        return m_player;
    }
    
    void changeLevelStatus()
    {
        finishLevel = true;
    }
    
    
    void addSomethingtoVector(int x, int y, StudentWorld* s_world, int ID, Actor::Direction dir)
    {
        if(ID == IID_BULLET)
        {
            m_actors.push_back(new Bullet(x, y, s_world, dir));
        }
        
        if(ID == IID_KLEPTOBOT)
        {
            m_actors.push_back(new KleptoBot(IID_KLEPTOBOT, x, y, s_world, dir));
        }
        
        if(ID == IID_ANGRY_KLEPTOBOT)
        {
            m_actors.push_back(new AngryKleptoBot(x, y, s_world, dir));
        }
        
        if(ID == IID_JEWEL)
        {
            m_actors.push_back(new Jewel(x, y, s_world));
        }
        
        if(ID == IID_AMMO)
        {
            m_actors.push_back(new Ammo(x, y, s_world));
        }
        
        if(ID == IID_EXTRA_LIFE)
        {
            m_actors.push_back(new ExtraLife(x, y, s_world));
        }
        
        if(ID == IID_RESTORE_HEALTH)
        {
            m_actors.push_back(new RestoreHealth(x, y, s_world));
        }
    }
    
    
    int numberOfJewels();
    
    void setDisplayText();
    
    //int LoadALevel();
private:
    vector<Actor*> m_actors;
    Player* m_player;
    int m_bonus;   //have to do this
    bool finishLevel;
};


string FormatFunction(int score, int level, int lives, double health, int ammo, int bonus);

#endif // STUDENTWORLD_H_