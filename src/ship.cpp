/*
/ Base ship class implementation
/ Author: Victor Rådmark
/ File created: 2010-12-23
/ File updated: 2010-12-23
/ License: GPLv3
*/
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "entity.h" //Base class def
#include "ship.h"

namespace sbe
{
    Ship::Ship(const sf::Image& img, const int& max, const unsigned int& mod)
        : Entity(img), speed(0, 0), maxSpeed(max), modifier(mod), xDir(0), yDir(0)
    {

    }

    Ship::Ship(const std::string& imgStr, ImageHandler& iHandler, const int& max, const unsigned int& mod)
        : Entity(imgStr, iHandler), speed(0, 0), maxSpeed(max), modifier(mod), xDir(0), yDir(0)
    {
    }

    Ship::~Ship()
    {

    }

    void Ship::update(const float& elapsed)
    {
        if(xDir == -1 && speed.x > (maxSpeed * -1))
            speed.x--;
        else if(xDir == 1 && speed.x < maxSpeed)
            speed.x++;
        else
        {
            if(speed.x < 0) speed.x++;
            if(speed.x > 0) speed.x--;
        }

        if(yDir == -1 && speed.y > (maxSpeed * -1))
            speed.y--;
        else if(yDir == 1 && speed.y < maxSpeed)
            speed.y++;
        else
        {
            if(speed.y < 0) speed.y++;
            if(speed.y > 0) speed.y--;
        }

        xDir = 0;
        yDir = 0;

        Move(speed.x * elapsed * modifier, speed.y * elapsed * modifier);
    }

    void Ship::fly(const Dir& dir)
    {
        if(dir == UP)
            yDir = -1;
        else if(dir == DOWN)
            yDir = 1;
        else if(dir == LEFT)
            xDir = -1;
        else
            xDir = 1;
    }
}
