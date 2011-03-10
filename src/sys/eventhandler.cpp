/*
/ Event handler class
/ Author: Jonathan Orrö
/ File created: 2010-11-30
/ File updated: 2010-12-22
/ License: GPLv3
*/

#include <map> //For maps

#include "eventhandler.h" //Class def

namespace sbe
{
    EventHandler::EventHandler()
    {

    }

    //Handles the events and tells the actions that should act to act
    void EventHandler::processEvents(const sf::Event& evt)
    {
        if(evt.Type == sf::Event::KeyReleased)
        {
            for(actionList::iterator it = actions.begin(); it != actions.end(); it++)
                isKeyReleased(it->getKey(), evt) ? it->act() : it->act(1);
        }
    }

    void EventHandler::processInput(const sf::Input& input)
    {
        for(actionList::iterator it = inputActions.begin(); it != inputActions.end(); it++)
            input.IsKeyDown(it->getKey()) ? it->act() : it->act(1);
    }

    void EventHandler::addAction(const sf::Key::Code& keyCode, void* object, void (*func) (void* object))
    {
        Action tmpAction(object, func, keyCode);
        actions.push_back(tmpAction);
    }

    void EventHandler::addInputAction(const sf::Key::Code& keyCode, void* object, void (*func) (void* object))
    {
        Action tmpAction(object, func, keyCode);
        inputActions.push_back(tmpAction);
    }

    void EventHandler::addInputAction(const sf::Key::Code& keyCode, void* object, void (*func) (void* object), void (*otherFunc) (void* object))
    {
        Action tmpAction(object, func, otherFunc, keyCode);
        inputActions.push_back(tmpAction);
    }

    bool EventHandler::isKeyReleased(const sf::Key::Code& key, const sf::Event& evt)
    {
        if((evt.Type == sf::Event::KeyReleased) && (evt.Key.Code == key))
            return true;
        else
            return false;
    }
}

