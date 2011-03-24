/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-03-23
/ License: GPL v3
*/
#include <SFML/Graphics.hpp>

#include "menu.h"
#include "selectmenu.h"

namespace sbe
{
    SelectMenu::SelectMenu()
        : funcObject(NULL), loadFunc(NULL)
    {}

    SelectMenu::SelectMenu(void* callObject, void (*loadFunction) (void* object, const int& map, bool selected), void (*backFunction) (void* object), ConfigReader* cReader, const sf::Vector2i& r, const sf::Font& font)
        : Menu(r), select(false)
    {
        createString("select", "SBE - Select stage", font, 34, sf::Vector2f(0, 0));
        strings["select"].SetCenter(strings["select"].GetRect().GetWidth() / 2, strings["select"].GetRect().GetHeight() / 2);
        strings["select"].SetPosition(sf::Vector2f(res.x / 2 - 17, 108.5));

        createButton("select", this, loadLevel, sf::String("Test level", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 175), sf::Vector2f(280, 215), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);

        createButton("back", callObject, backFunction, sf::String("Back", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, res.y - 165), sf::Vector2f(280, res.y - 125), sf::Color(80, 30, 30, 80), true, 1, sf::Color::White);

        funcObject = callObject;
        loadFunc = loadFunction;
    }

    void SelectMenu::loadLevel(void* object)
    {
        //Explicitly cast to a pointer to SelectMenu
        SelectMenu* self = (SelectMenu*) object;

        //Call member
        self->load();
    }

    void SelectMenu::load(const int& map)
    {
        loadFunc(funcObject, map, select);
        select = true;
    }
}
