/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <SFML/Graphics.hpp> //Sfml stuff

#include <iostream> //Debug output
#include "movable.h" //Base class def

namespace sbe
{
    class Particle : public sbe::Movable
    {
        /*
            Particle class
        */
        public:
            struct ParaMod
            {
                float   scalarRate,
                        frequency,
                        amplitude,
                        amplitudeOffset;
            };

            struct DiffColor
            {
                float   r,
                        g,
                        b;
            };

            struct ColModData
            {
                float   duration,
                        offset;
            };

            Particle(
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
                       );
            ~Particle()
            {
            }
            void update(const float& elapsed);
            float getLife();
            float getRotRate();
            void setRotRate(float r);
        private:

            bool    moveAngleAlign,
                    internalOscillation;
            int     fadeInToAlpha,
                    fadeOutFromAlpha,;

            float   life,
                    age,
                    rotRate,
                    preAlpha,
                    fadeInDuration, fadeOutDuration,
                    friction,
                    sizeModOsc,
                    widthFixed,
                    heightFixed,
                    movementModAngleRate,
                    spawnTime;

            ParaMod     sizeMod;

            DiffColor   colIni,
                        colMod;

            ColModData  colModData;

            bool    fadeIn,
                    fadeOut;
    };
}

#endif
