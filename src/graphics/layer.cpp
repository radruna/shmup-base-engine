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
                        const sf::Image&     img,
                        const float&         a,
                        const float&         v,
                        const float&         xOffset,
                        const float&         yOffset,
                        const float&         yScale,
                        const float&         xScale,
                        const float&           repeat_space_x,
                        const float&           repeat_space_y,
                        const unsigned int& w,
                        const unsigned int& h,
                        const bool& tile_x,
                        const bool& tile_y
                       )
    {

            width = w;
            height = h;
            angle = a;
            space_x = repeat_space_x;
            space_y = repeat_space_y;

            //Get img width and height
            img_width = img.GetWidth() * xScale;
            img_height = img.GetHeight() * yScale;

            //Numbers of sprites to fill the screen.
            repeat_nr_x = ceil(w/img_width) + 1;
            repeat_nr_y = ceil(h/img_height) + 1;

            img_offsetX = 0;
            img_offsetY = 0;

            //Create sprites
            if(tile_x == 1 && tile_y == 1)
            {
                for(int x = 0; x<repeat_nr_x; x++)
                {
                    for(int y = 0; y < repeat_nr_y; y++)
                    {
                        sprites.push_back(Movable(img, angle, v));
                        sprites[y].SetScale(xScale,yScale);
                        sprites[y].SetPosition(img_offsetX,img_offsetY);
                        img_offsetY += img_height;
                    }
                    img_offsetX += img_width;
                }
            }
            else if(tile_x == 1)
            {
                for(int x = 0; x<repeat_nr_x; x++)
                {
                    sprites.push_back(Movable(img, angle, v));
                    sprites[x].SetScale(xScale,yScale);
                    sprites[x].SetPosition(img_offsetX,img_offsetY);

                    img_offsetX += img_width;
                }
            }
            else if(tile_y == 1)
            {
                for(int y = 0; y < repeat_nr_y; y++)
                {
                    sprites.push_back(Movable(img, angle, v));
                    sprites[y].SetScale(xScale,yScale);
                    sprites[y].SetPosition(img_offsetX,img_offsetY);
                    img_offsetY += img_height;
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
        for(unsigned int it = 0; it < sprites.size(); it++) //Iterate through layer vector
        {
            sprites[it].update(elapsed);

            /*if(angle > 0 && angle < 90)
            {
                if(sprites[it].GetPosition().x > width)
                {
                }
                if(sprites[it].GetPosition().y > height)
                {
                }

            }*/

        }

    }

}
