/*
/ Base ship class
/ Author: Victor Rådmark
/ File created: 2010-12-23
/ File updated: 2010-12-24
/ License: GPLv3
*/
#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "movable.h" //Base class def

namespace sbe
{
    class Ship : public sbe::Movable
    {
        public:
            Ship(const sf::Image& img, const int& max = 15, const unsigned int& mod = 30);
            Ship(const std::string& imgStr, ImageHandler* iHandler, const int& max = 15, const unsigned int& mod = 30);
            ~Ship();

            enum Dir
            {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };

            void update() //Abstract override
            {

            }
            void update(const float& elapsed); //Run each frame
            void fly(const Dir& dir); //When something wants the ship to fly

            void setMaxSpeed(const int& max)
            {
                maxSpeed = max;
            }

            void setMod(const unsigned int& mod = 0)
            {
                modifier = mod;
            }

        protected:
            sf::Vector2f speedV;
            int maxSpeed;
            unsigned int modifier;
            short xDir, yDir;
    };
}

#endif
