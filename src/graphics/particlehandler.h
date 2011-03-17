/*
/ Particle system handler class
/ Author: Felix Westin
/ File created: 2011-03-17
/ File updated: 2011-03-17
/ License: GPLv3
*/
#ifndef PARTICLEHANDLER_H_INCLUDED
#define PARTICLEHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "particlesystem.h"
#include "../sys/configreader.h"
#include "../graphics/imagehandler.h"
#include "../sys/filehandler.h" //Abstract base class

namespace sbe
{
    class ParticleHandler : public FileHandler
    {
        /*
            Loads images, stores them and handles requests
        */
        public:
            ParticleHandler(
                ConfigReader* configReader,
                ImageHandler* imageHandler
            );
            ~ParticleHandler()
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
            ParticleSystem& getPSys(const std::string& imageKey);
        private:
            ConfigReader* cfgReader;
            ImageHandler *imgHandler;
            //Image list
            //std::map<std::string, ParticleSystem> pSystemList;
    };
}

#endif
