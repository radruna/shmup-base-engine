/*
/ Particle class
/ Author: Niklas Andréasson
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#include <SFML/Graphics.hpp> //Sfml stuff

#include <iostream> //Debug output
#include "const.h" //Constants
#include "movable.h" //Base entity class
#include "scrollayer.h"   //Header
#include "logger.h" //Outputs debug in console and log

namespace sbe
{

    Scrollayer::Scrollayer(
                       const std::string& scrollayerFile,
                       ImageHandler* imgHandler
                       )
        : Drawable()
    {
        scriptFile = scrollayerFile;
        imageHandler = imgHandler;
        load();
    }

    void Scrollayer::load()
    {
        Logger::writeMsg(1) << "\nLoading scroll layer " << scriptFile;

        //Open specified file
        fileReader.open(scriptFile.c_str());
        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Couldn't open the specified scroll layer file";
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
                if(parameterKey == "image")
                    bgImg = imageHandler->getImage(parameterValue);

                else
                    Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;
            }
        }

    }

    void Scrollayer::Render(sf::RenderTarget& Target) const
    {
        //Target.Draw(bgImg);
    }

    void Scrollayer::update(const float& elapsed)
    {

    }
}
