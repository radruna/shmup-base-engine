/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-04
/ License: GPLv3
*/
#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <SFML/Graphics.hpp> //Sfml stuff

#include "movable.h" //Base class def

namespace sbe
{
    class Particle : public sbe::Movable
    {
        /*
            Particle class
        */
        public:
            Particle(const sf::Image& img, const float& a, const float& v);
            ~Particle()
            {
            }
            void update(const float& elapsed);
    };
}

#endif
