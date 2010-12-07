/*
/ Particle class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2010-12-07
/ License: GPLv3
*/
#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <fstream>   //Read script files
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

namespace sbe
{
    class Particle : public Entity
    {
        /*
            Particle class
        */
        public:
            Particle();
            ~Particle()
            {
            }
            void onThink();
            void pUpdate();
        private:
            float xSpeed;
            float ySpeed;
    };
}

#endif
