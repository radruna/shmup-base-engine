/*
/ Dialog panels, for dialogue.
/ Author: Victor Rådmark
/ Created: 2011-01-31
/ Updated: 2011-02-01
/ License: GPL v3
*/
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "dialogpanel.h"

namespace sbe
{
    DialogPanel::DialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
        : curDiag(0), dialogue(dialog)
    {
        panelRect = new sf::Shape(sf::Shape::Rectangle(sf::Vector2f(20, res.y - 170), sf::Vector2f(600 + res.x / 4, res.y - 20), color, outline, outlineColor));
        createString("dialogString", dialog.at(curDiag), fonts["inconsolata"], 24, sf::Vector2f(30, 560));
        createButton("")
    }

    DialogPanel::createButton(const std::string& name, void (*callFunction) (void* object), const sf::Vector2i& p1, const sf::Vector2f& p2, const std::string& text, const sf::Color& txtCol,  const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        /*
            Purpose: Create a new button based on parameters, many of which are default.
        */
        sbe::Button tmpBtn(this, callFunction, text, txtCol, p1, p2, color, outline, outlineColor);
        buttons[name] = tmpBtn;
    }

    DialogPanel::next(void* object)
    {
        /*
            Go to the next line of dialogue in the called panel.
        */
        strings["dialogString"] = dialog.at(curDiag++);
    }
}
