/*
/ Background class
/ Author: Niklas Andréasson
/ File created: 2011-02-25
/ File updated: 2011-03-15
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../graphics/background.h"   //Header
#include "../graphics/layer.h"   //Layer class
#include <list> //For lists

namespace sbe
{

    Background::Background
    (
        ConfigReader* configReader,
        const std::string& scrollayerFile,
        ImageHandler* imgHandler
    )

    {
        //Save config reader pointer
        cfgReader = configReader;
        //Save image handler pointer
        imageHandler = imgHandler;
        //Save script file string
        scriptFile = scrollayerFile;
        //Load background
        load();
    }

    void Background::load()
    {
        std::ifstream fileReader;

        Logger::writeMsg(1) << "\nLoading background" << scriptFile;

        //Set default values
        spriteName = "dev1";
        moveAngle = 0;
        moveSpeed = 0;
        xOffset = 0;
        yOffset = 0;
        xScale = 1;
        yScale = 1;
        tile_x = 1;
        tile_y = 1;
        fit_x = 0;
        fit_y = 0;

        //Open specified file
        fileReader.open(scriptFile.c_str());

        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Couldn't open the specified background layer file";
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
            while( strStripSpace(output) == "layer" )
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
                        }
                    }
                    //Push new layer
                    layers.push_back(Layer(cfgReader, imageHandler, spriteName, moveAngle, moveSpeed, xOffset, yOffset, yScale, xScale, tile_x, tile_y, fit_x, fit_y));
                }
            }
        }
    }

    void Background::Render(sf::RenderTarget& Target) const
    {
        //Iterate through layer list and render all layers
        for(std::list<Layer>::const_iterator it = layers.begin(); it != layers.end(); it++) //Iterate through layer list
        {
            Target.Draw(*it);
        }
    }

    void Background::update(const float& elapsed)
    {
        //Iterate through layer list and update all layers
        for(std::list<Layer>::iterator it = layers.begin(); it != layers.end(); it++) //Iterate through layer list
        {
            it->update(elapsed);
        }
    }
}
