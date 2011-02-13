/*
/ Config reader class
/ Author: Victor Rådmark
/ File created: 2010-11-30
/ File updated: 2011-02-13
/ License: GPLv3
*/

#include <iostream> //Debug output
#include <fstream> //File reading

#include "configreader.h" //Class def
#include "logger.h" //Outputs debug in console and log

namespace sbe
{
    ConfigReader::ConfigReader()
    {
        settings["title"] = "SBE";
        settings["width"] = "1280";
        settings["height"] = "720";
        settings["fullscreen"] = "0";
        settings["limit_fps"] = "60";
        settings["vsync"] = "0";
        settings["show_menu"] = "1";
        settings["music_volume"] = "100";
        settings["sfx_volume"] = "100";
        settings["ps_reload"] = "10";
        settings["log"] = "1";
        writeSettings(0);
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
        else
        {
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
                    /*if(setting == "width")
                        res.x = atoi(value.c_str());
                    else if(setting == "height")
                        res.y = atoi(value.c_str());
                    else if(setting == "fullscreen")
                        fs = (bool) atoi(value.c_str());
                    else if(setting == "title")
                        title = value;
                    else if(setting == "log")
                        log = (bool) atoi(value.c_str());
                    else if(setting == "fps_limit")*/
                    if(setting != "")
                        settings[setting] = value;
                }
            }
            //Debug output
            Logger::writeMsg(1) << "Finished loading settings from \"" << cfgFile << "\"";
        }

        //Close file
        fileReader.close();
    }

    void ConfigReader::writeSettings(const bool& type)
    {
        std::string file = "default_settings.cfg";

        if(type)
            file = "settings.cfg";

        try
        {
            std::ofstream fileWriter(file.c_str());

            if(!fileWriter.is_open())
                throw;

            fileWriter << "//_______________________________________________________" << std::endl;
            if(!type) fileWriter << "// Rename this file to settings.cfg if you want to change any settings." << std::endl;
            else fileWriter << "// File generated from user settings." << std::endl;
            fileWriter << "//¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯" << std::endl;
            fileWriter << "\"title\"			    	\"" << settings["title"] << "\"" << std::endl;
            fileWriter << "\"width\"			    	\"" << settings ["width"] << "\"" << std::endl;
            fileWriter << "\"height\"			    \"" << settings ["height"] << "\"" << std::endl;
            fileWriter << "\"fullscreen\"		    \"" << settings ["fullscreen"] << "\"" << std::endl;
            fileWriter << "\"limit_fps\"			    \"" << settings ["limit_fps"] << "\" //If 0, no limit is set" << std::endl;
            fileWriter << "\"vsync\"			    	\"" << settings ["vsync"] << "\" //Should only be used with fullscreen" << std::endl;
            fileWriter << "\"show_menu\"                \"" << settings ["show_menu"] << "\" //Show the main menu first." << std::endl;
            fileWriter << std::endl;
            fileWriter << "\"music_volume\"		    \"" << settings ["music_volume"] << "\"" << std::endl;
            fileWriter << "\"sfx_volume\"		    \"" << settings ["sfx_volume"] << "\"" << std::endl;
            fileWriter << std::endl;
            fileWriter << "\"ps_reload\"            \"" << settings ["ps_reload"] << "\" //Interval between each frame that all particle systems should be reloaded, 0 to turn off" << std::endl;
            fileWriter << std::endl;
            fileWriter << "\"log\"                \"" << settings ["log"] << "\" //If logs should be written to the logs directory" << std::endl;
            fileWriter.close();
        }
        catch(...)
        {
            Logger::writeMsg(1) << "Could not open \"" << file << "\".";
        }

    }
}
