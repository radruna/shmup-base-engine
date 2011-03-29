/*
/ Console panel
/ Author: Victor Rådmark
/ Created: 2011-03-29
/ Updated: 2011-03-29
/ License: GPL v3
*/
#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../sys/logger.h"
#include "panel.h"
#include "console.h"

namespace sbe
{
    Console::Console(const sf::Vector2i& res, const sf::Font& f)
        : Panel(sf::Vector2f(1, 1), sf::Vector2f(res.x - 1, 300), sf::Color(0, 0, 0, 150), 1, sf::Color::White), font(f)
    {
    }

    Console::~Console()
    {
        //commands.clear();
        history.clear();
        strings.clear();
    }

    void Console::click(const sf::Vector2i& mousePos)
    {

    }

    void Console::hover(const sf::Vector2i& mousePos)
    {

    }

    void Console::update()
    {
        StrVec tmpLog = Logger::getLog();
        if(!tmpLog.empty())
        {
            for(unsigned int i = 0; i < tmpLog.size(); i++)
                addString(tmpLog.at(i));

            while(strings.size() > 30) removeString();
        }
    }

    void Console::Render(sf::RenderTarget& target) const
    {
        Panel::Render(target);
        for(unsigned int i = 0; i < strings.size(); i++)
            target.Draw((strings.at(i)));
    }

    void Console::addString(const std::string& str)
    {
        history.push_back(str);
        int pos = 2;
        if(!strings.empty()) pos = strings.back().GetPosition().y + 16;
        sf::String tmpStr(history.back(), font, 14.f);
        tmpStr.SetColor(sf::Color::White);
        tmpStr.SetPosition(5, pos);
        strings.push_back(tmpStr);
    }

    void Console::removeString()
    {
        strings.erase(strings.begin());
    }
}
