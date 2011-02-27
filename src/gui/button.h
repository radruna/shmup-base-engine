/*
/ Button class
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-02-27
/ License: GPLv3
*/
#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "../sys/util.h"

namespace sbe
{
    class Button : public sf::Drawable
    {
        public:
            Button();
            Button(void* callObject,
                   void (*callFunction) (void* object),
                   const sf::String& text,
                   const sf::Color& txtCol,
                   const sf::Vector2f& p1,
                   const sf::Vector2f& p2,
                   const sf::Color& color,
                   const float& outline = 1,
                   const sf::Color& outlineColor = sf::Color::White);
            Button(void* callObject,
                   void (*callFunction) (void* object),
                   const sf::String& text,
                   const sf::Color& txtCol,
                   const sf::Vector2f& p1,
                   const sf::Vector2f& p2,
                   const sf::Vector2f& p3,
                   const sf::Color& color,
                   const float& outline = 1,
                   const sf::Color& outlineColor = sf::Color::White);
            ~Button();
            //Check if mouse click is within bounds and if so execute callback
            void click(const sf::Vector2i& mousePos);

            void setTextColor(const sf::Color& txtCol)
            {
                string.SetColor(txtCol);
            }

        protected:
            virtual void Render(sf::RenderTarget& target) const;
            sf::Shape *buttonRect;
            sf::String string;
            void* funcObject; //The object which the callback function is a member of
            //The callback function has to be implemented as a wrapper to the actual function
            void (*buttonFunc) (void* object);
    };
}

#endif
