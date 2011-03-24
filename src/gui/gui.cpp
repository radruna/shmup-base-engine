/*
/ GUI class
/ Author: Victor Rådmark
/ File created: 2011-03-06
/ File updated: 2010-03-18
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
#include "selectmenu.h"
#include "optionsmenu.h"
#include "dialogpanel.h"
#include "gui.h"

namespace sbe
{
    Gui::Gui(const std::string& fontFile, const sf::Vector2i& res)
        : delMain(false), delOpt(false), delSec(false), delDia(false), showPause(false), fpsCount(0)
    {
        loadFonts(fontFile);

        fps = new sf::String("0", fonts["chiller"], 20);
        fps->SetPosition(10, 10);
        fps->SetColor(sf::Color::White);
        fps2 = new sf::String("0", fonts["chiller"], 20);
        fps2->SetPosition(12, 12);
        fps2->SetColor(sf::Color(0, 0, 0, 150));

        pauseStr = new sf::String("Paused", fonts["chiller"], 30);
        pauseStr->SetCenter(pauseStr->GetRect().GetWidth() / 2, pauseStr->GetRect().GetHeight() / 2);
        pauseStr->SetPosition(res.x / 2, (res.y - 50) / 2);
        pauseStr->SetColor(sf::Color::White);
        pauseStrShadow = new sf::String("Paused", fonts["chiller"], 30);
        pauseStrShadow->SetCenter(pauseStrShadow->GetRect().GetWidth() / 2, pauseStrShadow->GetRect().GetHeight() / 2);
        pauseStrShadow->SetPosition((res.x / 2) + 2, ((res.y - 50) / 2) + 2);
        pauseStrShadow->SetColor(sf::Color(0, 0, 0, 150));

        mainMenu = NULL;
        optionsMenu = NULL;
        selectMenu = NULL;
        diagPanel = NULL;
    }

    Gui::~Gui()
    {
        panels.clear();
        unloadFonts();
        safeDelete(mainMenu);
        safeDelete(optionsMenu);
        safeDelete(selectMenu);
        safeDelete(diagPanel);
        safeDelete(fps);
        safeDelete(fps2);
        safeDelete(pauseStr);
        safeDelete(pauseStrShadow);
    }

    void Gui::createMainMenu(void* callObject, void (*selectFunction) (void* object), void (*optionsFunction) (void* object), void (*hiscoreFunction) (void* object), void (*creditsFunction) (void* object), void (*exitFunction) (void* object),
                             const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cfgReader, const sf::Vector2i& r, const sf::Vector2f& psPos, const sf::Vector2i& next)
    {
        mainMenu = new MainMenu(callObject, selectFunction, optionsFunction, hiscoreFunction, creditsFunction, exitFunction,  psFile, imgHandler, cfgReader, r, fonts["chiller"], psPos, next);
    }

    void Gui::createOptionsMenu(void* callObject, void (*applyFunction) (void* object), void (*backFunction) (void* object), const std::string& psFile, ImageHandler* imgHandler, ConfigReader* cReader, const sf::Vector2i& r, const sf::Vector2f& psPos, const sf::Vector2i& next)
    {
        optionsMenu = new OptionsMenu(callObject, applyFunction, backFunction, psFile, imgHandler, cReader, r, fonts["chiller"], psPos, next);
    }

    void Gui::createSelectMenu(void* callObject, void (*selectFunction) (void* object, const int& map, bool selected), void (*backFunction) (void* object), ConfigReader* cReader, const sf::Vector2i& r)
    {
        selectMenu = new SelectMenu(callObject, selectFunction, backFunction, cReader, r, fonts["chiller"]);
    }

    void Gui::createDialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog)
    {
        diagPanel = new DialogPanel(res, dialog, fonts["chiller"]);
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
        else if(optionsMenu != NULL)
            return optionsMenu->getNextPSPos();
        else
            return sf::Vector2i(-1, -1);
    }

    sf::Vector2f Gui::getPSPos()
    {
        if(mainMenu != NULL)
            return mainMenu->getPSPos();
        else if(optionsMenu != NULL)
            return optionsMenu->getPSPos();
        else
            return sf::Vector2f(-1, -1);
    }

    void Gui::click(const sf::Vector2i& mousePos)
    {
        for(PanelMap::iterator it = panels.begin(); it != panels.end(); it++)
            it->second.click(mousePos);

        if(mainMenu != NULL)
            mainMenu->click(mousePos);
        if(optionsMenu != NULL)
            optionsMenu->click(mousePos);
        if(selectMenu != NULL && !delMain)
            selectMenu->click(mousePos);
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

        if(delSec)
        {
            safeDelete(selectMenu);
            delSec = false;
        }

        if(delDia)
        {
            safeDelete(diagPanel);
            delDia = false;
        }


    }

    void Gui::hover(const sf::Vector2i& mousePos)
    {
        for(PanelMap::iterator it = panels.begin(); it != panels.end(); it++)
            it->second.hover(mousePos);

        if(mainMenu != NULL)
            mainMenu->hover(mousePos);
        if(optionsMenu != NULL)
            optionsMenu->hover(mousePos);
        if(selectMenu != NULL)
            selectMenu->hover(mousePos);
        if(diagPanel != NULL)
            diagPanel->hover(mousePos);
    }

    void Gui::update(const float& elapsed)
    {
        //Show fps
        if(fpsCount++ == 4)
        {
            fpsStr << "fps: " << (int) ((1.f / elapsed));
            fps->SetText(fpsStr.str());
            fps2->SetText(fpsStr.str());
            if((int) ((1.f / elapsed)) < 20) fps->SetColor(sf::Color(255, 50, 50));
            else if((int) ((1.f / elapsed)) < 40) fps->SetColor(sf::Color(255, 255, 50));
            else fps->SetColor(sf::Color(155, 255, 155));
            fpsStr.str("");
            fpsCount = 0;
        }

        if(mainMenu != NULL)
            mainMenu->update(elapsed);
        if(optionsMenu != NULL)
            optionsMenu->update(elapsed);
    }

    void Gui::pause()
    {
        showPause = !showPause;
    }

    void Gui::Render(sf::RenderTarget& target) const
    {
        for(PanelMap::const_iterator it = panels.begin(); it != panels.end(); it++)
            target.Draw(it->second);

        if(mainMenu != NULL)
            target.Draw(*mainMenu);
        if(optionsMenu != NULL)
            target.Draw(*optionsMenu);
        if(selectMenu != NULL)
            target.Draw(*selectMenu);
        if(diagPanel != NULL)
            target.Draw(*diagPanel);

        target.Draw(*fps2);
        target.Draw(*fps);

        if(showPause)
        {
            target.Draw(*pauseStrShadow);
            target.Draw(*pauseStr);
        }
    }

    void Gui::loadFonts(const std::string& fontFile)
    {
        std::ifstream fileReader;

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
