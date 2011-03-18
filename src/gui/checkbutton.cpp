/*
/ Check button class
/ Author: Victor Rådmark
/ File created: 2011-02-21
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include <SFML/Graphics.hpp>

#include "../sys/logger.h"
#include "../sys/util.h"
#include "button.h"
#include "checkbutton.h"

namespace sbe
{
    CheckButton::CheckButton()
        : Button(), checked(false)
    {}

    CheckButton::CheckButton(void* callObject, void (*callFunction) (void* object), const bool& c, const sf::String& text, const sf::Color& txtCol, const sf::Vector2f& p1, const sf::Vector2f& p2,
                             const sf::Color& color, const sf::Color& outlineColor)
        : Button(callObject, callFunction, text, txtCol, p1, p2, color, false, 1, outlineColor), checked(c)
    {
        line1 = sf::Shape::Line(p1, p2, 1, outlineColor);
        line2 = sf::Shape::Line(p1.x, p2.y, p2.x, p1.y, 1, outlineColor);
    }

    void CheckButton::click(const sf::Vector2i& mousePos)
    {
        sf::Vector2f pos1 = buttonRect.GetPointPosition(0), pos2 = buttonRect.GetPointPosition(2);

        if(mousePos.x > pos1.x && mousePos.x < pos2.x)
        {
            if(mousePos.y > pos1.y && mousePos.y < pos2.y)
            {
                buttonFunc(funcObject);
                checked = !checked;
            }
        }
    }

    void CheckButton::Render(sf::RenderTarget& target) const
    {
        Button::Render(target);

        if(checked)
        {
            target.Draw(line1);
            target.Draw(line2);
        }
    }
}
