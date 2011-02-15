/*
/ Main menu panel
/ Author: Victor Rådmark
/ Created: 2011-02-11
/ Updated: 2011-02-15
/ License: GPL v3
*/
#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <string>

#include <SFML/Graphics.hpp>

#include "menu.h"
#include "particlesystem.h"
#include "imagehandler.h"
#include "configreader.h"

namespace sbe
{
    class MainMenu : public sbe::Menu
    {
        public:
            MainMenu(void* callObject,
                     void (*selectFunction) (void* object),
                     void (*optionsFunction) (void* object),
                     void (*hiscoreFunction) (void* object),
                     void (*creditsFunction) (void* object),
                     void (*exitFunction) (void* object),
                     const std::string& psFile,
                     ImageHandler* imgHandler,
                     ConfigReader* cfgReader,
                     const sf::Vector2i& r,
                     const sf::Font& font,
                     const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                     const sf::Vector2i& next = sf::Vector2i(-1, -1));
            ~MainMenu() {}
    };
}

#endif
