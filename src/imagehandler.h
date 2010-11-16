/*
/ Image handler class
/ Author: Felix Willebrand Westin
/ File created: 2010-11-16
/ File updated: 2010-11-16
/ License: GPLv3
*/
#ifndef IMAGEHANDLER_H_INCLUDED
#define IMAGEHANDLER_H_INCLUDED

#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects

#include <string>

#include <SFML/Graphics.hpp> //Sfml stuff

namespace sbe
{
    class ImageHandler
    {
        /*
            Loads images, stores them and handles requests
        */
        public:
            ImageHandler();
            ~ImageHandler()
            {

            }
            std::ifstream fileReader;
            std::map<std::string, sf::Image> imageList; //Image list
            void loadAssets(std::string& assetFile);    //Load images listed in the asset file
            void unloadAssets();    //Unload all images
            sf::Image getImage(std::string& imageKey);  //Request image
        private:
    };
}
#endif IMAGEHANDLER_H_INCLUDED
