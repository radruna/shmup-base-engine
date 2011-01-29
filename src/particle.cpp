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
                       const float&         width,
                       const float&         height,
                       const float&         a,
                       const float&         v,
                       const float&         lifeTime,
                       const int&           alpha,
                       const float&         fInDur,
                       const float&         fOutDur,
                       const float&         fric,
                       const ParaMod&       sizeModifier,
                       const float&         movementModAngle,
                       const float&         spawnT,
                       const bool&          moveAlign,
                       const bool&          internalOsc,
                       const DiffColor&     colorInitial,
                       const DiffColor&     colorModified,
                       const ColModData&    colorModData
                       )
        : Movable(img, a, v)
    {
        SetCenter(GetSize().x / 2,GetSize().y / 2);
        SetScale( width , height );
        age = 0;
        life = lifeTime;
        spawnTime = spawnT;
        fadeInToAlpha = alpha;
        fadeOutFromAlpha = alpha;
        fadeInDuration = fInDur;
        fadeOutDuration = fOutDur;
        friction = fric;

        sizeMod = sizeModifier;

        movementModAngleRate = movementModAngle;
        moveAngleAlign = moveAlign;
        internalOscillation = internalOsc;

        colIni = colorInitial;
        colMod = colorModified;
        colModData = colorModData;

        if(colIni.r != 255 || colIni.g != 255 || colIni.b != 255)
            SetDiffuseColor(colIni.r, colIni.g, colIni.b);

        //Set values if scalar size mod = off and oscillating size mod = on
        if(sizeMod.frequency != 0 && sizeMod.scalarRate == 1)
        {
            widthFixed = width;
            heightFixed = height;
        }

        if(fadeInDuration != 0)
        {
            fadeIn = true;
            SetAlpha(0);
            fadeInToAlpha = alpha;
            preAlpha = 0;
        }
        else
        {
            SetAlpha(alpha);
            preAlpha = alpha;
        }

    }

    void Particle::update(const float& elapsed)
    {

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

        //Apply size mods
        if(sizeMod.scalarRate != 1 || sizeMod.frequency != 0)
        {
            //Apply scalar size mod
            if(sizeMod.scalarRate != 1)
            {
                float a = GetScale().x + ( (sizeMod.scalarRate-1) / (1/elapsed) );
                float b = GetScale().y + ( (sizeMod.scalarRate-1) / (1/elapsed) );
                SetScale(a,b);
            }
            //Apply oscillating size mod
            else if(sizeMod.frequency != 0)
            {
                if(!internalOscillation)    //Global clock
                    sizeModOsc = sizeMod.amplitude * sin( (age + spawnTime) * sizeMod.frequency ) + sizeMod.amplitudeOffset;
                else                        //Internal clock
                    sizeModOsc = sizeMod.amplitude * sin( age * sizeMod.frequency ) + sizeMod.amplitudeOffset;

                SetScale(widthFixed * sizeModOsc, heightFixed * sizeModOsc);
            }
        }

        //Apply movement angle mod
        if(movementModAngleRate != 0)
        {
            if(moveAngleAlign)
                SetRotation(getAngle() * -1);       //Reversed angle. Why? :<
            setAngle(getAngle() + movementModAngleRate / (1/elapsed));
        }

        //Apply color mod
        if(colModData.offset < age)
        {
            if(colMod.r != colIni.r)
            {
                if(colModData.duration != 0)
                    SetColorR( GetColorR() - (GetColorR()-colMod.r) / colModData.duration / (1/elapsed) );
                else
                    SetColorR( GetColorR() - (GetColorR()-colMod.r) / life / (1/elapsed) );
            }

            if(colMod.g != colIni.g )
            {
                if(colModData.duration != 0)
                    SetColorG( GetColorG() - (GetColorG()-colMod.g) / colModData.duration / (1/elapsed) );
                else
                    SetColorG( GetColorG() - (GetColorG()-colMod.g) / life / (1/elapsed) );
            }

            if(colMod.b != colIni.b )
            {
                if(colModData.duration != 0)
                    SetColorB( GetColorB() - (GetColorB()-colMod.b) / colModData.duration / (1/elapsed) );
                else
                    SetColorB( GetColorB() - (GetColorB()-colMod.b) / life / (1/elapsed) );
            }
        }

        //Decrease life
        life -= elapsed;
        //Increase age
        age += elapsed;

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
