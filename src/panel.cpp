/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-18
/ File updated: 2011-02-13
/ License: GPLv3
*/
#include <iostream>
#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "panel.h"
#include "logger.h"
#include "button.h"

namespace sbe
{
    Panel::Panel(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        panelRect = new sf::Shape(sf::Shape::Rectangle(p1, p2, color, outline, outlineColor));
    }

    Panel::~Panel()
    {
        delete panelRect;
    }

    void Panel::Render(sf::RenderTarget& target) const
    {
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

    void Panel::createString(const std::string& name, const sf::String string)
    {
        strings[name] = string;
    }

    void Panel::createString(const std::string& name, const sf::Unicode::Text& text, const sf::Font& font, const float& size, const sf::Vector2f& pos, const sf::Color& color)
    {
        /*
            Purpose: Create a new string based on paremeters that can be displayed anywhere within the bounds of the panel.
        */
        sf::String tmpStr(text, font, size);
        strings[name] = tmpStr;
        strings[name].SetPosition(pos);
        strings[name].SetColor(color);
    }

    void Panel::createButton(const std::string& name, void* callObject, void (*callFunction) (void* object), const sf::String& text, const sf::Color& txtCol, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        /*
            Purpose: Create a new button based on parameters.
        */
        sbe::Button tmpBtn(callObject, callFunction, text, txtCol, p1, p2, color, outline, outlineColor);
        buttons[name] = tmpBtn;
    }

    bool Panel::withinPanel(const sf::Vector2i& mousePos) const
    {
        if(mousePos.x > panelRect->GetPointPosition(0).x && mousePos.x < panelRect->GetPointPosition(2).x)
        {
            if(mousePos.y > panelRect->GetPointPosition(0).y && mousePos.y < panelRect->GetPointPosition(2).y)
                return true;
        }

        return false;
    }

    void Panel::click(const sf::Vector2i& mousePos)
    {
        if(withinPanel(mousePos))
        {
            for(buttonMap::iterator it = buttons.begin(); it != buttons.end(); it++)
            {
                it->second.click(mousePos);
            }
        }
    }
}
