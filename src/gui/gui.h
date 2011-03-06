/*
/ GUI class
/ Author: Victor Rådmark
/ File created: 2011-03-06
/ File updated: 2010-03-06
/ License: GPLv3
*/
#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include <map>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "../graphics/drawable.h"
#include "mainmenu.h"
#include "optionsmenu.h"
#include "dialogpanel.h"
#include "panel.h"

typedef std::map<std::string, sbe::Menu> MenuMap;
typedef std::map<std::string, sbe::Panel> PanelMap;
typedef std::map<std::string, sf::Font> FontMap;

namespace sbe
{
    class Gui : public sbe::Drawable, public sbe::FileHandler
    {
        public:
            Gui(const std::string& fontFile);
            ~Gui();

            void createMainMenu(void* callObject,
                                void (*selectFunction) (void* object),
                                void (*optionsFunction) (void* object),
                                void (*hiscoreFunction) (void* object),
                                void (*creditsFunction) (void* object),
                                void (*exitFunction) (void* object),
                                const std::string& psFile,
                                ImageHandler* imgHandler,
                                ConfigReader* cfgReader,
                                const sf::Vector2i& r,
                                const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                                const sf::Vector2i& next = sf::Vector2i(-1, -1));
            void createOptionsMenu(void* callObject,
                                   void (*applyFunction) (void* object),
                                   void (*backFunction) (void* object),
                                   const std::string& psFile,
                                   ImageHandler* imgHandler,
                                   ConfigReader* cReader,
                                   const sf::Vector2i& r,
                                   const sf::Vector2f& psPos = sf::Vector2f(-1, -1),
                                   const sf::Vector2i& next = sf::Vector2i(-1, -1));
            void createDialogPanel(const sf::Vector2i& res, const std::vector<std::string>& dialog);
            void createPanel(const std::string& name,
                             const sf::Vector2f& p1,
                             const sf::Vector2f& p2,
                             const sf::Color& color,
                             const float& outline = 0,
                             const sf::Color& outlineColor = sf::Color::Black);

            void deleteMainMenu()
            {
                delMain = true;
            }

            void deleteOptionsMenu()
            {
                delOpt = true;
            }

            void deleteMain()
            {
                delDia = true;
            }

            sf::Vector2i getNextPSPos();

            sf::Vector2f getPSPos();

            void click(const sf::Vector2i& mousePos);

            void update(const float& elapsed);

        protected:
            void Render(sf::RenderTarget& target) const;

        private:
            void loadFonts(const std::string& fontFile);
            void unloadFonts()
            {
                fonts.clear();
            }

            bool delMain,
                 delOpt,
                 delDia;
            sbe::MainMenu *mainMenu;
            sbe::OptionsMenu *optionsMenu;
            sbe::DialogPanel *diagPanel;
            PanelMap panels;
            FontMap fonts;
            sf::String *fps;
            std::stringstream fpsStr;
            short fpsCount;
    };
}

#endif
