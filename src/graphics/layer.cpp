/*
/ Layer class
/ Author: Felix Westin, Niklas Andréasson
/ File created: 2011-03-03
/ File updated: 2011-03-03
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

    Layer::Layer(
                        ConfigReader* configReader,
                        const sf::Image&     img,
                        const float&         a,
                        const float&         v,
                        const float&         xOffset,
                        const float&         yOffset,
                        const float&         yScale,
                        const float&         xScale,
                        const float&         repeat_space_x,
                        const float&         repeat_space_y,
                        const bool& tile_x,
                        const bool& tile_y
                       )
    {
        cfgReader = configReader;
        angle = a;
        speed = v;
        space_x = repeat_space_x;
        space_y = repeat_space_y;

        tileX = tile_x;
        tileY = tile_y;

        //Get img width and height
        img_width = img.GetWidth() * xScale;
        img_height = img.GetHeight() * yScale;

        //Numbers of sprites needed to fill the screen.
        repeat_nr_x = ceil(cfgReader->getRes().x / img_width) + 1;
        repeat_nr_y = ceil(cfgReader->getRes().y / img_height) + 2;

        img_offsetX = 0;
        img_offsetY = 0;

        for(int u = 0; u < repeat_nr_y; u++)
        {
            for(int i = 0; i < repeat_nr_x; i++)
            {
                sprites.push_back(Movable(img, angle, v));
                sprites.back().SetCenter(img_width / 2, img_height / 2);
                sprites.back().SetScale(xScale,yScale);
                sprites.back().SetPosition(i * img_width,u * img_height);
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
                    if( ( sprites[i].GetPosition().x - sprites[i].GetSize().x / 2 ) > cfgReader->getRes().x)
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
