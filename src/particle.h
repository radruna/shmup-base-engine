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
            Particle(const sf::Image& img, const float& a, const float& v, const float& lifeTime, const int& alpha, const float& fInDur, const float& fOutDur, const float& fric);
            ~Particle()
            {
            }
            void update(const float& elapsed);
            float getLife();
            float getRotRate();
            void setRotRate(float r);

        private:
            int     fadeInToAlpha,
                    fadeOutFromAlpha,;

            float   life,
                    age,
                    rotRate,
                    preAlpha,
                    fadeInDuration, fadeOutDuration,
                    friction;

            bool    fadeIn,
                    fadeOut;
    };
}

#endif
