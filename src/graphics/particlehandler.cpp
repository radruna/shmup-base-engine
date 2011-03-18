/*
/ particle system handler class
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
#include "particlehandler.h"   //Class def

namespace sbe
{
    ParticleHandler::ParticleHandler(
        ConfigReader* configReader,
        ImageHandler* imageHandler
    )
    {
        //Save config reader pointer
        cfgReader = configReader;
        //Save image handler pointer
        imgHandler = imageHandler;
    }

    //Load particle systems listed in the asset file
    void ParticleHandler::loadAssets(const std::string& assetFile)
    {
        std::ifstream fileReader;
        Logger::writeMsg(1) << "\nLoading assets from: \"" << assetFile << "\"...";
        //Open specified file
        fileReader.open(assetFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The particle system handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string pSysKey;
        std::string pSysPath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation

            if(strReadLine(output,pSysKey,pSysPath))
            {

                //Search pSystemList
                if(pSystemList.find(pSysKey) != pSystemList.end())
                    Logger::writeMsg(1) << "Failed to load particle system \"" << pSysPath << "\". Reason: Particle system key already in system";
                else
                {

                    ParticleSystem pSys(pSysPath, imgHandler, cfgReader->getSetting<float>("ps_reload"));

                    //Add to pSystemList
                    pSystemList[pSysKey] = pSys;
                    //Debug output
                    Logger::writeMsg(1) << "Loaded particle system \"" << pSysKey << "\" with filepath \"" << pSysPath << "\"";
                }

            }
        }
        //Debug output
        Logger::writeMsg(1) << "Finished loading particle systems from \"" << assetFile << "\"";
        //Close file
        fileReader.close();
    }

    //Load a single particle system without the use of an asset file
    void ParticleHandler::loadAsset(const std::string& pSysKey,const std::string& pSysPath)
    {

        //Search pSystemList
        if(pSystemList.find(pSysKey) != pSystemList.end())
            Logger::writeMsg(1) << "Failed to load particle system \"" << pSysPath << "\". Reason: particle system key already in system";
        else
        {
            ParticleSystem pSys(pSysPath, imgHandler, cfgReader->getSetting<float>("ps_reload"));

            //Add to pSystemList
            pSystemList[pSysKey] = pSys;
            //Debug output
            Logger::writeMsg(1) << "Loaded particle system \"" << pSysKey << "\" with filepath \"" << pSysPath << "\"";
        }

    }

    //Unload all particle systems
    void ParticleHandler::unloadAssets(){
        //unloadAssets(pSystemList);
        pSystemList.clear();
    }

    //Handle particle system requests
    ParticleSystem& ParticleHandler::getPSys(const std::string& pSysKey){

        //Search pSystemList
        if( pSystemList.find(pSysKey) != pSystemList.end() )
        {
            //Assign particle system
            return pSystemList[pSysKey];
        }else{
            //Assign error particle system
            return pSystemList["error"];
        }

    }
}
