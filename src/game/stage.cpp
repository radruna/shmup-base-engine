/*
/ Stage class
/ Author: Felix Westin
/ File created: 2011-03-14
/ File updated: 2011-03-14
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

namespace sbe
{

    Stage::Stage
    (
        ConfigReader* configReader,
        ImageHandler* imgHandler,
        AudioHandler* audioHandler,
        const std::string& stageScriptFile
    )

    {
        //Save config reader pointer
        cfgReader = configReader;
        //Save image handler pointer
        imageHandler = imgHandler;
        //Save script file string
        audHandler = audioHandler;
        //Save stage file
        stageFile = stageScriptFile;
        //Load background
        load();
    }

    void Stage::load()
    {
        std::ifstream fileReader;

        Logger::writeMsg(1) << "\nLoading stage" << stageFile;

        //Set default values


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

            //If line == "layer"...
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
                            if(parameterKey == "sprite_name")
                                spriteName = parameterValue;
                            else if(parameterKey == "movement_angle")
                                moveAngle = atoi(parameterValue.c_str());
                            else if(parameterKey == "movement_speed")
                                moveSpeed = atoi(parameterValue.c_str());
                            else if(parameterKey == "offset_x")
                                xOffset = atof(parameterValue.c_str());
                            else if(parameterKey == "offset_y")
                                yOffset = atof(parameterValue.c_str());
                            else if(parameterKey == "scale_x")
                                xScale = atof(parameterValue.c_str());
                            else if(parameterKey == "scale_y")
                                yScale = atof(parameterValue.c_str());
                            else if(parameterKey == "tile_x")
                                tile_x = (bool) atoi(parameterValue.c_str());
                            else if(parameterKey == "tile_y")
                                tile_y = (bool) atoi(parameterValue.c_str());
                            else if(parameterKey == "fit_x")
                                fit_x = (bool) atoi(parameterValue.c_str());
                            else if(parameterKey == "fit_y")
                                fit_y = (bool) atoi(parameterValue.c_str());
                            else
                                Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;  //Variable not found
                                */
                        }
                    }
                }
            }

            //If line == "assets"...
            while( strStripSpace(output) == "assets" )
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
                            //Assign parameter values
                            if(parameterKey == "images")
                                1; //Load image asset file using imagehandler
                            if(parameterKey == "sounds")
                                1; //Load sound asset file using imagehandler
                            if(parameterKey == "music")
                                1; //Load image asset file using imagehandler
                            if(parameterKey == "particles")
                                1; //Load particle asset file using imagehandler
                            else
                                Logger::writeMsg(1) << "Invalid map asset parameter: " << parameterKey;  //Variable not found
                        }
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

    }
}
