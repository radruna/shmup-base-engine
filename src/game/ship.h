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
#include "../graphics/particlesystem.h" //Particle system

namespace sbe
{
    class Ship : public sbe::Movable
    {
        public:
            Ship() { pSysDeath = NULL; }
            Ship(const sf::Image& img, const std::string& pSysDeath, float r = 25, const int max = 15, const unsigned int dMod = 400, const unsigned int oMod = 200);
            Ship(const std::string& imgStr, ImageHandler* iHandler, const std::string& pSysDeath, float r = 25, const int max = 15, const unsigned int dMod = 400, const unsigned int oMod = 200);
            ~Ship();

            enum Dir
            {
                UP,
                DOWN,
                LEFT,
                RIGHT
            };

            void kill(float s = 0.5);

            bool death()
            {
                if(deathTimer != -1 && deathTimer <= 0) return true;

                return false;
            }

            bool readyToDie()
            {
                if(deathTimer != -1) return true;

                return false;
            }
            void update(const float& elapsed); //Run each frame
            void fly(const Dir& dir); //When something wants the ship to fly

            void setMaxSpeed(const int& max)
            {
                maxSpeed = max;
            }

            void setMod(bool def = 0)
            {
                !def ? modifier = otherMod : modifier = defMod;
            }

            int returnRadius()
            {
                return hitBoxRadius;
            }

        protected:
            ParticleSystem *pSysDeath;
            std::string pSysDeath_f;
            float hitBoxRadius,
                  deathTimer,
                  deathDelay;
            sf::Vector2f speedV;
            int maxSpeed;
            unsigned int modifier;
            short xDir, yDir;
            unsigned int defMod,
                           otherMod;
    };
}

#endif
