/*
/ Enemy handler class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-18
/ File updated: 2011-03-22
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
        std::string targetPath;
        std::string enemyName;
        std::string pathName;
        float moveSpeed;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);

            //If line == "info"...
            while( strStripSpace(output) == "path" )
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
                            if(parameterKey == "path")
                            {
                                targetPath = parameterValue;
                                fileReader2.open(parameterValue.c_str());

                                while(!fileReader2.eof())
                                {
                                    getline(fileReader2,output);

                                    if(strReadLine(output,parameterKey,parameterValue))
                                    {

                                        //Assign parameter values
                                        if(parameterKey == "path_name")
                                            enemyName = parameterValue;
                                        else if(parameterKey == "movement_speed")
                                            moveSpeed = atof(parameterValue.c_str());
                                            /*
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
                                            */
                                        else
                                            Logger::writeMsg(1) << "Invalid path parameter: " << parameterKey;  //Variable not found

                                    }
                                }
                                //Search enemyList
                                if(enemyList.find(enemyName) != enemyList.end())
                                    Logger::writeMsg(1) << "Failed to load path \"" << targetPath << "\". Reason: Path key already in system";
                                else
                                {
                                    Path path(moveSpeed);
                                    //Add to enemyList
                                    pathList[enemyName] = path;
                                    //Debug output
                                    Logger::writeMsg(1) << "Loaded path \"" << parameterKey << "\" with filepath \"" << targetPath << "\"";
                                }

                                fileReader2.close();
                            }
                        }
                    }
                }
            }

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
                                targetPath = parameterValue;
                                fileReader2.open(parameterValue.c_str());
                                std::string spriteName;

                                while(!fileReader2.eof())
                                {
                                    getline(fileReader2,output);

                                    if(strReadLine(output,parameterKey,parameterValue))
                                    {

                                        //Assign parameter values
                                        if(parameterKey == "enemy_name")
                                            enemyName = parameterValue;
                                        else if(parameterKey == "sprite_name")
                                            spriteName = parameterValue;
                                        else if(parameterKey == "path_name")
                                            pathName = parameterValue;

                                            /*
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
                                            */
                                        else
                                            Logger::writeMsg(1) << "Invalid enemy parameter: " << parameterKey;  //Variable not found

                                    }
                                }
                                //Search enemyList
                                if(enemyList.find(enemyName) != enemyList.end())
                                    Logger::writeMsg(1) << "Failed to load enemy \"" << targetPath << "\". Reason: Enemy key already in system";
                                else
                                {
                                    Enemy enemy(imgHandler,spriteName, getPath(pathName));
                                    //Add to enemyList
                                    enemyList[enemyName] = enemy;
                                    //Debug output
                                    Logger::writeMsg(1) << "Loaded enemy \"" << parameterKey << "\" with filepath \"" << targetPath << "\"";
                                }

                                fileReader2.close();
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

    //Handle enemy requests
    sbe::Enemy& EnemyHandler::getEnemy(const std::string& enemyKey){
        //Search enemyList
        if( enemyList.find(enemyKey) != enemyList.end() )
        {
            //Assign enemy
            return enemyList[enemyKey];
        }
        /*
        else{
            //Assign error image
            return enemyList["error"];
        }
        */
    }

    //Handle path requests
    sbe::Path& EnemyHandler::getPath(const std::string& enemyKey){
        //Search enemyList
        if( pathList.find(enemyKey) != pathList.end() )
        {
            //Assign enemy
            return pathList[enemyKey];
        }
        /*
        else{
            //Assign error image
            return enemyList["error"];
        }
        */
    }


}
