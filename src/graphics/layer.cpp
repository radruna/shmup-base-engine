/*
/ Layer class
/ Author: Felix Westin, Niklas Andréasson
/ File created: 2011-03-03
/ File updated: 2011-03-15
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../game/movable.h" //Base entity class
#include "layer.h"   //Header

namespace sbe
{

    Layer::Layer
    (
        ConfigReader* configReader,
        ImageHandler* imgHandler,
        const std::string&   spriteName,
        const float&         a,
        const float&         v,
        const float&         xOffset,
        const float&         yOffset,
        const float&         yScale,
        const float&         xScale,
        const bool& tile_x,
        const bool& tile_y,
        const bool& fit_x,
        const bool& fit_y
    )
    {
        cfgReader = configReader;
        angle = a;
        speed = v;

        imgHandler->getImage(spriteName).GetWidth();

        tileX = tile_x;
        tileY = tile_y;

        if(fit_x)
        {
            float a = cfgReader->getRes().x;
            float b = imgHandler->getImage(spriteName).GetWidth();
            scale_x = a / b;
            offsetX = a / 2;
        }
        else
        {
            scale_x = xScale;
            offsetX = xOffset + xOffset;
        }
        if(fit_y)
        {
            float a = cfgReader->getRes().y;
            float b = imgHandler->getImage(spriteName).GetHeight();
            scale_y = a / b;
            offsetY = a / 2 + yOffset;
        }
        else
        {
            scale_y = yScale;
            offsetY = yOffset;
        }

        //Get img width and height
        img_width = imgHandler->getImage(spriteName).GetWidth() * scale_x;
        img_height = imgHandler->getImage(spriteName).GetHeight() * scale_y;

        //Numbers of sprites needed to fill the screen.
        repeat_nr_x = ceil(cfgReader->getRes().x / img_width);
        if( repeat_nr_x * (int) img_width < cfgReader->getRes().x)
            repeat_nr_x += 2;
        else
            repeat_nr_x += 1;

        repeat_nr_y = ceil(cfgReader->getRes().y / img_height) ;
        if( repeat_nr_y * (int) img_height < cfgReader->getRes().y)
            repeat_nr_y += 2;
        else
            repeat_nr_y += 1;


        for(int u = 0; u < repeat_nr_y; u++)
        {
            for(int i = 0; i < repeat_nr_x; i++)
            {
                sprites.push_back(Movable(spriteName, imgHandler, angle, v));
                sprites.back().SetScale(scale_x,scale_y);
                sprites.back().SetCenter( sprites.back().GetSize().x / (2 * scale_x), sprites.back().GetSize().y / (2 * scale_y));    //Don't know what the fuck is going on here. Just leave it
                sprites.back().SetPosition(offsetX + i * sprites.back().GetSize().x,offsetY + u * sprites.back().GetSize().y);
            }
        }

    }

    void Layer::Render(sf::RenderTarget& Target) const
    {
        for(std::vector<sbe::Movable>::const_iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
        {
            Target.Draw(*it);
        }
    }

    void Layer::update(const float& elapsed)
    {
        for(unsigned int i = 0; i < sprites.size(); i++) //Iterate through layer vector
        {
            if(tileX)
            {
                //Handle x tiling
                if( ( angle < 90 && angle > -90 && speed > 0 ) || ( ( angle > 90 || angle < -90 ) && speed < 0 ) )  //Layer is moving to the right
                {
                    if( sprites[i].GetPosition().x - sprites[i].GetSize().x / 2 > cfgReader->getRes().x)
                    {
                        sprites[i].SetPosition( sprites[i].GetPosition().x - repeat_nr_x * img_width, sprites[i].GetPosition().y);
                    }
                }
                else  //Layer is moving to the left
                {
                    if( ( sprites[i].GetPosition().x + sprites[i].GetSize().x / 2 ) < 0)
                    {
                        sprites[i].SetPosition( sprites[i].GetPosition().x + repeat_nr_x * img_width, sprites[i].GetPosition().y);
                    }
                }
            }

            if(tileY)
            {
                //Handle y tiling
                if( ( angle > 0 && angle < 180 && speed > 0 ) || ( ( angle < 0 || angle > 180 ) && speed < 0 ) )   //Layer is moving downwards
                {
                    if( ( sprites[i].GetPosition().y - sprites[i].GetSize().y / 2 ) > cfgReader->getRes().y)
                    {
                        sprites[i].SetPosition( sprites[i].GetPosition().x, sprites[i].GetPosition().y - repeat_nr_y * img_height);
                    }
                }
                else   //Layer is moving upwards
                {
                    if( ( sprites[i].GetPosition().y + sprites[i].GetSize().y / 2 ) < 0)
                    {
                        sprites[i].SetPosition( sprites[i].GetPosition().x, sprites[i].GetPosition().y + repeat_nr_y * img_height);
                    }
                }
            }
            sprites[i].update(elapsed);
        }

    }

}
