/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-02-16
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output
#include <string> //For strings
#include <map> //Map for objects
#include <list> //For lists

#include <SFML/Graphics.hpp> //Pretty much everything else

#include "imagehandler.h" //Loading images
#include "audiohandler.h" //Playing sound/music
#include "eventhandler.h" //Handles events
#include "configreader.h" //Loads settings
#include "ship.h" //Ship class
#include "projectile.h"
//#include "player.h" //Player class
#include "panel.h"
#include "mainmenu.h"
#include "optionsmenu.h"
#include "logger.h"

typedef std::map<std::string, bool> boolMap;
typedef std::map<std::string, sf::Font> fontMap;

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
            sbe::EventHandler *evtHandler; //One of several
            sbe::ConfigReader *cfgReader;
            sbe::MainMenu *mainMenu;
            sbe::OptionsMenu *optionsMenu;
            std::map<std::string, Ship> *ships;
            sbe::Ship *testShip;
            sbe::Panel *testPanel;
            sbe::ParticleSystem *pSystem1;
            sbe::ParticleSystem *pSystem2;
            sbe::Music *loli;

            sf::Vector2i res;
            bool respawn,
                 pause,
                 menu,
                 opt;

            sf::Color c;
            short count;

            boolMap events;
            fontMap fonts;

            std::list<Projectile> projectileList;
    };
}

#endif
