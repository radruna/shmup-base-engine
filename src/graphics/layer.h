/*
/ Layer class
/ Author: Felix Westin, Niklas Andr�asson
/ File created: 2011-03-03
/ File updated: 2011-03-03
/ License: GPLv3
*/
#ifndef LAYER_H_INCLUDED
#define LAYER_H_INCLUDED

#include <iostream> //Debug output
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../graphics/drawable.h"
#include "../game/movable.h" //Base class def

namespace sbe
{
    class Layer : public sbe::Drawable
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
                        const float&         repeat_space_x,
                        const float&         repeat_space_y,
                        const unsigned int& w,
                        const unsigned int& h
                       );
            ~Layer()
            {
            }
            void update(const float& elapsed);
        private:
            std::vector <sbe::Movable> sprites;
            void Render(sf::RenderTarget& Target) const;

            float offset, repeat_y, repeat_x, angle;
            int repeat_nr;
            unsigned int width, height;
            float sprite_width;
            float space_x;

    };
}

#endif
