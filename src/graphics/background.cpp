/*
/ Background class
/ Author: Niklas Andréasson
/ File created: 2011-02-25
/ File updated: 2011-03-03
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../game/movable.h" //Base entity class
#include "../graphics/background.h"   //Header
#include "../graphics/layer.h"   //Layer class
#include <list> //For lists

namespace sbe
{

    Background::Background(
                       const std::string& scrollayerFile,
                       ImageHandler* imgHandler,
                        const unsigned int& w,
                        const unsigned int& h
                       )
    {
        scriptFile = scrollayerFile;
        imageHandler = imgHandler;
        width = w;
        height = h;
        load();
    }

    void Background::load()
    {
        std::ifstream fileReader;

        Logger::writeMsg(1) << "\nLoading background" << scriptFile;

        //Open specified file
        fileReader.open(scriptFile.c_str());
        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Couldn't open the specified background layer file";
            fileReader.close();
            return;
        }

        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation
            if(strReadLine(output,parameterKey,parameterValue))
            {
                //Assign parameter value based on the type of parameter.
                //Generic parameters
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
                else if(parameterKey == "scale_y")
                    yScale = atof(parameterValue.c_str());
                else if(parameterKey == "scale_x")
                    xScale = atof(parameterValue.c_str());
                else if(parameterKey == "repeat_space_x")
                    repeat_offsetx = atof(parameterValue.c_str());
                else if(parameterKey == "repeat_space_y")
                    repeat_offsety = atof(parameterValue.c_str());
                else
                    Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;
            }

        }

        tmpImg = imageHandler->getImage(spriteName);

        layers.push_back(Layer(tmpImg, moveAngle, moveSpeed, xOffset, yOffset, yScale, xScale, repeat_offsetx, repeat_offsety, width, height));

    }

    void Background::Render(sf::RenderTarget& Target) const
    {
       for(std::list<Layer>::const_iterator it = layers.begin(); it != layers.end(); it++) //Iterate through layer list
        {
            Target.Draw(*it);
        }
    }

    void Background::update(const float& elapsed)
    {
        for(std::list<Layer>::iterator it = layers.begin(); it != layers.end(); it++) //Iterate through layer list
        {
            it->update(elapsed);
        }
    }
}
