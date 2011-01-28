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
#include <fstream>
#include <ctime>

#include "logger.h"
#include "time.h"

namespace sbe
{
    std::ofstream Logger::fileWriter;
    unsigned char Logger::curLevel;
    unsigned char Logger::workLevel;
    std::ostringstream Logger::oss;

    void Logger::init()
    {
        system("mkdir logs");
        std::string file = "logs/log_" + sbe::getCurTime() + ".txt";
        fileWriter.open(file.c_str());
        if(!fileWriter)
        {
            //Debug output
            std::cout << "Log file could not be opened for writing!" << std::endl;
            return;
        }
    }

    std::ostringstream& Logger::writeMsg(const unsigned char level)
    {
        if(oss.str() != "") write();

        workLevel = level;
        return oss;
    }

    void Logger::write()
    {
        if(oss.str() != "")
        {
            if(curLevel >= workLevel)
            {
                //Add date and stuff
                std::cout << oss.str() << std::endl;

                if(fileWriter.is_open())
                    fileWriter << oss.str() << std::endl;

                oss.str("");
            }
        }
    }
}
