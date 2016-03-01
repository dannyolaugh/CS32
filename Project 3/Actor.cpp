#include "Actor.h"
#include "StudentWorld.h"
#include <iostream>
#include <string>
using namespace std;
// Students:  Add code to this file (if you wish), Actor.h, StudentWorld.h, and StudentWorld.cpp

void Player::doSomething()
{
    int valueOfKey = 0;
    if(getWorld()->getKey(valueOfKey))
    {
        
        // user hit a key this tick!
        switch (valueOfKey)
        {
            case KEY_PRESS_UP:     //if user presses up player should change direction to up
            {
                setDirection(up);
                
                if(getWorld()->WhatsAtThisSpot(getX(), getY()+1) != nullptr)  //dont want to continue this if null
                {
                    if(getWorld()->WhatsAtThisSpot(getX(),getY()+1)->getID() == IID_BOULDER) //if a boulder
                    {
                        if(getWorld()->WhatsAtThisSpot(getX(), getY()+2) == nullptr || getWorld()->WhatsAtThisSpot(getX(), getY()+2)->getID() == IID_HOLE)
                        {
                            getWorld()->WhatsAtThisSpot(getX(), getY()+1)->moveTo(getX(), getY()+2);  //if a hole comes next you move boulder
                            moveTo(getX(), getY()+1); //move player
                            break;
                        }
                    }
                    
                    
                }
                
                Actor* ptr = getWorld()->WhatsAtThisSpot(getX(), getY()+1);
                if(getWorld()->SpecificItem(getX(), getY()+1, IID_SNARLBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX(), getY()+1, IID_KLEPTOBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
                    break;
                
                else if(ptr != nullptr && ptr->blocksPath())
                {
                    break;
                }
                else
                {
                    moveTo(getX(), getY()+1);
                }
                
                break;
            }
            case KEY_PRESS_DOWN:
            {
                setDirection(down);
                
                if(getWorld()->WhatsAtThisSpot(getX(), getY()-1) != nullptr)
                {
                    if(getWorld()->WhatsAtThisSpot(getX(),getY()-1)->getID() == IID_BOULDER)
                    {
                        if(getWorld()->WhatsAtThisSpot(getX(), getY()-2) == nullptr || getWorld()->WhatsAtThisSpot(getX(), getY()-2)->getID() == IID_HOLE)
                        {
                            getWorld()->WhatsAtThisSpot(getX(), getY()-1)->moveTo(getX(), getY()-2);
                            moveTo(getX(), getY()-1);
                            break;
                        }
                    }
                    
                }
                
                Actor* ptr = getWorld()->WhatsAtThisSpot(getX(), getY()-1);
                if(getWorld()->SpecificItem(getX(), getY()-1, IID_SNARLBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX(), getY()-1, IID_KLEPTOBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
                    break;
                
                else if(ptr != nullptr && ptr->blocksPath())
                {
                    break;
                }
                else
                {
                    moveTo(getX(), getY()-1);
                }
                break;
            }
            case KEY_PRESS_LEFT:
            {
                setDirection(left);
                
                if(getWorld()->WhatsAtThisSpot(getX()-1, getY()) != nullptr)
                {
                    if(getWorld()->WhatsAtThisSpot(getX()-1,getY())->getID() == IID_BOULDER)
                    {
                        if(getWorld()->WhatsAtThisSpot(getX()-2, getY()) == nullptr || getWorld()->WhatsAtThisSpot(getX()-2, getY())->getID() == IID_HOLE)
                        {
                            getWorld()->WhatsAtThisSpot(getX()-1, getY())->moveTo(getX()-2, getY());
                            moveTo(getX()-1, getY());
                            break;
                        }
                    }
                }
                
                Actor* ptr = getWorld()->WhatsAtThisSpot(getX()-1, getY());
                
                if(getWorld()->SpecificItem(getX()-1, getY(), IID_SNARLBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX()-1, getY(), IID_KLEPTOBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                    break;
                else if(ptr != nullptr && ptr->blocksPath())
                {
                    break;
                }
                else
                {
                    moveTo(getX()-1, getY());
                }
                break;
            }
            case KEY_PRESS_RIGHT:
            {
                setDirection(right);
                
                if(getWorld()->WhatsAtThisSpot(getX()+1, getY()) != nullptr)
                {
                    if(getWorld()->WhatsAtThisSpot(getX()+1,getY())->getID() == IID_BOULDER)
                    {
                        if(getWorld()->WhatsAtThisSpot(getX()+2, getY()) == nullptr || getWorld()->WhatsAtThisSpot(getX()+2, getY())->getID() == IID_HOLE)
                        {
                            getWorld()->WhatsAtThisSpot(getX()+1, getY())->moveTo(getX()+2, getY());
                            moveTo(getX()+1, getY());
                            break;
                        }
                    }
                }
                
                Actor* ptr = getWorld()->WhatsAtThisSpot(getX()+1, getY());
                if(ptr != nullptr && ptr->blocksPath())
                {
                    break;
                }
                if(getWorld()->SpecificItem(getX()+1, getY(), IID_SNARLBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX()+1, getY(), IID_KLEPTOBOT) != nullptr)
                    break;
                else if(getWorld()->SpecificItem(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                    break;
                else
                {
                    moveTo(getX()+1, getY());
                }
                break;
            }
            case KEY_PRESS_SPACE:  //this shoots a bullet
            {
                //dynamically allocate a new bullet
                //add bullet to m_actors vectors
                if(getAmmo() == 0)
                    break;
                m_ammo--;
                
                
                if(getDirection() == up)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()+1, getWorld(), IID_BULLET, getDirection());
                }
                else if(getDirection() == down)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()-1, getWorld(), IID_BULLET, getDirection());
                }
                else if(getDirection() == right)
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->addSomethingtoVector(getX()+1, getY(), getWorld(), IID_BULLET, getDirection());
                }
                else
                {
                    getWorld()->playSound(SOUND_PLAYER_FIRE);
                    getWorld()->addSomethingtoVector(getX()-1, getY(), getWorld(), IID_BULLET, getDirection());
                }
                
                break;
            }
            case KEY_PRESS_ESCAPE:
            {
                setDead();
            }
        }
        
    }
    
    
}

int Player::getAmmo()
{
    return m_ammo;
}


void Hole::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_BOULDER) != nullptr)
        {
            setDead();
            getWorld()->SpecificItem(getX(), getY(), IID_BOULDER)->setDead();
        }
    }
    
}

void Jewel::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER))
        {
            //change score
            getWorld()->increaseScore(50);
            setDead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
        }
    }
    
}

void ExtraLife::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER))
        {
            getWorld()->increaseScore(1000);
            getWorld()->incLives();
            setDead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
        }
    }
    
}

void RestoreHealth::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER))
        {
            getWorld()->increaseScore(500);     //increase score
            getWorld()->getPlayer()->setHealth();           //set health back to 20
            setDead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
        }
    }
    
}

void Ammo::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER))
        {
            getWorld()->increaseScore(100);     //increase score
            getWorld()->getPlayer()->incAmmo();
            setDead();
            getWorld()->playSound(SOUND_GOT_GOODIE);
        }
    }
}

void Exit::doSomething()
{
    if(getWorld()->numberOfJewels() == 0)
    {
        setVisible(true);
    }
    if(isVisible() && getWorld()->SpecificItem(getX(), getY(), IID_PLAYER))
    {
        getWorld()->playSound(SOUND_FINISHED_LEVEL);
        getWorld()->changeLevelStatus();
    }
}

void SnarlBot::doSomething()
{
    if(!stillAlive())
        return;
    else if(!wait())
        return;
    else
    {
        if(getDirection()==right)
        {
            if((getY() == getWorld()->getPlayer()->getY()) && (getX() < getWorld()->getPlayer()->getX()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX()+1, getY(), getWorld(), IID_BULLET, right);
                    return;
                }
            }
            if(getWorld()->WhatsAtThisSpot(getX()+1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()+1, getY())->blocksPath())
            {
                setDirection(left);
            }
            else if(getWorld()->getPlayer()->getX() == getX()+1 && getWorld()->getPlayer()->getY() == getY())
            {
                setDirection(left);
            }
            else
                moveTo(getX()+1, getY());
        }
        
        else if(getDirection()==left)
        {
            if((getY() == getWorld()->getPlayer()->getY()) && (getX() > getWorld()->getPlayer()->getX()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX()-1, getY(), getWorld(), IID_BULLET, left);
                    return;
                }
            }
            if(getWorld()->WhatsAtThisSpot(getX()-1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()-1, getY())->blocksPath())
            {
                setDirection(right);
            }
            else if(getWorld()->getPlayer()->getX() == getX()-1 && getWorld()->getPlayer()->getY() == getY())
            {
                setDirection(right);
            }
            else
                moveTo(getX()-1, getY());
        }
        
        else if(getDirection()==up)
        {
            if((getX() == getWorld()->getPlayer()->getX()) && (getY() < getWorld()->getPlayer()->getY()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()+1, getWorld(), IID_BULLET, up);
                    return;
                }
            }
            if(getWorld()->WhatsAtThisSpot(getX(), getY()+1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()+1)->blocksPath())
            {
                setDirection(down);
            }
            else if(getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()+1)
            {
                setDirection(down);
            }
            else
                moveTo(getX(), getY()+1);
        }
        
        else if(getDirection()==down)
        {
            if((getX() == getWorld()->getPlayer()->getX()) && (getY() > getWorld()->getPlayer()->getY()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()-1, getWorld(), IID_BULLET, down);
                    return;
                }
            }
            if(getWorld()->WhatsAtThisSpot(getX(), getY()-1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()-1)->blocksPath())
            {
                setDirection(up);
            }
            else if(getWorld()->getPlayer()->getX() == getX() && getWorld()->getPlayer()->getY() == getY()-1)
            {
                setDirection(up);    //if robot runs into the player it must switch direction
            }
            else
                moveTo(getX(), getY()-1);
        }
        
    }
    
}

void AngryKleptoBot::doSomething()
{
    if(!stillAlive())
        return;
    else if(!wait())
    {
        return;
    }
    else
    {
        if(getWorld()->GoodieAtThisSpot(getX(), getY()) && !getHasGoodie())   //only pick up if a goodie is at this spot and the robot doesnt already have a goodie
        {
            int x = rand()%10 + 1;    //1 int 10 chance of picking it up
            
            if(x == 1)
            {
                if(getWorld()->SpecificItem(getX(), getY(),IID_AMMO) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_AMMO)->setDead();
                    setHasGoodie(true);    //robot should now know that it has a goodie
                    setGoodieID(IID_AMMO);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    
                }
                
                else if(getWorld()->SpecificItem(getX(), getY(),IID_EXTRA_LIFE) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_EXTRA_LIFE)->setDead();
                    setHasGoodie(true);
                    setGoodieID(IID_EXTRA_LIFE);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    
                }
                
                
                else if(getWorld()->SpecificItem(getX(), getY(), IID_RESTORE_HEALTH) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_RESTORE_HEALTH)->setDead();
                    setHasGoodie(true);
                    setGoodieID(IID_RESTORE_HEALTH);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    
                }
                
                
            }
        }
        
        if(getDirection()==right)
        {
            if((getY() == getWorld()->getPlayer()->getY()) && (getX() < getWorld()->getPlayer()->getX()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX()+1, getY(), getWorld(), IID_BULLET, right);
                    return;
                }
            }
            
            else
            {
                if(getDistance() == 0)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                if(getWorld()->WhatsAtThisSpot(getX()+1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()+1, getY())->blocksPath())
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX()+1, getY(), IID_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX()+1, getY(), IID_SNARLBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else
                {
                    moveTo(getX()+1, getY());
                    decDistance();
                }
                return;
            }
        }
        
        else if(getDirection()==left)
        {
            if((getY() == getWorld()->getPlayer()->getY()) && (getX() > getWorld()->getPlayer()->getX()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX()-1, getY(), getWorld(), IID_BULLET, left);
                    return;
                }
            }
            else
            {
                if(getDistance() == 0)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                if(getWorld()->WhatsAtThisSpot(getX()-1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()-1, getY())->blocksPath())
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                    
                }
                else if(getWorld()->SpecificItem(getX()-1, getY(), IID_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX()-1, getY(), IID_SNARLBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else
                {
                    moveTo(getX()-1, getY());
                    decDistance();
                }
                return;
            }
        }
        
        else if(getDirection()==up)
        {
            if((getX() == getWorld()->getPlayer()->getX()) && (getY() < getWorld()->getPlayer()->getY()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()+1, getWorld(), IID_BULLET, up);
                    return;
                }
            }
            
            else
            {
                if(getDistance() == 0)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                if(getWorld()->WhatsAtThisSpot(getX(), getY()+1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()+1)->blocksPath())
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()+1, IID_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()+1, IID_SNARLBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else
                {
                    moveTo(getX(), getY()+1);
                    decDistance();
                }
                return;
            }
        }
        
        else if(getDirection()==down)
        {
            if((getX() == getWorld()->getPlayer()->getX()) && (getY() > getWorld()->getPlayer()->getY()))
            {
                if(ClearPath())
                {
                    getWorld()->playSound(SOUND_ENEMY_FIRE);
                    getWorld()->addSomethingtoVector(getX(), getY()-1, getWorld(), IID_BULLET, down);
                    return;
                }
            }
            
            else
            {
                if(getDistance() == 0)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                if(getWorld()->WhatsAtThisSpot(getX(), getY()-1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()-1)->blocksPath())
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()-1, IID_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else if(getWorld()->SpecificItem(getX(), getY()-1, IID_SNARLBOT) != nullptr)
                {
                    setDirection(setRandomDirection());
                    distanceBeforeTurning();
                }
                else
                {
                    moveTo(getX(), getY()-1);
                    decDistance();
                }
            }
        }
    }
    
    
}
void Bullet::doSomething()
{
    if(!stillAlive())
        return;
    else
    {
        if(getWorld()->WhatsAtThisSpot(getX(), getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY())->blocksBullet())
        {
            getWorld()->WhatsAtThisSpot(getX(), getY())->damage();
            setDead();
            return;
        }
        else if(getWorld()->SpecificItem(getX(), getY(), IID_SNARLBOT) != nullptr)
        {
            getWorld()->SpecificItem(getX(), getY(), IID_SNARLBOT)->damage();
            setDead();
            return;
        }
        else if(getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT) != nullptr)
        {
            getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT)->damage();
            setDead();
            return;
        }
        else if(getWorld()->SpecificItem(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
        {
            getWorld()->SpecificItem(getX(), getY(), IID_ANGRY_KLEPTOBOT)->damage();
            setDead();
            return;
        }
        else if(getDirection()==right)
        {
            if(getWorld()->WhatsAtThisSpot(getX()+1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()+1, getY())->blocksBullet())
            {
                getWorld()->WhatsAtThisSpot(getX()+1, getY())->damage();  //call damage function at whatever is at that spot
                setDead();   //kill the bullet
                return;
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_SNARLBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()+1, getY(), IID_SNARLBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()+1, getY(), IID_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()+1, getY(), IID_ANGRY_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else
                moveTo(getX()+1, getY());
        }
        else if(getDirection()==left)
        {
            if(getWorld()->WhatsAtThisSpot(getX()-1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()-1, getY())->blocksBullet())
            {
                getWorld()->WhatsAtThisSpot(getX()-1, getY())->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_SNARLBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()-1, getY(), IID_SNARLBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()-1, getY(), IID_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX()-1, getY(), IID_ANGRY_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else
                moveTo(getX()-1, getY());
        }
        else if(getDirection()==up)
        {
            if(getWorld()->WhatsAtThisSpot(getX(), getY()+1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()+1)->blocksBullet())
            {
                getWorld()->WhatsAtThisSpot(getX(), getY()+1)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_SNARLBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()+1, IID_SNARLBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()+1, IID_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()+1, IID_ANGRY_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else
                moveTo(getX(), getY()+1);
        }
        else if(getDirection()==down)
        {
            if(getWorld()->WhatsAtThisSpot(getX(), getY()-1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()-1)->blocksBullet())
            {
                getWorld()->WhatsAtThisSpot(getX(), getY()-1)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_SNARLBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()-1, IID_SNARLBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()-1, IID_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                getWorld()->SpecificItem(getX(), getY()-1, IID_ANGRY_KLEPTOBOT)->damage();
                setDead();
                return;
            }
            else
                moveTo(getX(), getY()-1);
        }
    }
    
}

bool Robot::ClearPath()
{
    if(getDirection()==right)
    {
        for(int i = getX()+1; i < getWorld()->getPlayer()->getX(); i++)
        {
            if(getWorld()->WhatsAtThisSpot(i, getY()) != nullptr && getWorld()->WhatsAtThisSpot(i, getY())->blocksBullet())
                return false;
        }
    }
    else if(getDirection()==left)
    {
        for(int i = getX()-1; i > getWorld()->getPlayer()->getX(); i--)
        {
            if(getWorld()->WhatsAtThisSpot(i, getY()) != nullptr && getWorld()->WhatsAtThisSpot(i, getY())->blocksBullet())
                return false;
        }
    }
    else if(getDirection()==up)
    {
        for(int j = getY()+1; j < getWorld()->getPlayer()->getY(); j++)
        {
            if(getWorld()->WhatsAtThisSpot(getX(), j) != nullptr && getWorld()->WhatsAtThisSpot(getX(), j)->blocksBullet())
                return false;
        }
    }
    else if(getDirection()==down)
    {
        for(int j = getY()-1; j > getWorld()->getPlayer()->getY(); j--)
        {
            if(getWorld()->WhatsAtThisSpot(getX(), j) != nullptr && getWorld()->WhatsAtThisSpot(getX(), j)->blocksBullet())
                return false;
        }
    }
    return true;
}

void KleptoBotFactory::doSomething()
{
    int counter = 0;
    if(getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT) != nullptr)
    {
        return;
    }
    if(getWorld()->SpecificItem(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
    {
        return;
    }
    for(int x = getX(); x < VIEW_WIDTH && x <= getX()+3; x++)
    {
        for(int y = getY(); y <VIEW_HEIGHT && y <= getY()+3; y++)
        {
            if(getWorld()->SpecificItem(x, y, IID_KLEPTOBOT))
            {
                counter++;
            }
            if(getWorld()->SpecificItem(x, y, IID_ANGRY_KLEPTOBOT))
            {
                counter++;
            }
        }
        for(int y = getY()-1; y > 0 &&  y >= getY()-3; y--)
        {
            if(getWorld()->SpecificItem(x, y, IID_KLEPTOBOT))
            {
                counter++;
            }
            if(getWorld()->SpecificItem(x, y, IID_ANGRY_KLEPTOBOT))
            {
                counter++;
            }
        }
    }
    for(int x = getX()-1; x > 0 && x >= getX()-3; x--)
    {
        for(int y = getY(); y <VIEW_HEIGHT && y <= getY()+3; y++)
        {
            if(getWorld()->SpecificItem(x, y, IID_KLEPTOBOT))
            {
                counter++;
            }
            if(getWorld()->SpecificItem(x, y, IID_ANGRY_KLEPTOBOT))
            {
                counter++;
            }
        }
        for(int y = getY()-1; y >0 &&  y >= getY()-3; y--)
        {
            if(getWorld()->SpecificItem(x, y, IID_KLEPTOBOT))
            {
                counter++;
            }
            if(getWorld()->SpecificItem(x, y, IID_ANGRY_KLEPTOBOT))
            {
                counter++;
            }
        }
    }
    if(counter < 3)
    {
        if((rand()%50 +1) == 25)
        {
            CreateRobot();
            getWorld()->playSound(SOUND_ROBOT_BORN);
        }
    }
}

void Actor:: damage()
{
    m_health-=2;
    if(getHealth() <= 0)
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_SNARLBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_DIE);
            getWorld()->increaseScore(100);
        }
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER) != nullptr)
        {
            getWorld()->playSound(SOUND_PLAYER_DIE);
        }
        
        setDead();
    }
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_SNARLBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_IMPACT);
        }
        if(getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_IMPACT);
        }
        if(getWorld()->SpecificItem(getX(), getY(), IID_PLAYER) != nullptr)
        {
            getWorld()->playSound(SOUND_PLAYER_IMPACT);
        }
        
    }
}



void Robot::setTicks()
{
    
    m_ticks = (28 - getWorld()->getLevel()) / 4; // levelNumber is the current
    // level number (0, 1, 2, etc.)
    if (m_ticks < 3)
        m_ticks = 3; // no KleptoBot moves more frequently than this
}

bool Robot::wait()
{
    
    m_ticks--;
    if(m_ticks == 0)
    {
        setTicks();
        
        return true;
    }
    else
        return false;
}

void KleptoBot::distanceBeforeTurning()   //if the kleptobot is trapped in will just randomly change direction but if its blocked on one side
{                                           //it will keep randomly generating a new direction until it find a way it can move
    
    switch(rand()%6 + 1)
    {
        case 1:
            m_distance = 1;
            break;
        case 2:
            m_distance = 2;
            break;
        case 3:
            m_distance = 3;
            break;
        case 4:
            m_distance = 4;
            break;
        case 5:
            m_distance = 5;
            break;
        case 6:
            m_distance = 6;
            
    }
}

void KleptoBot::damage()
{
    decHealth();
    if(getHealth() <= 0)
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_DIE);
            getWorld()->addSomethingtoVector(getX(), getY(), getWorld(), getGoodieID(), none);
            getWorld()->increaseScore(10);
        }
        if(getWorld()->SpecificItem(getX(), getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_DIE);
            getWorld()->addSomethingtoVector(getX(), getY(), getWorld(), getGoodieID(), none);
            getWorld()->increaseScore(20);
        }
        setDead();
    }
    else
    {
        if(getWorld()->SpecificItem(getX(), getY(), IID_KLEPTOBOT) != nullptr)
        {
            getWorld()->playSound(SOUND_ROBOT_IMPACT);
        }
    }
    
}

Actor::Direction KleptoBot::setRandomDirection()
{
    int x = rand()%4 + 1;
    switch(x)
    {
        case 1:
            return up;
        case 2:
            return down;
        case 3:
            return left;
        case 4:
            return right;
    }
    return left;
    
}

void KleptoBot::doSomething()
{
    if(!stillAlive())
        return;
    else if(!wait())
    {
        return;
    }
    else
    {
        if(getWorld()->GoodieAtThisSpot(getX(), getY()) && !getHasGoodie())   //only pick up if a goodie is at this spot and the robot doesnt already have a goodie
        {
            int x = rand()%10 + 1;    //1 int 10 chance of picking it up
            
            if(x == 1)
            {
                if(getWorld()->SpecificItem(getX(), getY(),IID_AMMO) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_AMMO)->setDead();
                    setHasGoodie(true);    //robot should now know that it has a goodie
                    setGoodieID(IID_AMMO);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                }
                
                else if(getWorld()->SpecificItem(getX(), getY(),IID_EXTRA_LIFE) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_EXTRA_LIFE)->setDead();
                    setHasGoodie(true);
                    setGoodieID(IID_EXTRA_LIFE);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    
                }
                
                
                else if(getWorld()->SpecificItem(getX(), getY(), IID_RESTORE_HEALTH) != nullptr)
                {
                    getWorld()->SpecificItem(getX(), getY(),IID_RESTORE_HEALTH)->setDead();
                    setHasGoodie(true);
                    setGoodieID(IID_RESTORE_HEALTH);
                    getWorld()->playSound(SOUND_ROBOT_MUNCH);
                    
                }
                
                
            }
        }
        
        if(getDirection() == right)
        {
            if(getDistance() == 0)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            if(getWorld()->WhatsAtThisSpot(getX()+1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()+1, getY())->blocksPath())
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX()+1, getY(), IID_SNARLBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else
            {
                moveTo(getX()+1, getY());
                m_distance--;
            }
            return;
        }
        if(getDirection() == left)
        {
            if(getDistance() == 0)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            if(getWorld()->WhatsAtThisSpot(getX()-1, getY()) != nullptr && getWorld()->WhatsAtThisSpot(getX()-1, getY())->blocksPath())
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
                
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX()-1, getY(), IID_SNARLBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else
            {
                moveTo(getX()-1, getY());
                m_distance--;
            }
            return;
            
        }
        if(getDirection() == up)
        {
            if(getDistance() == 0)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            if(getWorld()->WhatsAtThisSpot(getX(), getY()+1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()+1)->blocksPath())
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()+1, IID_SNARLBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else
            {
                moveTo(getX(), getY()+1);
                m_distance--;
            }
            return;
        }
        if(getDirection() == down)
        {
            if(getDistance() == 0)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            if(getWorld()->WhatsAtThisSpot(getX(), getY()-1) != nullptr && getWorld()->WhatsAtThisSpot(getX(), getY()-1)->blocksPath())
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_ANGRY_KLEPTOBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else if(getWorld()->SpecificItem(getX(), getY()-1, IID_SNARLBOT) != nullptr)
            {
                setDirection(setRandomDirection());
                distanceBeforeTurning();
            }
            else
            {
                moveTo(getX(), getY()-1);
                m_distance--;
            }
        }
        
        
    }
}
void KleptoBotFactory::CreateRobot()
{
    if(m_isAngry == false)
        getWorld()->addSomethingtoVector(getX(), getY(), getWorld(), IID_KLEPTOBOT, right);
    else
        getWorld()->addSomethingtoVector(getX(), getY(), getWorld(), IID_ANGRY_KLEPTOBOT, right);
    
}








//WHEN A ROBOT AND A JEWEL ARE ON THE SAME SPOT IM ALLOWED TO MOVE OVER THE ROBOT fix this
//when a robot is on exit space bullets pass over the robot

//snarl = 100 pts
//20 angry
//10 klepto
