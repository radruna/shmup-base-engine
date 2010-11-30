/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2010-11-30
/ License: GPLv3
*/
#ifndef CONFIGREADER_H_INCLUDED
#define CONFIGREADER_H_INCLUDED

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

        private:
            sf::Vector2i res;
            bool fs;
    };
}

#endif
