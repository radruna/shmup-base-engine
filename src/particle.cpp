/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#include <SFML/Graphics.hpp> //Sfml stuff

#include <iostream> //Debug output
#include "const.h" //Constants
#include "movable.h" //Base entity class
#include "particle.h"   //Header

namespace sbe
{

    Particle::Particle(
                       const sf::Image&     img,
                       const float&         a,
                       const float&         v,
                       const float&         lifeTime,
                       const int&           alpha,
                       const float&         fInDur,
                       const float&         fOutDur,
                       const float&         fric,
                       const float&         sizeModScalar,
                       const float&         movementModAngle,
                       const bool&          moveAlign
                       )
        : Movable(img, a, v)
    {
        age = 0;
        life = lifeTime;
        fadeInToAlpha = alpha;
        fadeOutFromAlpha = alpha;
        fadeInDuration = fInDur;
        fadeOutDuration = fOutDur;
        friction = fric;
        sizeModScalarRate = sizeModScalar;
        movementModAngleRate = movementModAngle;
        moveAngleAlign = moveAlign;

        if(fadeInDuration != 0)
        {
            fadeIn = true;
            SetAlpha(0);
            fadeInToAlpha = alpha;
            preAlpha = 0;
        }
        else
            SetAlpha(alpha);

    }

    void Particle::update(const float& elapsed)
    {

        //Decrease life
        life -= elapsed;
        //Increase age
        age += elapsed;

        //Rotate
        if(rotRate != 0 && !moveAngleAlign)
        {
            Rotate(rotRate);
        }

        //Check if I should stop fading in and start fading out
        if(life < fadeOutDuration)
        {
            fadeIn = false;
            fadeOut = true;
        }

        if(fadeIn)
        {
            //Fade in
            if(GetAlpha() < fadeInToAlpha)
            {
                preAlpha += ( (255-preAlpha) / (fadeInDuration-age) / (1/elapsed) );
                SetAlpha(preAlpha);

                //Fix overdoing it
                if(GetAlpha() > fadeInToAlpha)
                {
                    SetAlpha(fadeInToAlpha);
                    fadeIn = false;
                    preAlpha = GetAlpha();
                }
                else if(age > fadeInDuration)
                {
                    fadeIn = false;
                    preAlpha = GetAlpha();
                }
            }
        }
        else if(fadeOut)
        {
            //Fade out
            preAlpha -= ( preAlpha/life/ (1/elapsed) );
            if(preAlpha < 1)    //1 instead of 0 to fix some sprites spazzing out when fading
                {
                    preAlpha = 0;
                    fadeOut = false;
                }
            SetAlpha(preAlpha);
        }

        //Apply friction
        if(friction != 1)
            speed *= friction;

        //Apply size mod
        if(sizeModScalarRate != 1)
        {
            float a = GetScale().x + ( (sizeModScalarRate-1) / (1/elapsed) );
            float b = GetScale().y + ( (sizeModScalarRate-1) / (1/elapsed) );
            SetScale(a,b);
        }

        //Apply movement angle mod
        if(movementModAngleRate != 0)
        {
            if(moveAngleAlign)
                SetRotation(getAngle() * -1);       //Reversed angle. Why? :<
            setAngle(getAngle() + movementModAngleRate / (1/elapsed));
        }

        //Update particle
        Movable::update(elapsed);

    }

    float Particle::getLife()
    {
        return life;
    }

    float Particle::getRotRate()
    {
        return rotRate;
    }

    void Particle::setRotRate(float r)
    {
        rotRate = r;
    }

}
