/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-04
/ License: GPLv3
*/
#include <SFML/Graphics.hpp> //Sfml stuff

#include "const.h" //Constants
#include "movable.h" //Base entity class
#include "particle.h"   //Header

namespace sbe
{

    Particle::Particle(const sf::Image& img, const float& a, const float& v, const float& lifeTime)
        : Movable(img, a, v)
    {
        life = lifeTime;
    }

    void Particle::update(const float& elapsed)
    {
        Movable::update(elapsed);
    }

    float Particle::getLife()
    {
        return life;
    }
}
