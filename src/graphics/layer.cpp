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
                       const int&           repeat,
                       const float&           repeat_offsetx,
                       const float&           repeat_offsety,
                       const int&           nr_repeat
                       )
    {

        sprites.push_back(Movable(img, a, v));

        sprites.front().SetPosition(xOffset, yOffset);

        if(repeat == 1)
        {
            for(int i= 0; i<nr_repeat; i++) {
                sprites.push_back(Movable(img, a, v));
            }

            for(std::list<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
            {
                repeat_x += repeat_offsetx;
                repeat_y += repeat_offsety;

                it->SetPosition(xOffset+repeat_x, yOffset+repeat_y);

            }
        }


        for(std::list<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
            {


                it->SetScale(xScale, yScale);

            }



    }



    void Layer::Render(sf::RenderTarget& Target) const
    {
        for(std::list<sbe::Movable>::const_iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
        {
            Target.Draw(*it);
        }
    }



    void Layer::update(const float& elapsed)
    {
        for(std::list<sbe::Movable>::iterator it = sprites.begin(); it != sprites.end(); it++) //Iterate through layer list
        {
            it->update(elapsed);
        }
    }
}
