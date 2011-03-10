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
                        const float&           repeat_space_x,
                        const float&           repeat_space_y,
                        const bool& tile_x,
                        const bool& tile_y
                       )
    {
            cfgReader = configReader;
            angle = a;
            speed = v;
            space_x = repeat_space_x;
            space_y = repeat_space_y;

            //Get img width and height
            img_width = img.GetWidth() * xScale;
            img_height = img.GetHeight() * yScale;

            //Numbers of sprites to fill the screen.
            repeat_nr_x = ceil(cfgReader->getRes().x / img_width) + 1;
            repeat_nr_y = ceil(cfgReader->getRes().y / img_height) + 1;

            img_offsetX = 0;
            img_offsetY = 0;

            if(tile_x)
            {
                for(int i = 0; i < repeat_nr_x; i++)
                {
                    sprites.push_back(Movable(img, angle, v));
                    sprites[i].SetCenter(sprites[i].GetSize().x / 2, sprites[i].GetSize().y / 2);
                    sprites[i].SetScale(xScale,yScale);
                    sprites[i].SetPosition(img_offsetX,img_offsetY);
                    img_offsetX += img_width;
                }
                img_offsetX = 0;
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
            if( ( 1 ) )
            {
                sprites[i].update(elapsed);
                if( ( sprites[i].GetPosition().x - sprites[i].GetSize().x / 2 ) > cfgReader->getRes().x)
                {
                    sprites[i].SetPosition( sprites[i].GetPosition().x - repeat_nr_x * img_width,img_offsetY);
                }
            }
        }

    }

}
