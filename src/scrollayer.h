/*
/ Particle class
/ Author: Niklas Andréasson
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#ifndef SCROLLAYER_H_INCLUDED
#define SCROLLAYER_H_INCLUDED

#include <SFML/Graphics.hpp> //Sfml stuff

#include <iostream> //Debug output
#include "movable.h" //Base class def

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
            sf::Image bgImg;
            std::string scriptFile;
            void Render(sf::RenderTarget& Target) const;
            ImageHandler *imageHandler;

    };
}

#endif
