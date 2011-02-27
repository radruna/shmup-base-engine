/*
/ Projectile class
/ Author: Felix Westin
/ File created: 2011-01-29
/ File updated: 2011-01-29
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream> //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list> //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "../graphics/imagehandler.h" //For loading images
#include "../graphics/particlesystem.h" //Particle system
#include "movable.h"
#include "projectile.h" //Class def

namespace sbe
{
    Projectile::Projectile(
                        ImageHandler*       imgHandler,
                        const sf::Image&    img,
                        const float&        a,
                        const float&        v
                       )
    : Movable(img, a, v)
    {

        //Set default values
        name            =   "none";
        spriteName      =   "default_particle";
        particleSystem  =   "none";
        speed           =   10;
        hitBoxRadius    =   5;
        damage          =   10;
    }

    void Projectile::update(const float& elapsed)
    {
        Movable::update(elapsed);
    }
}
