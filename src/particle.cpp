/*
/ Base entity class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-04
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "entity.h" //Base entity class
#include "particle.h"   //Header

const double PI = 3.14159265; //Pi

namespace sbe
{

    Particle::Particle(const sf::Image& img, float v, float a)
        : Entity(img)
    {
        speed = v;
        angle = a;
    }
    void Particle::update()
    {
        pUpdate();
    }
    void Particle::pUpdate()
    {
        Move( cos(angle / (180/PI) ) * speed , sin(angle / (180/PI) ) * speed );
    }
    float Particle::getAngle()
    {
        return angle;
    }
    void Particle::setAngle(float a)
    {
        angle = a;
    }
}
