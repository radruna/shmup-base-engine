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

    Particle::Particle(const sf::Image& img, const float& a, const float& v, const float& lifeTime, const int& alpha, const float& fInDur, const float& fOutDur)
        : Movable(img, a, v)
    {
        age = 0;
        life = lifeTime;
        fadeInToAlpha = alpha;
        fadeOutFromAlpha = alpha;
        fadeInDuration = fInDur;
        fadeOutDuration = fOutDur;

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
        age += elapsed;

        //Rotate
        if(rot != 0)
        {
            Rotate(rot);
        }

        if(fadeIn)
        {
            //Fade in
            if(GetAlpha() < fadeInToAlpha)
            {
                preAlpha += ( (255 - preAlpha) / (fadeInDuration - age) / (1 / elapsed) );
                SetAlpha(preAlpha);

                //Fix overdoing it
                if(GetAlpha() > fadeInToAlpha)
                    SetAlpha(fadeInToAlpha);
            }
        }
        else if(fadeOut)
        {

            //Fade out
            //TODO(Fewes#2#) Add fading out functionality

        }

        Movable::update(elapsed);

    }

    float Particle::getLife()
    {
        return life;
    }

    float Particle::getRot()
    {
        return rot;
    }

    void Particle::setRot(float r)
    {
        rot = r;
    }

}
