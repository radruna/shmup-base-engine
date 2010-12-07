/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2010-12-07
/ License: GPLv3
*/
#ifndef CONFIGREADER_H_INCLUDED
#define CONFIGREADER_H_INCLUDED

#include <string>

#include <SFML/System.hpp>

#include "filehandler.h"

namespace sbe
{
    class ConfigReader : public FileHandler
    {
        public:
            ConfigReader();
            ~ConfigReader()
            {

            }

            void readConfig(const std::string& cfgFile = "settings.cfg");

            sf::Vector2i getRes()
            {
                return res;
            }
            bool getFS()
            {
                return fs;
            }
            std::string getTitle()
            {
                return title;
            }

        private:
            sf::Vector2i res;
            bool fs;
            std::string title;
    };
}

#endif
