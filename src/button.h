/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-01-28
/ License: GPLv3
*/
#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

namespace sbe
{
    class Button : public sf::Drawable
    {
        public:
            Button();
            ~Button();
            void click(const sf::Vector2i& mousePos);
        private:
            sf::Shape *buttonRect;
            sf::String string;
            void* funcObject; //The object which the callback function is a member of
            //The callback function has to be implemented as a wrapper to the actual function
            void (*buttonFunc) (void* object, const sf::Unicode::Text& text);
    };
}

#endif
