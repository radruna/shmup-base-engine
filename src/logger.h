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
#include <sstream>

namespace sbe
{
    class Logger
    {
        public:
            Logger(){}
            ~Logger() {}

            static void init();
            static void setLevel(const unsigned char& level)
            {
                curLevel = level;
            }

            static std::ostringstream& writeMsg(const unsigned char level);

            static void write();
            static void close()
            {
                fileWriter.close();
            }

            //std::ostream& operator<< (std::ostream& out, )
        private:
            static unsigned char curLevel;
            static unsigned char workLevel;
            static std::ofstream fileWriter;
            static std::ostringstream oss;
            static bool log;
    };
}
#endif
