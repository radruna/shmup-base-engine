/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-02-15
/ License: GPLv3
*/
#ifndef CONFIGREADER_H_INCLUDED
#define CONFIGREADER_H_INCLUDED

#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <cassert>

#include <SFML/System.hpp>

#include "logger.h"
#include "filehandler.h"

typedef std::map<std::string, std::string> stdStringMap;
typedef std::vector<sf::Vector2i> resVector;

namespace sbe
{
    class ConfigReader : public FileHandler
    {
        public:
            ConfigReader();
            ~ConfigReader()
            {
                writeSettings(1);
            }

            void readConfig(const std::string& cfgFile = "settings.cfg");
            void writeSettings(const bool& type); //0 for default_settings.cfg, 1 for settings.cfg
            //Hurr, have to do this in the header because templates
            template<class T>
            T getSetting(const std::string& setting)
            {
                assert(settings.find(setting) != settings.end());

                T t;

                std::istringstream iss(settings[setting]);
                iss >> t;

                return t;
            }

            template<class T>
            void set(const std::string& setting, const T& value)
            {
                assert(settings.find(setting) != settings.end());

                std::ostringstream oss;

                oss << value;

                settings[setting] = oss.str();
            }

            sf::Vector2i getRes()
            {
                return sf::Vector2i(getSetting<int>("width"), getSetting<int>("height"));
            }
            /*bool getFS()
            {
                return fs;
            }
            bool getLog()
            {
                return log;
            }*/

            resVector getResList()
            {
                return resList;
            }

            void setRes(const sf::Vector2i& res);

        private:
            stdStringMap settings;
            resVector resList;
    };
}

#endif
