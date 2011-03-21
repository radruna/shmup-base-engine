/*
/ Enemy handler class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-18
/ File updated: 2011-03-18
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "enemyhandler.h"   //Class def

namespace sbe
{
    EnemyHandler::EnemyHandler(ImageHandler* iHandler)
    {
        imgHandler = iHandler;
    }

    //Load images listed in the asset file
    void EnemyHandler::loadAssets(const std::string& assetFile)
    {
        std::ifstream fileReader;
        std::ifstream fileReader2;
        Logger::writeMsg(1) << "\nLoading assets from: \"" << assetFile << "\"...";
        //Open specified file
        fileReader.open(assetFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The enemy handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string parameterKey;
        std::string parameterValue;
        std::string enemyPath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);

            //If line == "info"...
            while( strStripSpace(output) == "enemies" )
            {
                //Read line
                getline(fileReader,output);

                //...look for bracket and start reading data
                if( strStripSpace(output) == "{" )
                {
                    //Read until bracket ends data input
                    while( strStripSpace(output) != "}" )
                    {
                        //Read line
                        getline(fileReader,output);
                        //Check if line is empty and perform string operation
                        if(strReadLine(output,parameterKey,parameterValue))
                        {
                            if(parameterKey == "enemy")
                            {
                                enemyPath = parameterValue;
                                fileReader2.open(parameterValue.c_str());
                                std::string spriteName;

                                while(!fileReader2.eof())
                                {
                                    getline(fileReader2,output);

                                    if(strReadLine(output,parameterKey,parameterValue))
                                    {
                                        /*
                                        //Assign parameter values
                                        if(parameterKey == "sprite_name")
                                            spriteName = parameterValue;
                                        else if(parameterKey == "movement_angle")
                                            moveAngle = atoi(parameterValue.c_str());
                                        else if(parameterKey == "movement_speed")
                                            moveSpeed = atoi(parameterValue.c_str());
                                        else if(parameterKey == "offset_x")
                                            xOffset = atof(parameterValue.c_str());
                                        else if(parameterKey == "offset_y")
                                            yOffset = atof(parameterValue.c_str());
                                        else if(parameterKey == "scale_x")
                                            xScale = atof(parameterValue.c_str());
                                        else if(parameterKey == "scale_y")
                                            yScale = atof(parameterValue.c_str());
                                        else if(parameterKey == "tile_x")
                                            tile_x = (bool) atoi(parameterValue.c_str());
                                        else if(parameterKey == "tile_y")
                                            tile_y = (bool) atoi(parameterValue.c_str());
                                        else if(parameterKey == "fit_x")
                                            fit_x = (bool) atoi(parameterValue.c_str());
                                        else if(parameterKey == "fit_y")
                                            fit_y = (bool) atoi(parameterValue.c_str());
                                        else
                                            Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;  //Variable not found
                                        */
                                    }
                                }
                                //Search enemyList
                                if(enemyList.find(parameterKey) != enemyList.end())
                                    Logger::writeMsg(1) << "Failed to load enemy \"" << enemyPath << "\". Reason: Enemy key already in system";
                                else
                                {
                                    Enemy enemy(imgHandler,spriteName);
                                    //Add to enemyList
                                    enemyList[parameterKey] = enemy;
                                    //Debug output
                                    Logger::writeMsg(1) << "Loaded enemy \"" << parameterKey << "\" with filepath \"" << enemyPath << "\"";
                                }
                            }
                        }
                    }
                }
            }
        }
        //Debug output
        Logger::writeMsg(1) << "Finished loading enemy from \"" << assetFile << "\"";
        //Close file
        fileReader.close();
    }

    //Unload all enemies
    void EnemyHandler::unloadAssets(){
        //FileHandler::unloadAssets(enemyList);
        enemyList.clear();
    }
/*
    //Handle image requests
    sbe::Enemy& EnemyHandler::getEnemy(const std::string& enemyKey){
        //Search enemyList
        if( enemyList.find(enemyKey) != enemyList.end() )
        {
            //Assign image
            return enemyList[enemyKey];
        }else{
            //Assign error image
            return enemyList["error"];
        }
    }

    */
}
