/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2010-01-18
/ File updated: 2011-01-21
/ License: GPLv3
*/

#include <SFML/Graphics.hpp>

#include "panel.h"

namespace sbe
{
    Panel::Panel(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        panelRect = new sf::Shape(sf::Shape::Rectangle(p1, p2, color, outline, outlineColor));
    }

    Panel::~Panel()
    {

    }

    Panel::Draw()
    {
        Draw(*panelRect);
    }
}
