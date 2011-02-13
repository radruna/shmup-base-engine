/*
/ Main menu panel
/ Author: Victor Rådmark
/ Created: 2011-02-11
/ Updated: 2011-02-13
/ License: GPL v3
*/
#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "panel.h"
#include "particlesystem.h"
#include "imagehandler.h"
#include "configreader.h"

namespace sbe
{
    class MainMenu : public sbe::Panel
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
                     const sf::Vector2i& res,
                     const sf::Font& font);
            ~MainMenu() {}

            void update(const float& elapsed);
        protected:
            void Render(sf::RenderTarget& target) const;
        private:
            ParticleSystem *pSystem;
            sf::Vector2i res,
            nextPos;
    };
}

#endif
