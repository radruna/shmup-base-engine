/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2010-01-18
/ File updated: 2011-01-18
/ License: GPLv3
*/

#include <SFML/Graphics.hpp>

namespace sbe
{
    Panel::Panel(unsigned int& x1, unsigned int y1, unsigned int& x2, unsigned int& y2, sf::Color& color, unsigned int& outline = 0, sf::Color& color = sf::Color::Black)
        : Rect(x1, y1, x2, y2, color, outline, color)
    {

    }

    ~Panel()
    {

    }
}
