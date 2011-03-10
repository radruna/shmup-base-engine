/*
/ Event handler class
/ Authors: Jonathan Orrö and Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-03-10
/ License: GPLv3
*/

#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include <list> //For lists
#include <string> //For strings

#include <SFML/Window.hpp> //Event header

#include "action.h"

typedef std::list<sbe::Action> actionList;

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
                actions.clear();
                inputActions.clear();
            }

            //Handles the events and tells the actions that should act to act
            void processEvents(const sf::Event& evt);
            void processInput(const sf::Input& input);

            void addAction(const sf::Key::Code& keyCode,
                            void* object,
                            void (*func) (void* object));
            void addInputAction(const sf::Key::Code& keyCode,
                                 void* object,
                                 void (*func) (void* object));
            void addInputAction(const sf::Key::Code& keyCode,
                                 void* object,
                                 void (*func) (void* object),
                                 void (*otherFunc) (void* object));

        private:
            bool isKeyReleased(const sf::Key::Code& key, const sf::Event& evt);

            actionList actions;
            actionList inputActions;
    };
}

#endif
