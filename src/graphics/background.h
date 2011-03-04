/*
/ Background class
/ Author: Niklas Andréasson
/ File created: 2011-02-25
/ File updated: 2011-03-03
/ License: GPLv3
*/
#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

#include <iostream> //Debug output
#include <sstream> //Test
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../graphics/layer.h"   //Layer class
#include "../game/movable.h" //Base class def

namespace sbe
{
    class Background : public FileHandler , public sf::Drawable
    {
        /*
            Background class
        */
        public:
            Background(
                       const std::string& scrollayerFile,
                       ImageHandler* imgHandler
                       );
            ~Background()
            {
            }
            void load();
            void update(const float& elapsed);
        private:
            //sf::Image bgImg;
            //std::list <sf::Sprite> layers;
            //sf::Sprite bgSprite;
            std::string scriptFile;
            std::string spriteName;
            float       xOffset,
                        yOffset;
            float moveAngle;
            float moveSpeed;
            float yScale, xScale;
            int repeat;
            sf::Image tmpImg;

            std::list <Layer> layers;
            void Render(sf::RenderTarget& Target) const;
            ImageHandler *imageHandler;

    };
}

#endif
