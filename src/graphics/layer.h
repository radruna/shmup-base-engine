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
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../game/movable.h" //Base class def

namespace sbe
{
    class Layer : public sf::Drawable
    {
        /*
            Layer class
        */
        public:
            Layer(
                        const sf::Image&     img,
                        const float&         a,
                        const float&         v,
                        const float&         xOffset,
                        const float&         yOffset,
                        const float&         yScale,
                        const float&         xScale,
                        const int&           repeat,
                        const float&         repeat_offsetx,
                        const float&         repeat_offsety,
                        const int&          nr_repeat
                       );
            ~Layer()
            {
            }
            void update(const float& elapsed);
        private:
            std::list <sbe::Movable> sprites;
            void Render(sf::RenderTarget& Target) const;
            float offset, repeat_y, repeat_x;

    };
}

#endif
