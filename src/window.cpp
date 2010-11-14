/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-14
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Graphics and everything above

#include "window.h" //Class def

PlatformGame::PlatformGame(sf::VideoMode Mode, const std::string& Title, unsigned long WindowStyle, const sf::WindowSettings& Params)
    : RenderWindow(Mode, Title, WindowStyle, Params)
{
    /*
        Purpose: Constructor for sbe::Window.
    */
    //Construct stuff
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
    }

    return 0;
}
