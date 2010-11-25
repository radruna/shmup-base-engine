/*
/ Image handler class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-25
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"   //Class def
#include "filehandler.h" //Base class

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    //Load images listed in the asset file
    void ImageHandler::loadAssets(const std::string& assetFile)
    {
        std::cout << std::endl << "Loading assets from: \"" << assetFile << "\"..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, assetFile.c_str());
        //Open specified file
        fileReader.open(str);
        if(!fileReader)
        {
            //Debug output
            std::cout << "The image handler was unable to open the specified asset file" << std::endl;
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
                    std::cout << "Failed to load image \"" << imagePath << "\". Reason: Image key already in system" << std::endl;
                else
                {
                    sf::Image img;
                    //Load image file
                    if(!img.LoadFromFile(imagePath))
                    {
                        /*
                        //This is already handled by SFML
                        std::cout << "Failed to load image \"" << imagePath << "\". Reason: Unable to open image file" << std::endl;
                        */
                    }
                    else
                    {
                        //Add to imageList
                        imageList[imageKey] = img;
                        //Debug output
                        std::cout << "Loaded image \"" << imageKey << "\" with filepath \"" << imagePath << "\"" << std::endl;
                    }
                }
            }
        }
        //Debug output
        std::cout << "Finished loading images from \"" << assetFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    //Load a single image without the use of an asset file
    void ImageHandler::loadAsset(const std::string& imageKey,const std::string& imagePath)
    {
        //Search imageList
        if(imageList.find(imageKey) != imageList.end())
            std::cout << "Failed to load image \"" << imagePath << "\". Reason: Image key already in system" << std::endl;
        else
        {
            sf::Image img;
            //Load image file
            if(!img.LoadFromFile(imagePath))
            {
                /*
                //This is already handled by SFML
                std::cout << "Failed to load image \"" << imagePath << "\". Reason: Unable to open image file" << std::endl;
                */
                return;
            }
            else
            {
                //Add to imageList
                imageList[imageKey] = img;
                //Debug output
                std::cout << "Loaded image \"" << imageKey << "\" with filepath \"" << imagePath << "\"" << std::endl;
            }
        }
    }

    //Unload all images
    void ImageHandler::unloadAssets(){
        //FileHandler::unloadAssets(imageList);
        imageList.clear();
    }

    //Handle image requests
    sf::Image ImageHandler::getImage(const std::string& imageKey){
        sf::Image img;
        //Search imageList
        if( imageList.find(imageKey) != imageList.end() )
        {
            //Assign image
            img = imageList[imageKey];
        }else{
            //Assign error image
            img.LoadFromFile("assets/debug/error.png");
        }
        return img;
    }
}
