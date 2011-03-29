/*
/ Console panel
/ Author: Victor Rådmark
/ Created: 2011-03-29
/ Updated: 2011-03-29
/ License: GPL v3
*/
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

//#include "command.h"

//typedef std::map<std::string, sbe::Command> CmdMap;
typedef std::vector<std::string> StrVec;
typedef std::vector<sf::String> txtVec;

namespace sbe
{
    class Console : public sbe::Panel
    {
        public:
            Console(const sf::Vector2i& res, const sf::Font& f);
            ~Console();

            void click(const sf::Vector2i& mousePos);
            void hover(const sf::Vector2i& mousePos);
            void update();

            void showConsole()
            {
                active = !active;
            }
            bool isShown()
            {
                return active;
            }

        protected:
            void Render(sf::RenderTarget& target) const;

        private:
            void addString(const std::string& str);
            void removeString();

            sf::Font font;
            txtVec strings;
            bool active;
            //CmdMap commands;
            StrVec history;
    };
}

#endif
