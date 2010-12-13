/*
/ Event handler class
/ Author: Jonathan Orrö
/ File created: 2010-11-30
/ File updated: 2010-12-13
/ License: GPLv3
*/

#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include <map> //For maps
#include <string> //For strings

#include <SFML/Window.hpp> //Event header

namespace sbe
{
    class EventHandler
    {
        /*
            Handles events
        */
        public:

            EventHandler();
            ~EventHandler()
            {

            }

            //Returns what buttons are being pressed
            std::map<std::string, bool> returnEvents(sf::Event evt);

        private:

            bool isKeyReleased(sf::Key::Code key, sf::Event evt);

            std::map<std::string, bool> keyReleased;



    };
}

#endif
