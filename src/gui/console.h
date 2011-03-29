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

#include "panel.h"
//#include "command.h"

//typedef std::map<std::string, sbe::Command> CmdMap;
typedef std::vector<std::string> StrVec;

namespace sbe
{
    class Console : public sbe::Panel
    {
        public:
            Console();
            ~Console();

            click(sf::Vector2i& mousePos);
            addLog(const std::string& newLog);
        private:
            execCmd();
            //CmdMap commands;
            StrVec history;
    }
}
