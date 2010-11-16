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
