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

            if(a == 0)
                angle = 0;
            else
                angle = 90;


            sprites.push_back(Movable(img, angle, v));
            sprite_width = (sprites.front().GetSize().x);
            repeat_nr = ceil(w/sprite_width);

            for(int i= 0; i< repeat_nr; i++) {
                sprites.push_back(Movable(img, angle, v));
            }

            repeat_x = 0;
            //repeat_y = 0;

            for(std::vector<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
            {
                it->SetPosition(xOffset+repeat_x, yOffset);

                repeat_x -= (sprites.front().GetSize().x) + repeat_space_x;
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

            if((sprites[it].GetPosition().x) > width) {
                if(it == 0)
                    sprites[it].SetPosition(sprites[sprites.size()-1].GetPosition().x - (sprite_width + space_x), sprites[sprites.size()-1].GetPosition().y);
                else
                    sprites[it].SetPosition(sprites[it-1].GetPosition().x - (sprite_width + space_x), sprites[sprites.size()-1].GetPosition().y);
            }

        }
    }

}
