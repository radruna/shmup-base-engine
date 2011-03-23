/*
/ Enemy class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include "enemy.h"
#include "../sys/logger.h" //Outputs debug in console and log


namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName, Path& pth)
    : Ship(spriteName, imgHandler)
    {
        path = pth;

    }
    void Enemy::update(const float& elapsed)
    {

        Time = Clock.GetElapsedTime();
        if(Time >= path.getVector().front().duration) {
            //Logger::writeMsg(1) << Time;  //Variable not found
            Move(0,2);
        }else
            Move(path.getVector().front().moveSpeed,0);

    }

}
