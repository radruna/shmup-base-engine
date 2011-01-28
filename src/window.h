/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-01-28
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output
#include <string> //For strings
#include <map> //Map for objects

#include <SFML/Graphics.hpp> //Pretty much everything else

#include "imagehandler.h" //Loading images
#include "audiohandler.h" //Playing sound/music
#include "eventhandler.h" //Handles events
#include "ship.h" //Ship class
//#include "player.h" //Player class
#include "panel.h"

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
                   const std::string& Title = "SBE", //The window title
                   const bool& showIntro = true,
                   unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close, //Style of the window, used for fullscreen etc
                   const sf::WindowSettings& Params = sf::WindowSettings()); //Setting params, used for stuff like bit depth and AA
            ~Window();

            int exec(); //Main game loop
        private:
            void loadFonts(const std::string& fontFile);
            void unloadFonts()
            {
                fonts.clear();
            }

            static void buttonClicked()
            {
                std::cout << "Button clicked." << std::endl;
            }

            sbe::ImageHandler *imgHandler;
            sbe::AudioHandler *audHandler;
            sbe::EventHandler *evtHandler; //One of several
            //sbe::Panel *mainMenu;
            //DebugHandler?
            std::map<std::string, Ship> *ships;
            sbe::Ship *testShip;
            sbe::Panel *testPanel;

            sf::Vector2i res;
            bool pause;

            sf::Color c;
            short cCount;

            boolMap events;
            fontMap fonts;
    };
}

#endif
