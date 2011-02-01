/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-01-29
/ License: GPLv3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "button.h"

namespace sbe
{
    Button::Button(void* callObject, void (*callFunction) (void* object), const sf::String& text, const sf::Color& txtCol, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
        : string(text)
    {
        buttonRect = new sf::Shape(sf::Shape::Rectangle(p1, p2, color, outline, outlineColor));
        string.SetColor(txtCol);
        string.SetPosition(p1.x + 5, p1.y + 2);
        funcObject = callObject;
        buttonFunc = callFunction;
    }

    void Button::Render(sf::RenderTarget& target) const
    {
        target.Draw(*buttonRect);
        target.Draw(string);
    }

    void Button::click(const sf::Vector2i& mousePos)
    {
        if(mousePos.x > buttonRect->GetPointPosition(0).x && mousePos.x < buttonRect->GetPointPosition(2).x)
        {
            if(mousePos.y > buttonRect->GetPointPosition(0).y && mousePos.y < buttonRect->GetPointPosition(2).y)
                buttonFunc(funcObject);
        }
    }
}
