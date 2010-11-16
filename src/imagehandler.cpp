/*
/ Image handler class
/ Author: Felix Willebrand Westin
/ File created: 2010-11-16
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects

#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"   //Class def

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    void ImageHandler::loadAssets(const std::string& assetFile){    //Load images listed in the asset file
        std::cout << std::endl << "Loading assets from: '" << assetFile << "'..." << std::endl;
        char str[255];
        strcpy(str, assetFile.c_str()); //Convert string to char array
        fileReader.open(str);   //Open specified file
        if(fileReader.is_open())
        {
            int spacePos;
            std::string output;
            std::string imageKey;
            std::string imagePath;
            while(!fileReader.eof())    //Loop until end of file
            {
                getline(fileReader,output);
                spacePos = output.find (' ');   //Find space
                imageKey = output.substr(0,spacePos);   //Set image key
                imagePath = output.substr(spacePos+1,output.length() - (spacePos + 1));  //Set image path
                std::cout << "Loaded image: '" << imageKey << "' with filepath: '" << imagePath << "'" << std::endl;
                sf::Image img;
                img.LoadFromFile(imagePath);
                imageList[imageKey] = img;
            }
            std::cout << "Finished loading assets from: '" << assetFile << "'" << std::endl;
        }else
        {
            std::cout << "The image handler was unable to open the specified asset file." << std::endl;
        }
        fileReader.close(); //Close file
    }

    void ImageHandler::unloadAssets(){    //Unload all images
        imageList.clear();
    }

    sf::Image ImageHandler::getImage(const std::string& imageKey){  //TEMPORARY
        sf::Image img;
        std::cout << imageKey;
        //if( imageList.find(imageKey) != imageList.end() )   //Search imageList
        if(true)
        {
            img = imageList[imageKey];  //Assign image
        }else{
            img.LoadFromFile("assets/debug/error.png"); //Assign error image
        }
        return img;
    }
}
