/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-16
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output
#include <string> //For strings
#include <map> //Map for objects

#include <SFML/Graphics.hpp> //Pretty much everything else

#include "imagehandler.h"
//#include "eventhandler.h" //Not done yet
//#include "panel.h"

namespace sbe
{
    class Window : public sf::RenderWindow
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
            sbe::ImageHandler *imgHandler;
            //sbe::EventHandler *evtHandler; //One of several
            //sbe::Panel *mainMenu;
            //DebugHandler?
            std::map<std::string, sf::Sprite> *ships;
            sf::Sprite *testShip;
    };
}
#endif WINDOW_H_INCLUDED
