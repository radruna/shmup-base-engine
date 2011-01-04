/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2011-01-04
/ License: GPLv3
*/
#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <fstream>   //Read script files
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "entity.h" //Base class def

namespace sbe
{
    class Particle : public sbe::Entity
    {
        /*
            Particle class
        */
        public:
            Particle(const sf::Image& img, float h, float v);
            ~Particle()
            {
            }
            void update();
            void pUpdate();
            float getAngle();
            void setAngle(float a);
        private:
            float angle;
            float speed;
    };
}

#endif
