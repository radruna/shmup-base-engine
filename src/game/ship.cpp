/*
/ Base ship class implementation
/ Author: Victor Rådmark
/ File created: 2010-12-23
/ File updated: 2010-12-24
/ License: GPLv3
*/
#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "movable.h" //Base class def
#include "ship.h"

namespace sbe
{
    Ship::Ship(const sf::Image& img, const int& max, const unsigned int& mod)
        : Movable(img, 0, 0), speedV(0, 0), maxSpeed(max), modifier(mod), xDir(0), yDir(0)
    {

    }

    Ship::Ship(const std::string& imgStr, ImageHandler* iHandler, const int& max, const unsigned int& mod)
        : Movable(imgStr, iHandler, 0, 0), speedV(0, 0), maxSpeed(max), modifier(mod), xDir(0), yDir(0)
    {
    }

    Ship::~Ship()
    {

    }

    void Ship::update(const float& elapsed)
    {
        /*
            Purpose: Updates the ship's position each frame.
            It checks the previously set xDir and yDir vars and checks the current speed
            which makes for a nice flying algorithm.
        */
        //Use angle method instead
        if(xDir == -1 && speedV.x > (maxSpeed * -1))
            speedV.x--;
        else if(xDir == 1 && speedV.x < maxSpeed)
            speedV.x++;
        else
        {
            if(speedV.x < 0) speedV.x++;
            if(speedV.x > 0) speedV.x--;
        }

        if(yDir == -1 && speedV.y > (maxSpeed * -1))
            speedV.y--;
        else if(yDir == 1 && speedV.y < maxSpeed)
            speedV.y++;
        else
        {
            if(speedV.y < 0) speedV.y++;
            if(speedV.y > 0) speedV.y--;
        }

        xDir = 0;
        yDir = 0;

        Move(speedV.x * elapsed * modifier, speedV.y * elapsed * modifier);
    }

    void Ship::fly(const Dir& dir)
    {
        if(dir == UP)
            yDir = -1; //angle = 90
        else if(dir == DOWN)
            yDir = 1; //angle = 270
        else if(dir == LEFT)
            xDir = -1; //angle = 180
        else
            xDir = 1; //angle = 0
    }
}
