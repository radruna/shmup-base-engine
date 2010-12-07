/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2010-11-30
/ License: GPLv3
*/

#include <iostream> //Debug output
#include <fstream> //File reading
#include <cstdlib> //For converting strings

#include "configreader.h" //Class def

namespace sbe
{
    ConfigReader::ConfigReader()
        : fs(false)
    {
        title = "SBE Window";
        readConfig();
    }

    void ConfigReader::readConfig(const std::string& cfgFile)
    {
        /*
            Purpose: Read a config file.
        */
        std::cout << std::endl << "Loading settings from: \"" << cfgFile << "\"..." << std::endl;
        //Open specified file
        fileReader.open(cfgFile.c_str());
        if(!fileReader)
        {
            //Debug output
            std::cout << "The config reader was unable to open the specified configuration file" << std::endl;
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
                    fs = true;
                else if(setting == "title")
                    title = value;
            }
        }
        //Debug output
        std::cout << "Finished loading settings from \"" << cfgFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }
}
