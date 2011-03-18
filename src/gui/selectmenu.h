/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-03-17
/ License: GPL v3
*/
#ifndef SELECTMENU_H_INCLUDED
#ifndef SELECTMENU_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "menu.h"

namespace sbe
{
    class SelectMenu : public sbe::Menu
    {
        public:
            SelectMenu(void* callObject,
                       void (*loadFunction) (void* object, const int& map),
                       void (*backFunction) (void* object),
                       const std::string& psFile,
                       ImageHandler* imgHandler,
                       ConfigReader* cReader,
                       const sf::Vector2i& r,
                       const sf::Font& font,
                       const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                       const sf::Vector2i& next = sf::Vector2i(-1, -1));
            ~SelectMenu();

            int getSelected();

        private:



    };
}
