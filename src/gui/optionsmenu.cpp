/*
/ Options menu
/ Author: Victor Rådmark
/ Created: 2011-02-14
/ Updated: 2011-02-21
/ License: GPL v3
*/
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../graphics/particlesystem.h"
#include "../graphics/imagehandler.h"
#include "../sys/configreader.h"
#include "menu.h"
#include "optionsmenu.h"

namespace sbe
{
    OptionsMenu::OptionsMenu(void* callObject, void (*applyFunction) (void* object), void (*backFunction) (void* object), const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cReader, const sf::Vector2i& r, const sf::Font& font,
                             const sf::Vector2f& psPos, const sf::Vector2i& next)
        : Menu(psFile, imgHandler, cReader, r, psPos, next)
    {
        cfgReader = cReader;

        createString("options", "SBE - Options", font, 34, sf::Vector2f(0, 0));
        strings["options"].SetCenter(strings["options"].GetRect().GetWidth() / 2, strings["options"].GetRect().GetHeight() / 2);
        strings["options"].SetPosition(sf::Vector2f(res.x / 2 - 17, 108.5));

        createString("res", "Resolution ", font, 30, sf::Vector2f(110, 168));
        createButton("decrRes", this, decrRes, sf::String("", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(281, 190), sf::Vector2f(305, 202), sf::Vector2f(305, 178), sf::Color(30, 30, 50, 0), 1, sf::Color::White);

        std::string curRes = cfgReader->getSetting<std::string>("width") + "x" + cfgReader->getSetting<std::string>("height");
        createString("curRes", curRes, font, 30, sf::Vector2f(312, 168));
        strings["curRes"].SetCenter(strings["curRes"].GetRect().GetWidth() / 2, strings["curRes"].GetRect().GetHeight() / 2);
        strings["curRes"].SetPosition(378, 184);

        createButton("incrRes", this, incrRes, sf::String("", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(455, 178), sf::Vector2f(455, 202), sf::Vector2f(479, 190), sf::Color(30, 30, 50, 0), 1, sf::Color::White);

        createString("fs", "Fullscreen ", font, 30, sf::Vector2f(110, 212));
        createCheckButton("fs", this, toggleFS, cfgReader->getSetting<int>("fullscreen"), sf::String("", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(280, 220), sf::Vector2f(310, 250), sf::Color(30, 30, 50, 0), sf::Color::White);

        createString("vsync", "Vertical sync ", font, 30, sf::Vector2f(110, 256));
        createCheckButton("vsync", this, toggleVSync, cfgReader->getSetting<int>("vsync"), sf::String("", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(280, 264), sf::Vector2f(310, 294), sf::Color(30, 30, 50, 0), sf::Color::White);

        createButton("apply", callObject, applyFunction, sf::String("Apply", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, res.y - 220), sf::Vector2f(280, res.y - 180), sf::Color(30, 80, 30, 80), true, 1, sf::Color::White);
        createButton("back", callObject, backFunction, sf::String("Back", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, res.y - 165), sf::Vector2f(280, res.y - 125), sf::Color(80, 30, 30, 80), true, 1, sf::Color::White);
    }

    void OptionsMenu::incrRes(void* object)
    {
        //Explicitly cast to a pointer to OptionsMember
        OptionsMenu* self = (OptionsMenu*) object;

        //Call member
        self->setRes(1);
    }

    void OptionsMenu::decrRes(void* object)
    {
        //Explicitly cast to a pointer to OptionsMember
        OptionsMenu* self = (OptionsMenu*) object;

        //Call member
        self->setRes(0);
    }

    void OptionsMenu::toggleFS(void* object)
    {
        //Explicitly cast to a pointer to OptionsMember
        OptionsMenu* self = (OptionsMenu*) object;

        //Call member
        self->setFS();
    }

    void OptionsMenu::toggleVSync(void* object)
    {
        //Explicitly cast to a pointer to OptionsMember
        OptionsMenu* self = (OptionsMenu*) object;

        //Call member
        self->setVS();
    }

    void OptionsMenu::setRes(const bool& incr)
    {
        /*
            Purpose: Set the window resolution to the value contained in the next or previous position of the cfgReader's resList.
        */
        unsigned int resPos = 0;
        resVector resList = cfgReader->getResList();
        for(resVector::iterator it = resList.begin(); it != resList.end(); it++)
        {
            if((*it) == cfgReader->getRes())
                break;
            resPos++;
        }

        if(incr)
        {
            if(resPos + 1 == resList.size())
                cfgReader->setRes(resList.at(0));
            else
                cfgReader->setRes(resList.at(resPos + 1));
        }
        else
        {
            if(resPos == 0)
                cfgReader->setRes(resList.at(resList.size() - 1));
            else
                cfgReader->setRes(resList.at(resPos - 1));
        }

        strings["curRes"].SetText(cfgReader->getSetting<std::string>("width") + "x" + cfgReader->getSetting<std::string>("height"));
        strings["curRes"].SetCenter(strings["curRes"].GetRect().GetWidth() / 2, strings["curRes"].GetRect().GetHeight() / 2);
        strings["curRes"].SetPosition(378, 184);
    }

    void OptionsMenu::setFS()
    {
        if(cfgReader->getSetting<int>("fullscreen") == 1)
            cfgReader->set<int>("fullscreen", 0);
        else
            cfgReader->set<int>("fullscreen", 1);
    }

    void OptionsMenu::setVS()
    {
        if(cfgReader->getSetting<int>("vsync") == 1)
            cfgReader->set<int>("vsync", 0);
        else
            cfgReader->set<int>("vsync", 1);
    }
}
