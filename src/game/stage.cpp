/*
/ Stage class
/ Author: Felix Westin
/ File created: 2011-03-14
/ File updated: 2011-03-15
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../game/movable.h" //Base entity class
#include "../game/stage.h"   //Header
#include "../graphics/layer.h"   //Layer class
#include "../audio/audiohandler.h"
#include <list> //For lists
#include "../graphics/background.h" // Background

namespace sbe
{

    Stage::Stage
    (
        ConfigReader* configReader,
        ImageHandler* imageHandler,
        AudioHandler* audioHandler,
        const std::string& stageScriptFile
    )

    {
        //Save config reader pointer
        cfgReader = configReader;
        //Save image handler pointer
        imgHandler = imageHandler;
        //Save audio handler pointer
        audHandler = audioHandler;
        //Save stage file
        stageFile = stageScriptFile;
        //Load stage
        load();
    }

    void Stage::load()
    {
        std::ifstream fileReader;

        Logger::writeMsg(1) << "\nLoading stage" << stageFile;

        //Set default values
        bg = NULL;

        //Open specified file
        fileReader.open(stageFile.c_str());

        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Couldn't open the specified stage file";
            fileReader.close();
            return; //Um, can I do this?
        }

        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);

            //If line == "info"...
            while( strStripSpace(output) == "info" )
            {
                //Read line
                getline(fileReader,output);

                //...look for bracket and start reading data
                if( strStripSpace(output) == "{" )
                {
                    //Read until bracket ends data input
                    while( strStripSpace(output) != "}" )
                    {
                        //Read line
                        getline(fileReader,output);
                        //Check if line is empty and perform string operation
                        if(strReadLine(output,parameterKey,parameterValue))
                        {
                            /*
                            //Assign parameter values
                            if(parameterKey == "name")
                                info_name = parameterValue;
                            else if(parameterKey == "mod")
                                info_mod = parameterValue;
                            else if(parameterKey == "chapter")
                                info_chapter = atoi(parameterValue.c_str());
                            else
                                Logger::writeMsg(1) << "Invalid map info parameter: " << parameterKey;  //Variable not found
                            */
                        }
                    }
                }
            }

            //If line == "data"...
            while( strStripSpace(output) == "data" )
            {
                //Read line
                getline(fileReader,output);

                //...look for bracket and start reading data
                if( strStripSpace(output) == "{" )
                {
                    //Read until bracket ends data input
                    while( strStripSpace(output) != "}" )
                    {
                        Logger::writeMsg(1) << "\nLoading data...";
                        //Read line
                        getline(fileReader,output);
                        //Check if line is empty and perform string operation
                        if(strReadLine(output,parameterKey,parameterValue))
                        {
                            //Assign parameter values
                            if(parameterKey == "background")
                                Logger::writeMsg(1) << "\nLoading background..."; //Load background
                            else if(parameterKey == "images")
                                imgHandler->loadAssets(parameterValue); //Load image asset file using image handler
                            else if(parameterKey == "sounds")
                                audHandler->loadSound(parameterValue); //Load sound asset file using audio handler
                            else if(parameterKey == "music")
                                audHandler->loadMusic(parameterValue); //Load music asset file using audio handler
                            else if(parameterKey == "particles")
                                1; //Load particle asset file using particle handler (Doesn't exist yet, mind you)
                            else
                                Logger::writeMsg(1) << "Invalid map asset parameter: " << parameterKey;  //Variable not found
                        }
                        Logger::writeMsg(1) << "\Data loaded";
                    }
                }
            }
        }
    }

    void Stage::Render(sf::RenderTarget& Target) const
    {

    }

    void Stage::update(const float& elapsed)
    {
        //Shitload of stuff is going to happen here
    }
}
