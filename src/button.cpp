/*
/ Button class
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-02-21
/ License: GPLv3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "logger.h"

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

    Button::Button(void* callObject, void (*callFunction) (void* object), const sf::String& text, const sf::Color& txtCol, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
        : string(text)
    {
        buttonRect = new sf::Shape();
        buttonRect->AddPoint(p1, color, outlineColor);
        buttonRect->AddPoint(p2, color, outlineColor);
        buttonRect->AddPoint(p3, color, outlineColor);
        buttonRect->SetOutlineWidth(2);
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
        sf::Vector2f pos1 = buttonRect->GetPointPosition(0), pos2 = buttonRect->GetPointPosition(2);

        if(buttonRect->GetNbPoints() == 3)
        {
            pos1.x = buttonRect->GetPointPosition(0).x;
            pos2.x = buttonRect->GetPointPosition(2).x;
            pos2.y = buttonRect->GetPointPosition(1).y;

            if(buttonRect->GetPointPosition(0).y < buttonRect->GetPointPosition(2).y)
                pos1.y = buttonRect->GetPointPosition(0).y;
            else
                pos1.y = buttonRect->GetPointPosition(2).y;
        }

        if(mousePos.x > pos1.x && mousePos.x < pos2.x)
        {
            if(mousePos.y > pos1.y && mousePos.y < pos2.y)
                buttonFunc(funcObject);
        }
    }
}
