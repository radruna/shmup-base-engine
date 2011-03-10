/*
/ Image handler class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-30
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "imagehandler.h"   //Class def

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    //Load images listed in the asset file
    void ImageHandler::loadAssets(const std::string& assetFile)
    {
        std::ifstream fileReader;
        Logger::writeMsg(1) << "\nLoading assets from: \"" << assetFile << "\"...";
        //Open specified file
        fileReader.open(assetFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The image handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string imageKey;
        std::string imagePath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation

            if(strReadLine(output,imageKey,imagePath))
            {
                //Search imageList
                if(imageList.find(imageKey) != imageList.end())
                    Logger::writeMsg(1) << "Failed to load image \"" << imagePath << "\". Reason: Image key already in system";
                else
                {
                    sf::Image img;
                    img.SetSmooth(false);   //Turn off image smoothing because it fucks tiling up and generally looks like shit.
                    //Load image file
                    if(!img.LoadFromFile(imagePath))
                    {
                        Logger::writeMsg(1) << "Failed to load image \"" << imagePath << "\". Reason: Unable to open image file";
                    }
                    else
                    {
                        //Add to imageList
                        imageList[imageKey] = img;
                        //Debug output
                        Logger::writeMsg(1) << "Loaded image \"" << imageKey << "\" with filepath \"" << imagePath << "\"";
                    }
                }
            }
        }
        //Debug output
        Logger::writeMsg(1) << "Finished loading images from \"" << assetFile << "\"";
        //Close file
        fileReader.close();
    }

    //Load a single image without the use of an asset file
    void ImageHandler::loadAsset(const std::string& imageKey,const std::string& imagePath)
    {
        //Search imageList
        if(imageList.find(imageKey) != imageList.end())
            Logger::writeMsg(1) << "Failed to load image \"" << imagePath << "\". Reason: Image key already in system";
        else
        {
            sf::Image img;
            //Load image file
            if(!img.LoadFromFile(imagePath))
            {
                Logger::writeMsg(1) << "Failed to load image \"" << imagePath << "\". Reason: Unable to open image file";
                return;
            }
            else
            {
                //Add to imageList
                imageList[imageKey] = img;
                //Debug output
                Logger::writeMsg(1) << "Loaded image \"" << imageKey << "\" with filepath \"" << imagePath << "\"";
            }
        }
    }

    //Unload all images
    void ImageHandler::unloadAssets(){
        //FileHandler::unloadAssets(imageList);
        imageList.clear();
    }

    //Handle image requests
    sf::Image& ImageHandler::getImage(const std::string& imageKey){
        //Search imageList
        if( imageList.find(imageKey) != imageList.end() )
        {
            //Assign image
            return imageList[imageKey];
        }else{
            //Assign error image
            return imageList["error"];
        }
    }
}
