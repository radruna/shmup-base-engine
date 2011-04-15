/*
/ Event handler class
/ Authors: Jonathan Orrö and Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-03-11
/ License: GPLv3
*/
#include <list> //For maps

#include "eventhandler.h" //Class def

namespace sbe
{
    EventHandler::EventHandler()
    {

    }

    //Handles the events and tells the actions that should act to act
    void EventHandler::processEvents(const sf::Event& evt, bool c)
    {
        if(evt.Type == sf::Event::KeyReleased)
        {
            for(actionMap::iterator it = actions.begin(); it != actions.end(); it++)
                if(!c || it->first == "Console") isKeyReleased(it->second.getKey(), evt) ? it->second.act() : it->second.act(1);
        }
    }

    void EventHandler::processInput(const sf::Input& input)
    {
        if(inputActions.find("Right") != inputActions.end())
        {
            if(input.IsKeyDown(sf::Key::Right) && !input.IsKeyDown(sf::Key::Left))
                inputActions["Right"].act();
            else if(input.IsKeyDown(sf::Key::Left) && !input.IsKeyDown(sf::Key::Right))
                inputActions["Left"].act();

            if(input.IsKeyDown(sf::Key::Up) && !input.IsKeyDown(sf::Key::Down))
                inputActions["Up"].act();
            else if(input.IsKeyDown(sf::Key::Down) && !input.IsKeyDown(sf::Key::Up))
                inputActions["Down"].act();
        }

        for(actionMap::iterator it = inputActions.begin(); it != inputActions.end(); it++)
        {
            if(it->second.getKey() != sf::Key::Right && it->second.getKey() != sf::Key::Left)
            {
                if(it->second.getKey() != sf::Key::Up && it->second.getKey() != sf::Key::Down)
                    input.IsKeyDown(it->second.getKey()) ? it->second.act() : it->second.act(1);
            }
        }
    }

    void EventHandler::addAction(const std::string& name, const sf::Key::Code& keyCode, void* object, void (*func) (void* object))
    {
        Action tmpAction(object, func, keyCode);
        actions[name] = tmpAction;
    }

    void EventHandler::addInputAction(const std::string& name, const sf::Key::Code& keyCode, void* object, void (*func) (void* object))
    {
        Action tmpAction(object, func, keyCode);
        inputActions[name] = tmpAction;
    }

    void EventHandler::addInputAction(const std::string& name, const sf::Key::Code& keyCode, void* object, void (*func) (void* object), void (*otherFunc) (void* object))
    {
        Action tmpAction(object, func, otherFunc, keyCode);
        inputActions[name] = tmpAction;
    }

    bool EventHandler::isKeyReleased(const sf::Key::Code& key, const sf::Event& evt)
    {
        if((evt.Type == sf::Event::KeyReleased) && (evt.Key.Code == key))
            return true;
        else
            return false;
    }
}

