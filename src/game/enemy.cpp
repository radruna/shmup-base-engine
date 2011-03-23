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
        i = 0;
        sbe::Sprite::SetCenter(sbe::Sprite::GetSize().x/2, sbe::Sprite::GetSize().y/2);
    }
    void Enemy::update(const float& elapsed)
    {

        Time        = MoveClock.GetElapsedTime();
        OrientTime  = OrientClock.GetElapsedTime();

        duration = path.getVector()[i].duration;
        orientation = path.getVector()[i].orientation;
        orientDuration = path.getVector()[i].orientDuration;
        startAngle = path.getVector()[i].startAngle;
        stopAngle = path.getVector()[i].stopAngle;
        orientStart = path.getVector()[i].orientStart;
        orientStop = path.getVector()[i].orientStop;
        stopMax = path.getVector()[i].stopMax;

        if(Time > duration && i != (path.getVector().size()-1)){
            i++;
            MoveClock.Reset();
            Time = 0;
        }

        if(OrientTime > orientDuration && stopMax == 0){
            OrientClock.Reset();
            OrientTime = 0;
        }

        angle = startAngle;
        orientmin = orientStart;
        dir = 0;

        if(startAngle > stopAngle){
            maxangle = startAngle - stopAngle;
            dir = 1;
        }
        else
            maxangle = stopAngle - startAngle;

        if(orientStart > orientStop){
            orientmax = orientStart - orientStop;
            orientDir = 1;
        }
        else
            orientmax = orientStop - orientStart;

        if(Time >=duration){
            maxangle = 0;
            angle = stopAngle;
        }

        float speed = path.getVector()[i].moveSpeed;

        angleTime = Time/duration;
        rotationTime = OrientTime/orientDuration;

        if(dir == 1)
            angle -= maxangle*angleTime;
        else
            angle += maxangle*angleTime;

        if(orientDir == 1 && orientation == 1)
            orientmin -= orientmax*rotationTime;
        else if(orientation == 1)
            orientmin += orientmax*rotationTime;

        if(orientStop <= orientmin && stopMax == 1)
            orientmin = orientStop;

        sbe::Sprite::SetRotation(-(angle+90+orientmin));
        Move( (cos((angle) / (180/PI)) * speed) * elapsed,(sin((angle) / (180/PI)) * speed) * elapsed);
    }

}
