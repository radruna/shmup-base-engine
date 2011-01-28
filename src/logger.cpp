/*
/ Panel class, used for GUI elements
/ Author: Victor Rådmark
/ File created: 2011-01-28
/ File updated: 2011-01-28
/ License: GPLv3
*/
#include <iostream>
#include <string>
#include <cstdlib>

#include "logger.h"

namespace sbe
{
    std::ofstream Logger::fileWriter;
    unsigned char Logger::curLevel;

    void Logger::init()
    {
        system("mkdir logs");
        fileWriter.open("logs/log.txt");
        if(!fileWriter)
        {
            //Debug output
            std::cout << "Log file could not be opened for writing!" << std::endl;
            return;
        }
    }

    void Logger::writeMsg(const std::string& message, const unsigned char& level)
    {
        //TODO(Liag#5#): Fix stringstream support.
        if(curLevel >= level)
        {
            //Add date and stuff
            std::cout << message << std::endl;

            if(fileWriter.is_open())
                fileWriter << message << std::endl;
        }
    }
}
