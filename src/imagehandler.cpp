/*
/ Image handler class
/ Author: Felix Willebrand Westin
/ File created: 2010-11-16
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <map> //Map for objects

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"   //Class def

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    void loadAssets(std::string& assetFile){    //Load images listed in the asset file
    }
    void unloadAssets(){    //Unload all images
    }

    sf::Image getImage(std::string& imageFile){  //TEMPORARY
        if(imageFile == "testShip")
        {
            sf::Image img;
            img.LoadFromFile("assets/jet.png");
            return img;
        }
    }
}
    /*
    sf::Image getImage(std::string& imageKey){
    }
    */
