/*
/ Options menu
/ Author: Victor Rådmark
/ Created: 2011-02-14
/ Updated: 2011-02-15
/ License: GPL v3
*/
#include <string>
#include <algorithm>
#include <vector>

#include <SFML/Graphics.hpp>

#include "menu.h"
#include "particlesystem.h"
#include "imagehandler.h"
#include "configreader.h"
#include "optionsmenu.h"

namespace sbe
{
    OptionsMenu::OptionsMenu(void* callObject, void (*backFunction) (void* object), const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cReader, const sf::Vector2i& r, const sf::Font& font, const sf::Vector2f& psPos, const sf::Vector2i& next)
        : Menu(psFile, imgHandler, cReader, r, psPos, next)
    {
        cfgReader = cReader;
        createString("options", "SBE - Options", font, 34, sf::Vector2f(0, 0));
        strings["options"].SetCenter(strings["options"].GetRect().GetWidth() / 2, strings["options"].GetRect().GetHeight() / 2);
        strings["options"].SetPosition(sf::Vector2f(res.x / 2 - 17, 109));
        createButton("incrRes", this, incrRes, sf::String("", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 175), sf::Vector2f(280, 215), sf::Color(30, 30, 50, 0), 1, sf::Color::White);
        //TODO(Liag#5#): Back function
        createButton("back", callObject, backFunction, sf::String("Back", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 395), sf::Vector2f(280, 435), sf::Color(80, 30, 30, 80), 1, sf::Color::White);
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

    void OptionsMenu::setRes(const bool& incr)
    {
        resVector::const_iterator it = find(cfgReader->getResList().begin(), cfgReader->getResList().end(), cfgReader->getRes());
        unsigned int resPos = it - cfgReader->getResList().begin();

        if(incr)
        {
            if(resPos + 1 == cfgReader->getResList().size())
                cfgReader->setRes(cfgReader->getResList().at(0));
            else
                cfgReader->setRes(cfgReader->getResList().at(resPos + 1));
        }
        else
        {
            if(resPos == 0)
                cfgReader->setRes(cfgReader->getResList().at(cfgReader->getResList().size() - 1));
            else
                cfgReader->setRes(cfgReader->getResList().at(resPos - 1));
        }
    }
}
