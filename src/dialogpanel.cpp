/*
/ Dialog panels, for dialogue.
/ Author: Victor Rådmark
/ Created: 2011-01-31
/ Updated: 2011-01-31
/ License: GPL v3
*/
#include <SFML/Graphics.hpp>

#include "dialogpanel.h"

namespace sbe
{
    DialogPanel::DialogPanel(const sf::Vector2i& res, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        panelRect = new sf::Shape(sf::Shape::Rectangle(sf::Vector2f(20, res.y - 170), sf::Vector2f(600 + res.x / 4, res.y - 20), color, outline, outlineColor));
    }
}
