/*
/ Background class
/ Author: Niklas Andréasson
/ File created: 2011-02-25
/ File updated: 2011-03-15
/ License: GPLv3
*/
#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <iostream> //Debug output
#include <sstream> //Test
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../graphics/drawable.h" //Base class def
#include "../graphics/layer.h"   //Layer class
#include "../sys/filehandler.h" //Base class def
#include "../sys/configreader.h"

namespace sbe
{
    class Background : public FileHandler , public sbe::Drawable
    {
        /*
            Background class
        */
        public:
            Background
            (
                ConfigReader* configReader,
                const std::string& scrollayerFile,
                ImageHandler* imgHandler
            );
            ~Background()
            {
            }
            void load();
            void update(const float& elapsed);
            void setSpeedFactor(float f);
        private:
            ConfigReader* cfgReader;
            std::string scriptFile;
            std::string spriteName;
            float       xOffset,
                        yOffset;

            float   yScale,
                    xScale;

            bool    ignoreSpeedFactor,
                    tile_x,
                    tile_y,
                    fit_x,
                    fit_y;
            float moveAngle;
            float moveSpeed;

            std::list <Layer> layers;
            void Render(sf::RenderTarget& Target) const;
            ImageHandler *imageHandler;

    };
}

#endif
