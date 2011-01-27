/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2010-01-18
/ File updated: 2011-01-28
/ License: GPLv3
*/
#ifndef PANEL_H_INCLUDED
#define PANEL_H_INCLUDED

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

typedef std::map<std::string, sf::String> stringMap;
typedef std::map<std::string, sf::Shape> shapeMap;

namespace sbe
{
    class Panel : public sf::Drawable
    {
        public:
            Panel(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Color& color, const float& outline = 0, const sf::Color& outlineColor = sf::Color::Black);
            ~Panel();

            void Render(sf::RenderTarget& target) const;

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
                              const sf::String& text,
                              const sf::Color& txtCol,
                              const sf::Vector2f& p1,
                              const sf::Vector2f& p2,
                              const sf::Color& color,
                              const float& outline = 1,
                              const sf::Color& outlineColor = sf::Color::Black);

            bool withinPanel(const sf::Vector2i& mousePos);
            std::string withinButton(const sf::Vector2i& mousePos);
        protected:
            sf::Shape *panelRect;
            stringMap strings;
            shapeMap buttons;
    };
}

#endif
