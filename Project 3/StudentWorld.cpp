#include "StudentWorld.h"
#include "Level.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "stdlib.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
void StudentWorld:: cleanUp()
{
    vector<Actor*>::iterator p = m_actors.begin();
    for(; p < m_actors.end(); p++)
    {
        delete (*p);
    }
    m_actors.clear();
    delete m_player;
}
int StudentWorld::move()
{
    setDisplayText();
    m_player->doSomething();
    vector<Actor*>::iterator b = m_actors.begin();
    for(; b < m_actors.end(); b++)
    {
        if((*b)->stillAlive())
        {
            (*b)->doSomething();
            
        }
        else
        {
            delete(*b);
            b = m_actors.erase(b);
            
        }
        
        
    }
    
    if(m_bonus != 0)
        m_bonus--;
    
    if(getPlayer()->getHealth() == 0)
    {
        decLives();
        return GWSTATUS_PLAYER_DIED;
    }
    
    if(finishLevel == true)
    {
        if(m_bonus != 0)
            increaseScore(m_bonus);
        return GWSTATUS_FINISHED_LEVEL;
    }
    return GWSTATUS_CONTINUE_GAME;
    
    
}

Actor* StudentWorld:: WhatsAtThisSpot(int x, int y)
{
    if(getPlayer()->getX() == x && getPlayer()->getY() == y)
        return getPlayer();
    //loop though intil you find the thing at x,y
    vector<Actor*>::iterator b = m_actors.begin();
    for(; b < m_actors.end(); b++)
    {
        if((*b)->getX() == x && (*b)->getY() == y)
            return (*b);
    }
    
    
    
    return nullptr;
}

int StudentWorld::numberOfJewels()    //this allows the exit to know when it should set itself to visible
{
    int counter = 0;
    vector<Actor*>::iterator p = m_actors.begin();
    for(; p < m_actors. end(); p++)
    {
        if((*p)->getID() == IID_KLEPTOBOT || (*p)->getID() == IID_ANGRY_KLEPTOBOT)   //do this for angry kleptobots too
        {
            KleptoBot* kleptoPtr = dynamic_cast<KleptoBot*>(*p);
            if(kleptoPtr != nullptr && kleptoPtr->getGoodieID()== IID_JEWEL)
                counter++;
            AngryKleptoBot* angkleptoPtr = dynamic_cast<AngryKleptoBot*>(*p);
            if(angkleptoPtr != nullptr && angkleptoPtr->getGoodieID() == IID_JEWEL)
                counter++;
        }
        if((*p)->getID() == IID_JEWEL)
        {
            counter++;
        }
        
    }
    
    return counter;
}

Actor* StudentWorld:: SpecificItem(int x, int y, int imageID)         //gets a specific actor at a specific location
{
    vector<Actor*>::iterator p = m_actors.begin();
    for(; p < m_actors. end(); p++)
    {
        if((*p)->getX() == x && (*p)->getY() == y && (*p)->getID() == imageID)
        {
            return (*p);
        }
        
    }
    
    //what if the specific item is a player? the player wouldnt be contained in the vector so check for that
    if(getPlayer()->getX() == x && getPlayer()->getY() == y && getPlayer()->getID() == imageID)
        return getPlayer();
    
    
    return nullptr;
}


int StudentWorld::init()
{
    string	curLevel	=	"level0";
    curLevel += (char)(((int)'0')+getLevel());
    curLevel += ".dat";
    finishLevel = false;
    Level	lev(assetDirectory());
    Level::LoadResult result	=	lev.loadLevel(curLevel);
    if (result	==	Level::load_fail_file_not_found	|| result	==	Level:: load_fail_bad_format)
        return GWSTATUS_LEVEL_ERROR; //	something	bad	happened!
    if(getLevel() >= 100)
        return GWSTATUS_PLAYER_WON;
    
    
    for(int x = 0; x < VIEW_WIDTH; x++)
    {
        for(int y = 0; y < VIEW_HEIGHT; y++)
        {
            Level::MazeEntry item =	lev.getContentsOf(x, y);
            if(item	==	Level::player)
            {
                m_player = new Player(x, y, this, 20);
            }
            else if(item == Level::wall)
            {
                m_actors.push_back(new Wall(x, y, this));
            }
            else if(item == Level::boulder)
            {
                m_actors.push_back(new Boulder(x, y, this));
            }
            else if(item == Level::hole)
            {
                m_actors.push_back(new Hole(x, y, this));
            }
            else if(item == Level::jewel)
            {
                m_actors.push_back(new Jewel(x, y, this));
            }
            else if(item == Level::extra_life)
            {
                m_actors.push_back(new ExtraLife(x,y, this));
            }
            else if(item== Level::ammo)
            {
                m_actors.push_back(new Ammo(x,y , this));
            }
            else if(item == Level::exit)
            {
                m_actors.push_back(new Exit(x, y, this));
            }
            else if(item == Level::restore_health)
            {
                m_actors.push_back(new RestoreHealth(x, y, this));
            }
            else if(item == Level::horiz_snarlbot)   //start right
            {
                m_actors.push_back(new SnarlBot(x, y, this, Actor::right));
            }
            else if(item == Level::vert_snarlbot)   //start right
            {
                m_actors.push_back(new SnarlBot(x, y, this, Actor::down)); //starts down
            }
            else if(item == Level::kleptobot_factory)
            {
                m_actors.push_back(new KleptoBotFactory(x, y, this, false));
            }
            else if(item == Level::angry_kleptobot_factory)
            {
                m_actors.push_back(new KleptoBotFactory(x, y, this, true));
            }
            
        }
    }
    return GWSTATUS_CONTINUE_GAME;
    
}

void StudentWorld::setDisplayText()


{
    
    int score = getScore();
    
    int level = getLevel();
    
    unsigned int bonus = m_bonus;
    
    int livesLeft = getLives();
    
    
    
    string s = FormatFunction(score, level, livesLeft, m_player->getHealth(), m_player->getAmmo(), bonus);
    
    
    
    setGameStatText(s);
    
}

Actor* StudentWorld::GoodieAtThisSpot(int x, int y)
{
    vector<Actor*>::iterator b = m_actors.begin();
    for(; b < m_actors.end(); b++)
    {
        if((*b)->getX() == x && (*b)->getY() == y && (*b)->isGoodie())  //need this funtion incase a goodie and something else are on the same spot
            return (*b);
    }
    return nullptr;
}




string FormatFunction(int score, int level, int lives, double health, int ammo, int bonus)
{
    string s;
    
    ostringstream oss, oss1, oss2, oss3, oss4, oss5, oss6;
    
    s += "Score: ";
    
    oss.fill('0');
    
    oss << setw(7) << score;
    
    s += oss.str();
    
    
    oss1.fill('0');
    
    s += "  Level: ";
    
    oss1 << setw(2) << level;
    
    s += oss1.str();
    
    
    s += "  Lives: ";
    
    oss3 << setw(2) << lives;
    
    s += oss3.str();
    
    
    s += "  Health: ";
    
    oss4 << setw(3) << (health/20)*100;
    
    s += oss4.str();
    
    s += "%";
    
    
    s += "  Ammo: ";
    
    oss5 << setw(3) << ammo;
    
    s += oss5.str();
    
    
    s += "  Bonus: ";
    
    oss6 << setw(4) << bonus;
    
    s += oss6.str();
    
    
    return s;
    
}


//add bonus to score