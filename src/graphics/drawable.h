/*
/ Drawable class with z value.
/ Author: Victor Rådmark
/ File created: 2011-03-04
/ File updated: 2011-03-05
/ License: GPLv3
*/
#ifndef DRAWABLE_H_INCLUDED
#define DRAWABLE_H_INCLUDED

#include <SFML/Graphics.hpp>

namespace sbe
{
    class Drawable : public sf::Drawable
    {
        public:
            Drawable(int zLevel = 0) : sf::Drawable(), z(zLevel) { }
            Drawable(const sf::Vector2f& Position, const sf::Vector2f& Scale, float Rotation, const sf::Color& Col)
             : sf::Drawable(Position, Scale, Rotation, Col)
            {}
            virtual void update(const float& elapsed) {};

            int getZPos()
            {
                return z;
            }

            void setZPos(int zPos)
            {
                z = zPos;
            }
        protected:
            int z;
    };
}

#endif
