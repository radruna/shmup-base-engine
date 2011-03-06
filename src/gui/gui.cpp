/*
/ GUI class
/ Author: Victor Rådmark
/ File created: 2011-03-06
/ File updated: 2010-03-06
/ License: GPLv3
*/
#include <map>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../graphics/drawable.h"
#include "../sys/logger.h"
#include "../sys/util.h"
#include "panel.h"
#include "mainmenu.h"
#include "optionsmenu.h"
#include "dialogpanel.h"
#include "gui.h"

namespace sbe
{
    Gui::Gui(const std::string& fontFile)
        : delMain(false), delOpt(false), delDia(false), fpsCount(0)
    {
        loadFonts(fontFile);

        fps = new sf::String("0", fonts["inconsolata"], 20);
        fps->SetPosition(10, 10);
        fps->SetColor(sf::Color::White);

        mainMenu = NULL;
        optionsMenu = NULL;
        diagPanel = NULL;
    }

    Gui::~Gui()
    {
        panels.clear();
        unloadFonts();
        safeDelete(mainMenu);
        safeDelete(optionsMenu);
        safeDelete(diagPanel);
        safeDelete(fps);
    }

    void Gui::createMainMenu(void* callObject, void (*selectFunction) (void* object), void (*optionsFunction) (void* object), void (*hiscoreFunction) (void* object), void (*creditsFunction) (void* object), void (*exitFunction) (void* object),
                             const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cfgReader, const sf::Vector2i& r, const sf::Vector2f& psPos, const sf::Vector2i& next)
    {
        mainMenu = new MainMenu(callObject, selectFunction, optionsFunction, hiscoreFunction, creditsFunction, exitFunction,  psFile, imgHandler, cfgReader, r, fonts["inconsolata"], psPos, next);
    }

    void Gui::createOptionsMenu(void* callObject, void (*applyFunction) (void* object), void (*backFunction) (void* object), const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cReader, const sf::Vector2i& r, const sf::Vector2f& psPos, const sf::Vector2i& next)
    {
        optionsMenu = new OptionsMenu(callObject, applyFunction, backFunction, psFile, imgHandler, cReader, r, fonts["inconsolata"], psPos, next);
    }

    void Gui::createDialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog)
    {
        diagPanel = new DialogPanel(res, dialog, fonts["inconsolata"]);
    }

    void Gui::createPanel(const std::string& name, const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline, const sf::Color& outlineColor)
    {
        Panel tmpPanel(p1, p2, color, outline, outlineColor);
        panels[name] = tmpPanel;
    }

    sf::Vector2i Gui::getNextPSPos()
    {
        if(mainMenu != NULL)
            return mainMenu->getNextPSPos();
        else
            return optionsMenu->getNextPSPos();
    }

    sf::Vector2f Gui::getPSPos()
    {
        if(mainMenu != NULL)
            return mainMenu->getPSPos();
        else
            return optionsMenu->getPSPos();
    }

    void Gui::click(const sf::Vector2i& mousePos)
    {
        for(PanelMap::iterator it = panels.begin(); it != panels.end(); it++)
            it->second.click(mousePos);

        if(mainMenu != NULL)
            mainMenu->click(mousePos);
        if(optionsMenu != NULL)
            optionsMenu->click(mousePos);
        if(diagPanel != NULL)
            diagPanel->click(mousePos);

        if(delMain)
        {
            safeDelete(mainMenu);
            delMain = false;
        }

        if(delOpt)
        {
            safeDelete(optionsMenu);
            delOpt = false;
        }

        if(delDia)
        {
            safeDelete(diagPanel);
            delDia = false;
        }
    }

    void Gui::update(const float& elapsed)
    {
        //Show fps
        if(fpsCount++ % 4 == 0)
        {
            fpsStr << "fps: " << (int) ((1.f / elapsed));
            fps->SetText(fpsStr.str());
            fpsStr.str("");
            fpsCount = 0;
        }

        if(mainMenu != NULL)
            mainMenu->update(elapsed);
        if(optionsMenu != NULL)
            optionsMenu->update(elapsed);
    }

    void Gui::Render(sf::RenderTarget& target) const
    {
        for(PanelMap::const_iterator it = panels.begin(); it != panels.end(); it++)
            target.Draw(it->second);

        if(mainMenu != NULL)
            target.Draw(*mainMenu);
        if(optionsMenu != NULL)
            target.Draw(*optionsMenu);
        if(diagPanel != NULL)
            target.Draw(*diagPanel);

        target.Draw(*fps);
    }

    void Gui::loadFonts(const std::string& fontFile)
    {
        Logger::writeMsg(1) << "\nLoading assets from: \"" << fontFile << "\"...";
        //Open specified file
        fileReader.open(fontFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The font handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string fontKey;
        std::string fontPath;

        while(getline(fileReader,output))
        {
            //Check if line is empty and perform string operation

            if(strReadLine(output, fontKey, fontPath))
            {
                //Search fonts
                if(fonts.find(fontKey) != fonts.end())
                    Logger::writeMsg(1) << "Failed to load font \"" << fontPath << "\". Reason: Font key already in system";
                else
                {
                    sf::Font fnt;
                    //Load font file
                    if(!fnt.LoadFromFile(fontPath))
                        Logger::writeMsg(1) << "Failed to load font \"" << fontPath << "\". Reason: Unable to open image file";
                    else
                    {
                        //Add to fonts
                        fonts[fontKey] = fnt;
                        //Debug output
                        Logger::writeMsg(1) << "Loaded font \"" << fontKey << "\" with filepath \"" << fontPath << "\"";;
                    }
                }
            }
        }

        //Debug output
        Logger::writeMsg(1) << "Finished loading fonts from \"" << fontFile << "\"";
        //Close file
        fileReader.close();
    }
}
