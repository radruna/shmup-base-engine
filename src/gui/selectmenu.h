/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-03-23
/ License: GPL v3
*/
#ifndef SELECTMENU_H_INCLUDED
#define SELECTMENU_H_INCLUDED

#include <vector>

#include <SFML/Graphics.hpp>

#include "menu.h"

namespace sbe
{
    class SelectMenu : public sbe::Menu
    {
        public:
            SelectMenu();
            SelectMenu(void* callObject,
                       void (*loadFunction) (void* object, int map, bool selected),
                       void (*backFunction) (void* object),
                       ConfigReader* cReader,
                       const sf::Vector2i& r,
                       const sf::Font& font);
            ~SelectMenu() {}

            bool isSelected()
            {
                for(unsigned int i = 0; i < selections.size(); i++)
                    if(selections.at(i)) return true;

                return false;
            }

        private:
            static void loadLevel(void* object, const std::string& name);

            void load(int map = 0);

            std::vector<bool> selections;

            void *funcObject;
            void (*loadFunc) (void* object, int map, bool selected);
    };
}

#endif
