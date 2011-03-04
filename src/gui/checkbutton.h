/*
/ Check button class
/ Author: Victor Rådmark
/ File created: 2011-02-21
/ File updated: 2011-03-04
/ License: GPLv3
*/
#ifndef CHECKBUTTON_H_INCLUDED
#define CHECKBUTTON_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "button.h"

namespace sbe
{
    class CheckButton : public sbe::Button
    {
        public:
            CheckButton();
            CheckButton(void* callObject,
                        void (*callFunction) (void* object),
                        const bool& c,
                        const sf::String& text,
                        const sf::Color& txtCol,
                        const sf::Vector2f& p1,
                        const sf::Vector2f& p2,
                        const sf::Color& color,
                        const sf::Color& outlineColor = sf::Color::White);
            ~CheckButton();

            void click(const sf::Vector2i& mousePos);

        protected:
            void Render(sf::RenderTarget& target) const;
        private:
            bool checked;
            sf::Shape line1;
            sf::Shape line2;
    };
}

#endif
