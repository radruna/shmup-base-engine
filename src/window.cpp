/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <map> //For mapping objects

#include <SFML/Graphics.hpp> //Graphics and everything above

#include "window.h" //Class def
//#include "imagehandler.h" //Not done yet
//#include "eventhandler.h"
//#include "panel.h"

namespace sbe
{
    PlatformGame::PlatformGame(sf::VideoMode Mode, const std::string& Title, const bool& showIntro, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, Title, WindowStyle, Params)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        //imgHandler = new sbe::ImageHandler();
        //evtHandler = new sbe::EventHandler();
        //mainMenu = new sbe::Panel();
    }

    int PlatformGame::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */
        sf::Clock clock; //For frame checking etc

        while(IsOpened())
        {
            //Loop the loop and output stuff worth outputting, ideally whilst fighting the power
            //Display the intro and then the main menu
            //evtHandler.Handle(); //hurr!!!
        }

        return 0;
    }
}
