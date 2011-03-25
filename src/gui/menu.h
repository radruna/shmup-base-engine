/*
/ Menu panels base class
/ Author: Victor Rådmark
/ Created: 2011-02-14
/ Updated: 2011-02-27
/ License: GPL v3
*/
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "../graphics/particlesystem.h"
#include "../graphics/imagehandler.h"
#include "../sys/configreader.h"
#include "panel.h"

namespace sbe
{
    class Menu : public sbe::Panel
    {
        public:
            Menu()
            {
                pSystem = NULL;
            }

            Menu(const sf::Vector2i& r, const sf::Color& color = sf::Color(50, 80, 80, 25))
                : Panel(sf::Vector2f(75, 75), sf::Vector2f(r.x - 75, r.y - 75), color, 1, sf::Color::White), res(r)
            {
                pSystem = NULL;
            }

            Menu(const std::string& psFile,
                 ImageHandler* imgHandler,
                 ConfigReader* cfgReader,
                 const sf::Vector2i& r,
                 const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                 const sf::Vector2i& next = sf::Vector2i(-1, -1));
            ~Menu();

            void update(const float& elapsed);

            sf::Vector2i getNextPSPos()
            {
                return nextPos;
            }

            sf::Vector2f getPSPos()
            {
                return sf::Vector2f(pSystem->GetPositionX(), pSystem->GetPositionY());
            }

        protected:
            void Render(sf::RenderTarget& target) const;

            ParticleSystem *pSystem;
            sf::Vector2i res,
                         nextPos;
    };
}

#endif
