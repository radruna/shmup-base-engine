/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2010-01-18
/ File updated: 2011-01-21
/ License: GPLv3
*/
#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sbe
{
    class Panel
    {
        public:
            Panel(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline = 0, const sf::Color& outlineColor = sf::Color::Black);
            ~Panel();

        protected:
            sf::Shape *panelRect;
    };
}

#endif
