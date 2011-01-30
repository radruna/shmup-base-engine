/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-01-28
/ License: GPLv3
*/

#include <iostream> //Debug output
#include <fstream> //File reading
#include <cstdlib> //For converting strings

#include "configreader.h" //Class def
#include "logger.h" //Outputs debug in console and log

namespace sbe
{
    ConfigReader::ConfigReader()
        : fs(false)
    {
        res.x = 1280;
        res.y = 1024;
        title = "SBE Window";
        readConfig();
    }

    void ConfigReader::readConfig(const std::string& cfgFile)
    {
        /*
            Purpose: Read a config file.
        */
        Logger::writeMsg(1) << "\nLoading settings from: \"" << cfgFile << "\"...";
        //Open specified file
        fileReader.open(cfgFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The config reader was unable to open the specified configuration file";
            return;
        }
        //Saving vars
        std::string output;
        std::string setting;
        std::string value;

        //Loop until end of file
        while(getline(fileReader,output))
        {
            //Check if line is empty and perform string operation
            if(strReadLine(output, setting, value))
            {
                if(setting == "width")
                    res.x = atoi(value.c_str());
                else if(setting == "height")
                    res.y = atoi(value.c_str());
                else if(setting == "fullscreen")
                    fs = (bool) atoi(value.c_str());
                else if(setting == "title")
                    title = value;
                else if(setting == "log")
                    log = (bool) atoi(value.c_str());
                else
                {
                    Logger::writeMsg(1) << "Setting " << setting << " couldn't be found.";
                }
            }
        }
        //Debug output
        Logger::writeMsg(1) << "Finished loading settings from \"" << cfgFile << "\"";
        //Close file
        fileReader.close();
    }
}
