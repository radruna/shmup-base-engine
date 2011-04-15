/*
/ Event handler class
/ Authors: Jonathan Orrö and Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-03-10
/ License: GPLv3
*/

#ifndef EVENTHANDLER_H_INCLUDED
#define EVENTHANDLER_H_INCLUDED

#include <map> //For maps
#include <string> //For strings

#include <SFML/Window.hpp> //Event header

#include "action.h"

typedef std::map<std::string, sbe::Action> actionMap;

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
            void processEvents(const sf::Event& evt, bool c = 0);
            void processInput(const sf::Input& input);

            void addAction(const std::string& name,
                            const sf::Key::Code& keyCode,
                            void* object,
                            void (*func) (void* object));
            void addInputAction(const std::string& name,
                                 const sf::Key::Code& keyCode,
                                 void* object,
                                 void (*func) (void* object));
            void addInputAction(const std::string& name,
                                 const sf::Key::Code& keyCode,
                                 void* object,
                                 void (*func) (void* object),
                                 void (*otherFunc) (void* object));

        private:
            bool isKeyReleased(const sf::Key::Code& key, const sf::Event& evt);

            actionMap actions;
            actionMap inputActions;
    };
}

#endif
