/*
/ Base entity class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2010-12-07
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "entity.h" //Base entity class
#include "particle.h"   //Header

namespace sbe
{
    Particle::Particle()
    {
        xSpeed = 0;
        ySpeed = 0;
    }
    void Particle::onThink()
    {
        pUpdate();
    }
    void Particle::pUpdate()
    {
        Move( GetPosition().x + xSpeed , GetPosition().y + ySpeed );
    }
}
