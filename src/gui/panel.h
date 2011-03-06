/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-18
/ File updated: 2011-02-27
/ License: GPLv3
*/
#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include "../graphics/drawable.h"
#include "button.h"
#include "checkbutton.h"

typedef std::map<std::string, sf::String> stringMap;
typedef std::map<std::string, sbe::Button> buttonMap;
typedef std::map<std::string, sbe::CheckButton> checkButtonMap;

namespace sbe
{
    class Panel : public sbe::Drawable
    {
        public:
            Panel()
            {}

            Panel(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline = 0, const sf::Color& outlineColor = sf::Color::Black);
            ~Panel();

            void createString(const std::string& name, const sf::String string);
            void createString(const std::string& name,
                              const sf::Unicode::Text& text,
                              const sf::Font& font = sf::Font::GetDefaultFont(),
                              const float& size = 30.f,
                              const sf::Vector2f& pos = sf::Vector2f(0, 0),
                              const sf::Color& color = sf::Color::White);

            sf::String& getString(const std::string& name)
            {
                return strings[name];
            }

            void createButton(const std::string& name,
                              void* callObject,
                              void (*callFunction) (void* object),
                              const sf::String& text,
                              const sf::Color& txtCol,
                              const sf::Vector2f& p1,
                              const sf::Vector2f& p2,
                              const sf::Color& color,
                              const float& outline = 1,
                              const sf::Color& outlineColor = sf::Color::Black);

            void createButton(const std::string& name,
                              void* callObject,
                              void (*callFunction) (void* object),
                              const sf::String& text,
                              const sf::Color& txtCol,
                              const sf::Vector2f& p1,
                              const sf::Vector2f& p2,
                              const sf::Vector2f& p3,
                              const sf::Color& color,
                              const float& outline = 1,
                              const sf::Color& outlineColor = sf::Color::Black);

            void createCheckButton(const std::string& name,
                                   void* callObject,
                                   void (*callFunction) (void* object),
                                   const bool& c,
                                   const sf::String& text,
                                   const sf::Color& txtCol,
                                   const sf::Vector2f& p1,
                                   const sf::Vector2f& p2,
                                   const sf::Color& color,
                                   const sf::Color& outlineColor = sf::Color::Black);

            void click(const sf::Vector2i& mousePos);

            virtual sf::Vector2i getNextPSPos() { return sf::Vector2i(0, 0); }
            virtual sf::Vector2f getPSPos() { return sf::Vector2f(0.f, 0.f); }
        protected:
            void Render(sf::RenderTarget& target) const;
            bool withinPanel(const sf::Vector2i& mousePos) const;
            sf::Shape panelRect;
            stringMap strings;
            buttonMap buttons;
            checkButtonMap checkButtons;
    };
}

#endif
