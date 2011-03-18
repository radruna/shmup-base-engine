/*
/ Menu panels base class
/ Author: Victor Rådmark
/ Created: 2011-02-14
/ Updated: 2011-02-27
/ License: GPL v3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "../graphics/particlesystem.h"
#include "../graphics/imagehandler.h"
#include "../sys/configreader.h"
#include "../sys/util.h"
#include "panel.h"
#include "menu.h"

namespace sbe
{
    Menu::Menu(const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cfgReader, const sf::Vector2i& r, const sf::Vector2f& psPos, const sf::Vector2i& next)
        : Panel(sf::Vector2f(75, 75), sf::Vector2f(r.x - 75, r.y - 75), sf::Color(50, 80, 80, 25), 1, sf::Color::White), res(r)
    {
        pSystem = new ParticleSystem(psFile, imgHandler, cfgReader->getSetting<float>("ps_reload"));

        if(psPos.x != -1)
        {
            pSystem->SetPosition(psPos.x, psPos.y);
            nextPos = sf::Vector2i(next.x, next.y);
        }
        else
        {
            pSystem->SetPosition(res.x / 2, res.y / 2);
            nextPos = sf::Vector2i(res.x / 2, res.y / 2);
        }
    }

    Menu::~Menu()
    {
        safeDelete(pSystem);
    }

    void Menu::update(const float& elapsed)
    {
        if(pSystem == NULL) return;

        if(pSystem->GetPositionX() == nextPos.x && pSystem->GetPositionY() == nextPos.y)
        {
            nextPos.x = sf::Randomizer::Random(0, res.x / 5) * 5;
            nextPos.y = sf::Randomizer::Random(0, res.y / 5) * 5;
        }
        else
        {
            int x = pSystem->GetPositionX(), y = pSystem->GetPositionY();

            for(int i = 0; i < 5; i++)
            {
                if(x == nextPos.x)
                    break;
                else if(x > nextPos.x)
                    x--;
                else
                    x++;
            }

            for(int i = 0; i < 5; i++)
            {
                if(y == nextPos.y)
                    break;
                else if(y > nextPos.y)
                    y--;
                else
                    y++;
            }

            pSystem->SetPosition(x, y);
        }

        pSystem->update(elapsed);
    }

    void Menu::Render(sf::RenderTarget& target) const
    {
        if(pSystem != NULL) target.Draw(*pSystem);

        Panel::Render(target);
    }
}
