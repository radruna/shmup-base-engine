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
                        ImageHandler* imgHandler,
                        const int&          xPos,
                        const int&          yPos,
                        const sf::Image&    img,
                        const float&        a,
                        const float&        v,
                        const std::string&  pSys1,
                        const std::string&  pSys2
                       )
    : Movable(img, a, v)
    {
        SetPosition(xPos, yPos);
        //Set default values
        pSystem1File = pSys1;
        pSystem2File = pSys2;
        hitBoxRadius    =   5;
        damage          =   10;

        if(pSystem1File != "none")
        {
            pSystem1 = new ParticleSystem(pSystem1File, imgHandler, 0);
        }
        if(pSystem2File != "none")
        {
            pSystem2 = new ParticleSystem(pSystem2File, imgHandler, 0);
        }
    }

    void Projectile::Render(sf::RenderTarget& Target) const
    {
        Sprite::Render(Target);

        if(pSystem1File != "none")
        {
            Target.Draw(*pSystem1);
        }
        if(pSystem2File != "none")
        {
            Target.Draw(*pSystem2);
        }
    }

    void Projectile::update(const float& elapsed)
    {
        Movable::update(elapsed);

        //Update particle systems
        if(pSystem1File != "none")
        {
            pSystem1->update(elapsed);
            //pSystem1->SetPosition(GetPosition().x, GetPosition().y);
        }
        //Draw children
        if(pSystem2File != "none")
        {
            pSystem2->update(elapsed);
            //pSystem2->SetPosition(GetPosition().x, GetPosition().y);
        }
    }
}
