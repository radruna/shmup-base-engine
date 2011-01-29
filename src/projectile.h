/*
/ Projectile class
/ Author: Felix Westin
/ File created: 2011-01-29
/ File updated: 2011-01-29
/ License: GPLv3
*/
#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <iostream> //Debug output
#include <fstream> //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list> //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h" //For loading images
#include "filehandler.h" //Base class
#include "particlesystem.h" //Particle system
#include "movable.h"
#include "logger.h" //Outputs debug in console and log

namespace sbe
{
    class Projectile : public FileHandler , public Movable
    {
        /*
        Projectile class
        */
        public:
            Projectile(
                        const std::string&  projectileFile,
                        ImageHandler*       imgHandler,
                        const sf::Image&    img,
                        const float&        a,
                        const float&        v
                       );
            ~Projectile()
            {
            }
            void update(const float& elapsed);

        protected:
            //void Render(sf::RenderTarget& Target) const;

        private:
            std::string         name,
                                spriteName,
                                particleSystem;

            float               speed,
                                hitBoxRadius,
                                damage;
    };
}

#endif
