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

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"   //Class def

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    void ImageHandler::loadAssets(const std::string& assetFile){    //Load images listed in the asset file
        char str[255];
        strcpy(str, assetFile.c_str()); //Convert string to char array
        fileReader.open(str);   //Open specified file
        char output[255];   //Char array output, should be replaced by a list with dynamic length
        if(fileReader.is_open())
        {
            while(!fileReader.eof())    //Read until end of file
            {
                fileReader >> output;
                std::cout << output;
            }
        }
        fileReader.close(); //Close file
    }

    void ImageHandler::unloadAssets(){    //Unload all images
        imageList.clear();
    }

    sf::Image ImageHandler::getImage(const std::string& imageKey){  //TEMPORARY
        sf::Image img;
        if(imageKey == "testShip")
        {
            img.LoadFromFile("assets/jet.png");
        }else{
            img.LoadFromFile("assets/debug/error.png");
        }
        return img;
    }
}
    /*
    sf::Image getImage(std::string& imageKey){
    }
    */
