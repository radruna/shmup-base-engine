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
                       const int&           repeat
                       )
        : Movable(img, a, v)
    {

        SetPosition(xOffset, yOffset);
        SetScale(xScale, yScale);
    }



    void Layer::update(const float& elapsed)
    {
        Movable::update(elapsed);
    }
}
