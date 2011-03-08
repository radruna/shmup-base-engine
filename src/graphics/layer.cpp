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
                       const unsigned int& h
                       )
    {

            width = w;
            height = h;
            space_x = repeat_space_x;
            space_y = repeat_space_y;

            if(a == 0)
                angle = 0;
            else if(a == 1)
                angle = 180;
            else if(a == 2)
                angle = 90;
            else if(a == 3)
                angle = 270;
            else
                angle = 0;


            sprites.push_back(Movable(img, angle, v));
            sprites.front().SetScale(xScale,yScale);

            //Sprite width and height
            sprite_width = (sprites.front().GetSize().x);
            sprite_height = (sprites.front().GetSize().y);

            repeat_nr_x = ceil(w/sprite_width);
            repeat_nr_y = ceil(h/sprite_height);

            if(angle == 0 || angle == 180)
            {
                for(int i= 0; i< repeat_nr_x; i++)
                {
                    sprites.push_back(Movable(img, angle, v));
                    sprites[i+1].SetScale(xScale,yScale);
                }
            }
            else if(angle == 90 || angle == 270)
            {
                for(int i= 0; i< repeat_nr_y; i++)
                {
                    sprites.push_back(Movable(img, angle, v));
                    sprites[i+1].SetScale(xScale,yScale);
                }

            }

            repeat_x = 0;
            repeat_y = 0;


            if(angle == 0 || angle == 180)
            {
                for(std::vector<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
                {
                    it->SetPosition(xOffset+repeat_x, yOffset);

                    if(angle == 0)
                        repeat_x -= (sprites.front().GetSize().x) + repeat_space_x;
                    else
                        repeat_x += (sprites.front().GetSize().x) + repeat_space_x;
                }

            }
            else if(angle == 90 || angle == 270)
            {
                for(std::vector<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
                {
                    it->SetPosition(xOffset, yOffset+repeat_y);

                    if(angle == 90)
                        repeat_y -= (sprites.front().GetSize().y) + repeat_space_y;
                    else
                        repeat_y += (sprites.front().GetSize().y) + repeat_space_y;
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

                if(angle == 0)
                {
                        if((sprites[it].GetPosition().x) > width)
                        {
                            if(it == 0)
                                sprites[it].SetPosition(sprites[sprites.size()-1].GetPosition().x - (sprite_width + space_x), sprites[0].GetPosition().y);
                            else
                                sprites[it].SetPosition(sprites[it-1].GetPosition().x - (sprite_width + space_x), sprites[0].GetPosition().y);
                        }
                }
                else if(angle == 90)
                {
                       if((sprites[it].GetPosition().y) > height)
                        {
                            if(it == 0)
                                sprites[it].SetPosition(sprites[0].GetPosition().x, sprites[sprites.size()-1].GetPosition().y - (sprite_height + space_y));
                            else
                                sprites[it].SetPosition(sprites[0].GetPosition().x, sprites[it-1].GetPosition().y - (sprite_height + space_y));
                        }
                }
                else if(angle == 180)
                {
                       if((sprites[it].GetPosition().x + sprite_width) < 0 )
                        {
                            if(it == 0)
                                sprites[it].SetPosition(sprites[sprites.size()-1].GetPosition().x + (sprite_width + space_x), sprites[0].GetPosition().y);
                            else
                                sprites[it].SetPosition(sprites[it-1].GetPosition().x + (sprite_width + space_x), sprites[0].GetPosition().y);
                        }
                }
                else if(angle == 270)
                {
                       if((sprites[it].GetPosition().y + sprite_height) < 0)
                        {
                            if(it == 0)
                                sprites[it].SetPosition(sprites[0].GetPosition().x, sprites[sprites.size()-1].GetPosition().y + (sprite_height + space_y));
                            else
                                sprites[it].SetPosition(sprites[0].GetPosition().x, sprites[it-1].GetPosition().y + (sprite_height + space_y));
                        }
                }
        }

    }

}
