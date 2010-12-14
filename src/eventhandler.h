/*
/ Event handler class
/ Author: Jonathan Orrö
/ File created: 2010-11-30
/ File updated: 2010-12-14
/ License: GPLv3
*/

#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include <map> //For maps
#include <string> //For strings

#include <SFML/Window.hpp> //Event header

typedef std::map<std::string, bool> boolMap;

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
            static void returnEvents(sf::Event evt, boolMap& keyReleased);

        private:

            static bool isKeyReleased(sf::Key::Code key, sf::Event evt);

            //boolMap keyReleased;
    };
}

#endif
