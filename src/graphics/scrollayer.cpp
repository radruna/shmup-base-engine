/*
/ Scroll layer class
/ Author: Niklas Andréasson
/ File created: 2010-12-07
/ File updated: 2011-01-27
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../game/movable.h" //Base entity class
#include "scrollayer.h"   //Header
#include <list> //For lists

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
                if(parameterKey == "image"){
                   tmp.bgSprite.SetImage(imageHandler->getImage(parameterValue));

                }
                else if(parameterKey == "xPos") {
                   // Layer.bgSprite.SetX(atof(parameterValue.c_str()));
                    //x = atof(parameterValue.c_str());
                }
                else if(parameterKey == "yPos") {
                   // Layer.bgSprite.SetY(atof(parameterValue.c_str()));
                   tmp.bgSprite.SetY(atof(parameterValue.c_str()));
                    //layers.push_back(bgSprite);
                    layers.push_back(tmp);

                }
                else if(parameterKey == "speed") {

                }
                else
                    Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;
            }


        }

    }

    void Scrollayer::Render(sf::RenderTarget& Target) const
    {
       for(std::list<Layer>::const_iterator it = layers.begin(); it != layers.end(); it++) //Iterate through particle list
        {
            Target.Draw(it->bgSprite);
        }
    }

    void Scrollayer::update(const float& elapsed)
    {
        //x = x + 10;

        //layers.front().SetX(x);
    }
}
