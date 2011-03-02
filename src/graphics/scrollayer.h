/*
/ Scroll layer class
/ Author: Niklas Andréasson
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#ifndef SCROLLAYER_H_INCLUDED
#define SCROLLAYER_H_INCLUDED

#include <iostream> //Debug output
#include <sstream> //Test
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../game/movable.h" //Base class def

namespace sbe
{
    class Scrollayer : public sf::Drawable , FileHandler
    {
        /*
            Particle class
        */
        public:
            Scrollayer(
                       const std::string& scrollayerFile,
                       ImageHandler* imgHandler
                       );
            ~Scrollayer()
            {
            }
            void load();
            void update(const float& elapsed);
        private:
            //sf::Image bgImg;
            //std::list <sf::Sprite> layers;
            //sf::Sprite bgSprite;
            std::string scriptFile;

            struct Layer
            {
                sf::Sprite bgSprite;
                float speed, xPos, yPos;
            };

            std::list <Layer> layers;
            Layer tmp;
            void Render(sf::RenderTarget& Target) const;
            ImageHandler *imageHandler;

    };
}

#endif
