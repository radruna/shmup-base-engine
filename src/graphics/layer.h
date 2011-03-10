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

#include "../graphics/drawable.h"
#include "../game/movable.h" //Base class def
#include "../sys/configreader.h"

namespace sbe
{
    class Layer : public sbe::Drawable
    {
        /*
            Layer class
        */
        public:
            Layer(
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
                       );
            ~Layer()
            {
            }
            void update(const float& elapsed);
        private:
            bool tileX, tileY;
            ConfigReader* cfgReader;
            std::vector <sbe::Movable> sprites;
            void Render(sf::RenderTarget& Target) const;
            float repeat_y, repeat_x, angle, speed;
            int repeat_nr_x, repeat_nr_y;
            unsigned int width, height, img_width, img_height;
            float space_x, space_y, img_offsetX, img_offsetY;

    };
}

#endif

