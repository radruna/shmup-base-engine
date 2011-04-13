/*
/ Enemy class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include "enemy.h"
#include "../sys/logger.h" //Outputs debug in console and log
#include "../sys/util.h"

namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName, Path pth, float r)
    : Ship(spriteName, imgHandler)
    {
        hitBoxRadius = r;
        path = pth;
        i = 0;
        sbe::Sprite::SetCenter(sbe::Sprite::GetSize().x/2, sbe::Sprite::GetSize().y/2);
        //hitbox = new Hitbox(hitBoxRadius);
    }

    Enemy::~Enemy()
    {
        //safeDelete(hitbox);
    }

    void Enemy::update(const float& elapsed)
    {
        //Timers for two different movements
        Time        = MoveClock.GetElapsedTime();
        OrientTime  = OrientClock.GetElapsedTime();

        //Duration for one path
        duration = path.getVector()[i].duration;

        //If enemies rotation will follow path
        orientation = path.getVector()[i].orientation;

        //Duration for rotation
        orientDuration = path.getVector()[i].orientDuration;
        //Start & stop angle for enemy
        startAngle = path.getVector()[i].startAngle;
        stopAngle = path.getVector()[i].stopAngle;

        //Start & stop angle for enemy orientation
        orientStart = path.getVector()[i].orientStart;
        orientStop = path.getVector()[i].orientStop;
        //Set enemies speed
        speed = path.getVector()[i].moveSpeed;

        //Will it stop or loop at end of orientation
        stopMax = path.getVector()[i].stopMax;
        //Changes path when duration time reached
        if(Time > duration && i != (path.getVector().size()-1)){
            i++;
            MoveClock.Reset();
            Time = 0;
        }
        //If stopMax == 0 and orientDuration is reached reset clock
        if(OrientTime > orientDuration && stopMax == 0){
            OrientClock.Reset();
            OrientTime = 0;
        }
        //enemy angle is set to startAngle
        angle = startAngle;
        orientmin = orientStart;
        dir = 0;
        //Checks which way the enemy is to turn
        if(startAngle > stopAngle){
            maxangle = startAngle - stopAngle;
            dir = 1;
        }
        else
            maxangle = stopAngle - startAngle;
        //Checks which way the enemy is to rotate
        if(orientStart > orientStop){
            orientmax = orientStart - orientStop;
            orientDir = 1;
        }
        else
            orientmax = orientStop - orientStart;
        //Makes enemy go in a straight line after last path
        if(Time >=duration){
            maxangle = 0;
            angle = stopAngle;
        }

        //Calculates how much the enemy is to move based on elapsed time
        angleTime = Time/duration;
        //Calculates how much the enemy is to rotate based on elapsed time
        rotationTime = OrientTime/orientDuration;
        //Changes the angle based on elapsed time
        if(dir == 1)
            angle -= maxangle*angleTime;
        else
            angle += maxangle*angleTime;
        //Changes the orientation based on elapsed time
        if(orientDir == 1 && orientation == 1)
            orientmin -= orientmax*rotationTime;
        else if(orientation == 1)
            orientmin += orientmax*rotationTime;
        //If stopMax == 1 then stop at maxorientation angle
        if(orientStop <= orientmin && stopMax == 1)
            orientmin = orientStop;
        //Sets rotation for enemy
        sbe::Sprite::SetRotation(-(angle+90+orientmin));
        //Moves the enemy
        Move( (cos((angle) / (180/PI)) * speed) * elapsed,(sin((angle) / (180/PI)) * speed) * elapsed);
    }

    int Enemy::returnRadius() {
        return hitBoxRadius;
    }

}
