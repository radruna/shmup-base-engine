/*
/ Drawable class with z value.
/ Author: Victor Rådmark
/ File created: 2011-04-13
/ File updated: 2011-04-13
/ License: GPLv3
*/
#include "drawable.h"

namespace sbe
{
    int Drawable::globId = 0;

    Drawable::Drawable(int zLevel)
        : sf::Drawable(), z(zLevel), id(globId++)
    { }

    Drawable::Drawable(const sf::Vector2f& Position, const sf::Vector2f& Scale, float Rotation, const sf::Color& Col)
        : sf::Drawable(Position, Scale, Rotation, Col), id(globId++)
    {}
}
