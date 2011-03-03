/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-02-21
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output
#include <string> //For strings
#include <map> //Map for objects
#include <list> //For lists

#include <SFML/Graphics.hpp> //Pretty much everything else

#include "../sys/logger.h"
#include "../sys/util.h"
#include "../sys/eventhandler.h" //Event handling
#include "../sys/configreader.h" //Loads settings
#include "../audio/audiohandler.h" //For loading and playing sound and music
#include "../gui/panel.h"
#include "../gui/mainmenu.h"
#include "../gui/optionsmenu.h"
#include "../game/entity.h"
#include "../game/ship.h"
//#include "../game/player.h"
#include "../game/weapon.h"
#include "imagehandler.h" //For loading images
#include "background.h"; // Background layers

typedef std::map<std::string, bool> boolMap;
typedef std::map<std::string, sf::Font> fontMap;
typedef std::list<sf::Drawable*> RenderList;

namespace sbe
{
    class Window : public sf::RenderWindow, public sbe::FileHandler
    {
        /*
            The Window class is simply an extension of the default RenderWindow class that acts as the container for the rest of the game.
        */
        public:
            Window(sf::VideoMode Mode, //The video mode of the window, used for res etc
                   ConfigReader* reader, //Loads all the settings and stuff
                   unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close, //Style of the window, used for fullscreen etc
                   const sf::WindowSettings& Params = sf::WindowSettings()); //Setting params, used for stuff like bit depth and AA
            ~Window();

            bool exec(); //Main game loop, returns respawn

        private:
            void loadFonts(const std::string& fontFile);
            void unloadFonts()
            {
                fonts.clear();
            }

            static void select(void* object);
            static void options(void* object);
            static void hiscore(void* object);
            static void credits(void* object);
            static void exit(void* object);
            static void apply(void* object);
            static void back(void* object);

            void loadStuff(const int& map = 0);
            void showOptions();
            void showHiScore() {}
            void showCredits() {}
            void applyOptions();
            void goBack();

            sbe::ImageHandler *imgHandler;
            sbe::AudioHandler *audHandler;
            sbe::EventHandler *evtHandler;
            sbe::ConfigReader *cfgReader;
            sbe::MainMenu *mainMenu;
            sbe::OptionsMenu *optionsMenu;
            std::map<std::string, Ship> *ships;
            sbe::Ship *testShip;
            sbe::Panel *testPanel;
            sbe::ParticleSystem *pSystem1;
            sbe::ParticleSystem *pSystem2;
            sbe::Weapon *wpn1;
            sbe::Music *loli;
            sbe::Background *scroll; // test

            sf::Vector2i res;
            bool respawn,
                 pause,
                 menu,
                 opt;
            short count;

            boolMap events;
            fontMap fonts;

            RenderList renderList;
            std::list<Projectile> projectileList;
    };
}

#endif
