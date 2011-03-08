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
                        ConfigReader* cfgReader,
                        const int&          xPos,
                        const int&          yPos,
                        const sf::Image&    img,
                        const float&        a,
                        const float&        v,
                        const std::string&  pSysFile
                       )
    {
        imageHandler = imgHandler;
        configReader = cfgReader;
        proj = Movable( img, a, v);
        proj.SetCenter(proj.GetSize().x / 2, proj.GetSize().y / 2);
        proj.SetPosition(xPos, yPos);
        //Set default values
        hitBoxRadius    =   5;
        damage          =   10;

        if(pSysFile != "" || pSysFile != "none")
        {
            pSys = new ParticleSystem( pSysFile, imageHandler, 0 );
            pSystemFile = pSysFile;
            pSys->SetPosition(xPos, yPos);
        }
    }

    void Projectile::Render(sf::RenderTarget& Target) const
    {
        Target.Draw(proj);

        if(pSystemFile != "" || pSystemFile != "none")
            Target.Draw(*pSys);
    }

    void Projectile::update(const float& elapsed)
    {
        if(
           pSys->GetPositionX() < 0
           ||
           pSys->GetPositionX() > configReader->getRes().x
           ||
           pSys->GetPositionY() < 0
           ||
           pSys->GetPositionY() > configReader->getRes().y
        )
            pSys->turnOff();

        proj.update(elapsed);

        if(pSystemFile != "" || pSystemFile != "none")
        {
            pSys->update(elapsed);
            pSys->SetPosition(proj.GetPosition().x, proj.GetPosition().y);
        }
    }

    void Projectile::kill()
    {
        pSys->kill();
        safeDelete(pSys);
    }

    bool Projectile::isUseless()
    {
        if(
           ( pSys->GetPositionX() < 0 && pSys->isEmpty() )
           ||
           ( pSys->GetPositionX() > configReader->getRes().x && pSys->isEmpty() )
           ||
           ( pSys->GetPositionY() < 0 && pSys->isEmpty() )
           ||
           ( pSys->GetPositionY() > configReader->getRes().y && pSys->isEmpty() )
        )
            return true;
        else
            return false;
    }

    void Projectile::push(const float& distance)
    {
        proj.push(distance);
    }

    void Projectile::SetScale(const float& x, const float& y)
    {
        proj.SetScale(x,y);
    }

    void Projectile::SetRotation(const float& r)
    {
        proj.SetRotation(r);
    }
}
