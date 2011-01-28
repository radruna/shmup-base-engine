/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-01-28
/ License: GPLv3
*/
#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

namespace sbe
{
    class Logger
    {
        public:
            Logger(){}
            ~Logger() {}

            static void init();
            static void writeMsg(const std::string& message, const unsigned char& level);
            static void setLevel(const unsigned char& level)
            {
                curLevel = level;
            }

            static void close()
            {
                fileWriter.close();
            }
        private:
            static unsigned char curLevel;
            static std::ofstream fileWriter;
    };
}
#endif
