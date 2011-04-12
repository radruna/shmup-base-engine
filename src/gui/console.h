/*
/ Console panel
/ Author: Victor Rådmark
/ Created: 2011-03-29
/ Updated: 2011-04-12
/ License: GPL v3
*/
#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <string>
#include <map>
#include <vector>

#include <SFML/Graphics.hpp>

#include "command.h"

typedef std::map<std::string, sbe::Command> CmdMap;
typedef std::vector<std::string> StrVec;
typedef std::vector<sf::String> txtVec;

namespace sbe
{
    class Console : public sbe::Panel
    {
        public:
            Console(const sf::Vector2i& res, const sf::Font& f);
            ~Console();

            void addCommand(const std::string& name, const std::string& description, void* callObject, void (*cmdFunction) (void* object));
            void addCommand(const std::string& name, const std::string& description, void* callObject, void (*cmdFunction) (void* object, StrVec args));

            void click(const sf::Vector2i& mousePos);
            void hover(const sf::Vector2i& mousePos);
            void type(const sf::Uint32& text);
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
            static void help(void* object);
            static void cmd(void* object);
            void printHelp();
            void printCmds();
            void exec(std::string cmd);
            void addString(const std::string& str);
            void removeString();

            sf::Font font;
            sf::String *inStr;
            txtVec strings;
            bool active,
                  focus;
            CmdMap commands;
            StrVec history;
    };
}

#endif
