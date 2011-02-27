/*
/ Time functions
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-01-28
/ License: GPLv3
*/
#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <ctime>
#include <string>

namespace sbe
{
    std::string getCurTime()
    {
        //Return current time in the format of YYYYmmDDHHMMSS
        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];

        time(&rawtime);

        timeinfo = localtime(&rawtime);

        strftime(buffer, 80, "%Y%m%d%H%M%S", timeinfo);

        std::string s = buffer;

        return s;
    }
}

#endif
