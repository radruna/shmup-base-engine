/*
/ Enemy class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-04
/ File updated: 2011-03-14
/ License: GPLv3
*/
#include "enemy.h"
#include "../sys/logger.h" //Outputs debug in console and log
#include "../sys/util.h"

namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName, Path pth, float r, std::string pSysExpl, int l, float scale_x, float scale_y)
    : Ship(spriteName, imgHandler)
    {
        pSysDeath = NULL;
        pSysDeath_f = pSysExpl;
        hitBoxRadius = r;
        path = pth;
        i = 0;
        sbe::Sprite::SetCenter(sbe::Sprite::GetSize().x/2, sbe::Sprite::GetSize().y/2);
        life = l;
        sbe::Sprite::SetScale(scale_x, scale_y);
        alive = 1;
        //hitbox = new Hitbox(hitBoxRadius);
    }

    Enemy::~Enemy()
    {
        //safeDelete(hitbox);
    }

    void Enemy::Render(sf::RenderTarget& Target) const
    {
        Ship::Render(Target);

        if(pSysDeath != NULL)
        {
            Target.Draw(*pSysDeath);
        }
    }

    void Enemy::kill()
    {
            pSysDeath = new ParticleSystem( pSysDeath_f, imgHandler, 0 );
            pSysDeath->SetPosition(GetSize().x / 2, GetSize().x / 2);
    }

    void Enemy::update(const float& elapsed)
    {
        if(pSysDeath != NULL)
        {
            pSysDeath->update(elapsed);
        }

        //Timers for two different movements
        Time        += elapsed;
        OrientTime  += elapsed;

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
    /*
        if(alive == 0){
            Logger::writeMsg(1) << "Nu";
            deathTimer += elapsed;
        }
*/
        //Changes path when duration time reached
        if(Time > duration && i != (path.getVector().size()-1)){
            i++;
            Time = 0;
        }

        //If stopMax == 0 and orientDuration is reached reset clock
        if(OrientTime > orientDuration && stopMax == 0){
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
        if(Time > duration){
            maxangle = 0;
            angle = stopAngle;
        }

        //Calculates how much the enemy is to move based on elapsed time
        if(Time == 0)
        {
            angleTime = 1;
        }else{
            angleTime = Time/duration;
        }
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

    float Enemy::xPos() {
        return GetPosition().x;
    }

    float Enemy::yPos() {
        return GetPosition().y;
    }

    float Enemy::isDead()
    {
        if(life <= 0)
        {
            return true;
        }else
        {
            return false;
        }
    }

    void Enemy::hit()
    {
        life--;
        Logger::writeMsg(1) << life;
    }

}
