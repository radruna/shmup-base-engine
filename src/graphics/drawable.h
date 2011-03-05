/*
/ Drawable class with z value.
/ Author: Victor Rådmark
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sbe
{
    class Drawable : sf::Drawable
    {
        private:
            int z;
    };
}
