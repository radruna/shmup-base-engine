/*
/ Main menu panel
/ Author: Victor Rådmark
/ Created: 2011-02-11
/ Updated: 2011-02-15
/ License: GPL v3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "../graphics/particlesystem.h"
#include "../graphics/imagehandler.h"
#include "../sys/configreader.h"
#include "menu.h"
#include "mainmenu.h"

namespace sbe
{
    MainMenu::MainMenu(void* callObject, void (*selectFunction) (void* object), void (*optionsFunction) (void* object), void (*hiscoreFunction) (void* object), void (*creditsFunction) (void* object), void (*exitFunction) (void* object),
                       const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cfgReader, const sf::Vector2i& r, const sf::Font& font, const sf::Vector2f& psPos, const sf::Vector2i& next)
        : Menu(psFile, imgHandler, cfgReader, r, psPos, next)
    {
        createString("hello", "SBE - Main menu", font, 34, sf::Vector2f(0, 0));
        strings["hello"].SetCenter(strings["hello"].GetRect().GetWidth() / 2, strings["hello"].GetRect().GetHeight() / 2);
        strings["hello"].SetPosition(sf::Vector2f(res.x / 2, 105));
        createButton("select", callObject, selectFunction, sf::String("Select stage", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 175), sf::Vector2f(280, 215), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
        createButton("options", callObject, optionsFunction, sf::String("Options", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 230), sf::Vector2f(280, 270), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
        createButton("hiscore", callObject, hiscoreFunction, sf::String("High scores", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 285), sf::Vector2f(280, 325), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
        createButton("credits", callObject, creditsFunction, sf::String("Credits", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 340), sf::Vector2f(280, 380), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
        createButton("exit", callObject, exitFunction, sf::String("Quit", font, 24), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 395), sf::Vector2f(280, 435), sf::Color(80, 30, 30, 80), true, 1, sf::Color::White);
    }


}
