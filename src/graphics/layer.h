/*
/ Layer class
/ Author: Felix Westin, Niklas Andréasson
/ File created: 2011-03-03
/ File updated: 2011-03-03
/ License: GPLv3
*/
#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../game/movable.h" //Base class def

namespace sbe
{
    class Layer : public sbe::Movable
    {
        /*
            Layer class
        */
        public:
            Layer(
                       const sf::Image&     img,
                       const float&          a,
                       const float&          v,
                       const float&          xOffset,
                       const float&          yOffset
                       );
            ~Layer()
            {
            }
            void update(const float& elapsed);
        private:
    };
}

#endif
