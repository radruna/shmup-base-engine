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
                        const std::string&  pSysFile,
                        const float         radie
                       )
    {
        imageHandler = imgHandler;
        configReader = cfgReader;
        proj = Movable( img, a, v);
        proj.SetCenter(proj.GetSize().x / 2, proj.GetSize().y / 2);
        proj.SetPosition(xPos, yPos);
        //Set default values
        hitBoxRadius    =   radie;
        damage          =   10;
        hitbox = new Hitbox(hitBoxRadius);

        pSystemFile = pSysFile;

        if(pSystemFile == "none")
        {}
        else
        {
            pSys = new ParticleSystem( pSysFile, imageHandler, 0 );
            pSys->SetPosition(xPos, yPos);
        }
    }

    void Projectile::Render(sf::RenderTarget& Target) const
    {
        Target.Draw(proj);

        if(pSystemFile == "none")
        {}
        else
            Target.Draw(*pSys);
    }

    void Projectile::update(const float& elapsed)
    {

        if(pSystemFile == "none")
        {}
        else
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
        }

        proj.update(elapsed);

        if(pSystemFile == "none")
        {}
        else
        {
            pSys->update(elapsed);
            pSys->SetPosition(proj.GetPosition().x, proj.GetPosition().y);
        }
    }

    void Projectile::kill()
    {
        if(pSystemFile == "none")
        {}
        else
        pSys->kill();
        safeDelete(pSys);
    }

    bool Projectile::isUseless()
    {
        if(pSystemFile == "none")
        {
            if(
                     proj.GetPosition().x < 0
                    ||
                     proj.GetPosition().x > configReader->getRes().x
                    ||
                     proj.GetPosition().y < 0
                    ||
                     proj.GetPosition().y > configReader->getRes().y
                )
                return true;
            else
                return false;
        }
        else
        {
            if(pSys->isEmpty())
            {
                if(
                     pSys->GetPositionX() < - 20
                    ||
                     pSys->GetPositionX() > configReader->getRes().x + 20
                    ||
                     pSys->GetPositionY() < 0 - 20
                    ||
                     pSys->GetPositionY() > configReader->getRes().y + 20
                )
                    return true;
                else
                    return false;
            }
        }

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

    int Projectile::returnRadius() {
        return hitBoxRadius;
    }

    float Projectile::xPos() {
        return proj.GetPosition().x;
    }

        float Projectile::yPos() {
        return proj.GetPosition().y;
    }
}
