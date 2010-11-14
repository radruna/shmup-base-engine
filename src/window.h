/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-14
/ License: GPLv3
*/
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Pretty much everything else

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
                   unsigned long WindowStyle = sf::Style::Resize | sf::Style::Close, //Style of the window, used for fullscreen etc
                   const sf::WindowSettings& Params = sf::WindowSettings()); //Setting params, used for stuff like bit depth and AA
            ~Window()
            {

            }

            int exec(); //Main game loop
        private:
            //Add event handling (friend class/functions?)
            //and debug stuff
            //and vectors with stuff
    };
}
#endif WINDOW_H_INCLUDED
