/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-02-13
/ License: GPLv3
*/
#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

typedef std::vector<std::string> StrVec;

namespace sbe
{
    class Logger
    {
        public:
            Logger(){}
            ~Logger() {}

            static void init(const bool l);
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

            static StrVec getLog()
            {
                return logHistory;
            }

            static void clearLog()
            {
                logHistory.clear();
            }

            //std::ostream& operator<< (std::ostream& out, )
        private:
            static unsigned char curLevel;
            static unsigned char workLevel;
            static std::ofstream fileWriter;
            static std::ostringstream oss;
            static bool log;
            static StrVec logHistory;
    };
}
#endif
