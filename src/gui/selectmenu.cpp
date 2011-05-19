/*
/ Select menu
/ Author: Victor Rådmark
/ Created: 2011-03-12
/ Updated: 2011-05-19
/ License: GPL v3
*/
#include <sstream>

#include <SFML/Graphics.hpp>

#include "menu.h"
#include "selectmenu.h"
#include "../sys/logger.h"

namespace sbe
{
    SelectMenu::SelectMenu()
        : funcObject(NULL), loadFunc(NULL)
    {}

    SelectMenu::SelectMenu(void* callObject, void (*loadFunction) (void* object, const std::string& map), void (*backFunction) (void* object), ConfigReader* cReader, const sf::Vector2i& r, const sf::Font& font)
        : Menu(r, sf::Color(50, 80, 80, 150))
    {
        createString("select", "SBE - Select stage", font, 30, sf::Vector2f(0, 0));
        strings["select"].SetCenter(strings["select"].GetRect().GetWidth() / 2, strings["select"].GetRect().GetHeight() / 2);
        strings["select"].SetPosition(sf::Vector2f(res.x / 2 - 17, 108.5));

        loadMaps(font, "scripts/maps.ast");
        //createButton("map01", this, loadLevel, sf::String("Test level", font, 20), sf::Color(225, 225, 225, 255), sf::Vector2f(125, 175), sf::Vector2f(280, 215), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
        createButton("back", callObject, backFunction, sf::String("Back", font, 20), sf::Color(225, 225, 225, 255), sf::Vector2f(125, res.y - 165), sf::Vector2f(280, res.y - 125), sf::Color(80, 30, 30, 80), true, 1, sf::Color::White);
        funcObject = callObject;
        loadFunc = loadFunction;
    }

    void SelectMenu::loadLevel(void* object, const std::string& map)
    {
        //Explicitly cast to a pointer to SelectMenu
        SelectMenu* self = (SelectMenu*) object;

        //Call member
        self->load(map);
    }

    void SelectMenu::load(const std::string& map)
    {
        loadFunc(funcObject, map);
    }

    void SelectMenu::loadMaps(const sf::Font& font, const std::string& mapFile)
    {
        /*
            Purpose: Load the map file names and then create the buttons pointing to the maps.
        */
        std::ifstream fileReader;
        Logger::writeMsg(1) << "\nLoading assets from: \"" << mapFile << "\"...";
        //Open specified file
        fileReader.open(mapFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The map handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string mapKey;
        std::string mapPath;
        int pos = 175;
        //Read line
        while(getline(fileReader, output))
        {
            //Check if line is empty and perform string operation
            if(strReadLine(output, mapKey, mapPath))
            {
                createButton(mapPath, this, loadLevel, sf::String(mapKey, font, 20), sf::Color(225, 225, 225, 255), sf::Vector2f(125, pos), sf::Vector2f(280, (pos + 40)), sf::Color(30, 30, 50, 0), true, 1, sf::Color::White);
                pos += 55;
            }
        }

        //Debug output
        Logger::writeMsg(1) << "Finished loading maps from \"" << mapFile << "\"";
        //Close file
        fileReader.close();
    }
}
