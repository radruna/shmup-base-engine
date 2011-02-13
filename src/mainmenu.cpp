/*
/ Main menu panel
/ Author: Victor Rådmark
/ Created: 2011-02-11
/ Updated: 2011-02-13
/ License: GPL v3
*/
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "panel.h"
#include "particlesystem.h"
#include "imagehandler.h"
#include "configreader.h"
#include "mainmenu.h"

namespace sbe
{
    MainMenu::MainMenu(void* callObject, void (*selectFunction) (void* object), void (*optionsFunction) (void* object), void (*hiscoreFunction) (void* object), void (*creditsFunction) (void* object), void (*exitFunction) (void* object),
                       const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cfgReader, const sf::Vector2i& r, const sf::Font& font)
        : Panel(sf::Vector2f(75, 75), sf::Vector2f(r.x - 75, r.y - 75), sf::Color(50, 80, 80, 25), 1, sf::Color::White), res(r)
    {
        createString("hello", "SBE - Main menu", font, 34, sf::Vector2f(0, 0));
        strings["hello"].SetCenter(strings["hello"].GetRect().GetWidth() / 2, strings["hello"].GetRect().GetHeight() / 2);
        strings["hello"].SetPosition(sf::Vector2f(res.x / 2, 105));
        createButton("select", callObject, selectFunction, sf::String("Select map", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 175), sf::Vector2f(265, 215), sf::Color(30, 30, 50, 0), 1, sf::Color::White);
        pSystem = new ParticleSystem(psFile, imgHandler, cfgReader->getSetting<float>("ps_reload"));
        pSystem->SetPosition(res.x / 2, res.y / 2);
        nextPos = sf::Vector2i(res.x / 2, res.y / 2);
    }

    void MainMenu::update(const float& elapsed)
    {
        if(pSystem->GetPositionX() == nextPos.x && pSystem->GetPositionY() == nextPos.y)
        {
            nextPos.x = sf::Randomizer::Random(0, res.x / 5) * 5;
            nextPos.y = sf::Randomizer::Random(0, res.y / 5) * 5;
        }
        else
        {
            int x = pSystem->GetPositionX(), y = pSystem->GetPositionY();

            if(x > nextPos.x)
                x -= 5;
            else if(x < nextPos.x)
                x += 5;

            if(y > nextPos.y)
                y -= 5;
            else if(y < nextPos.y)
                y += 5;

            pSystem->SetPosition(x, y);
        }

        pSystem->update(elapsed);
    }

    void MainMenu::Render(sf::RenderTarget& target) const
    {
        target.Draw(*pSystem);
        target.Draw(*panelRect);
        for(buttonMap::const_iterator it = buttons.begin(); it != buttons.end(); it++)
        {
            target.Draw(it->second);
        }
        for(stringMap::const_iterator it = strings.begin(); it != strings.end(); it++)
        {
            target.Draw(it->second);
        }
    }
}
