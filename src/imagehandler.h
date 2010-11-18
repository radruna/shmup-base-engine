/*
/ Image handler class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-17
/ License: GPLv3
*/
#ifndef IMAGEHANDLER_H_INCLUDED
#define IMAGEHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "filehandler.h" //Abstract base class

namespace sbe
{
    class ImageHandler : public FileHandler
    {
        /*
            Loads images, stores them and handles requests
        */
        public:
            ImageHandler();
            ~ImageHandler()
            {
                unloadAssets();
            }

            //Load images listed in the asset file
            void loadAssets(const std::string& assetFile);
            //Load a single image without the use of an asset file
            void loadAsset(const std::string& imageKey,const std::string& filePath);
            //Unload all images
            void unloadAssets();
            //Handle image requests
            sf::Image getImage(const std::string& imageKey);
        private:
            //Image list
            std::map<std::string, sf::Image> imageList;
    };
}

#endif
