/*
/ Layer class
/ Author: Felix Westin, Niklas Andréasson
/ File created: 2011-03-03
/ File updated: 2011-03-15
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
                        ImageHandler* imgHandler,
                        const std::string&   spriteName,
                        const float&         a,
                        const float&         v,
                        const bool&          ignoreSpeedFactor,
                        const float&         xOffset,
                        const float&         yOffset,
                        const float&         yScale,
                        const float&         xScale,
                        const bool& tile_x,
                        const bool& tile_y,
                        const bool& fit_x,
                        const bool& fit_y
                       );
            ~Layer()
            {
            }
            void update(const float& elapsed);
            void setSpeedFactor(float f);
        private:
            bool    ignoreSpeedFactor,
                    tileX,
                    tileY;

            ConfigReader* cfgReader;
            std::vector <sbe::Movable> sprites;
            void Render(sf::RenderTarget& Target) const;

            float   repeat_y,
                    repeat_x,
                    angle,
                    speed,
                    scale_x,
                    scale_y,
                    speedFactor;

            int     repeat_nr_x,
                    repeat_nr_y;

            unsigned int    width,
                            height,
                            img_width,
                            img_height;

            float   space_x,
                    space_y,
                    offsetX,
                    offsetY;

    };
}

#endif

