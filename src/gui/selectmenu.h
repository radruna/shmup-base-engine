/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-05-19
/ License: GPL v3
*/
#ifndef SELECTMENU_H_INCLUDED
#define SELECTMENU_H_INCLUDED

#include <vector>

#include <SFML/Graphics.hpp>

#include "menu.h"

namespace sbe
{
    class SelectMenu : public sbe::Menu, public sbe::FileHandler
    {
        public:
            SelectMenu();
            SelectMenu(void* callObject,
                       void (*loadFunction) (void* object, const std::string& map),
                       void (*backFunction) (void* object),
                       ConfigReader* cReader,
                       const sf::Vector2i& r,
                       const sf::Font& font);
            ~SelectMenu() {}

        private:
            static void loadLevel(void* object, const std::string& map);

            void load(const std::string& map = "");

            void loadMaps(const sf::Font& font, const std::string& mapFile);

            void *funcObject;
            void (*loadFunc) (void* object, const std::string& map);
    };
}

#endif
