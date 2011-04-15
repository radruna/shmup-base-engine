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


#include "../sys/configreader.h" //Config reader
#include "../sys/filehandler.h" //Base class
#include "../sys/logger.h" //Outputs debug in console and log
#include "enemyhandler.h"   //Class def

namespace sbe
{
    EnemyHandler::EnemyHandler(ImageHandler* iHandler, ConfigReader* cfgReader)
    {
        imgHandler = iHandler;
        res = cfgReader->getRes();
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
        std::string enemyName = "none";
        std::string pathName = "none";
        std::string pSysDeath = "none";
        int life = 1;
        //float moveSpeed;
        float radius;
        Path::pathContent stats;


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
                                pathContentList.clear();
                                targetPath = parameterValue;
                                fileReader2.open(parameterValue.c_str());

                                while(!fileReader2.eof())
                                {
                                    getline(fileReader2,output);


                                    if(strReadLine(output,parameterKey,parameterValue))
                                    {

                                        //Assign parameter values
                                        if(parameterKey == "path_name") {
                                            enemyName = parameterValue;
                                            getline(fileReader2,output);
                                        }
                                    }


                                        while( strStripSpace(output) == "path" )
                                        {
                                            //Set default values
                                            stats.moveSpeed = 0;
                                            stats.startAngle = 0;
                                            stats.stopAngle = 0;
                                            stats.duration = 0;
                                            stats.orientation = 0;
                                            stats.orientStart = 0;
                                            stats.orientStop = 0;
                                            stats.orientDuration = 0;

                                            getline(fileReader2,output);

                                            if( strStripSpace(output) == "{" )
                                            {
                                                //Read until bracket ends data input
                                                while( strStripSpace(output) != "}" )
                                                {
                                                    //Read line
                                                    getline(fileReader2,output);
                                                    //Check if line is empty and perform string operation
                                                    if(strReadLine(output,parameterKey,parameterValue))
                                                    {
                                                        //Assign parameter values
                                                        if(parameterKey == "movement_speed")
                                                            stats.moveSpeed = atof(parameterValue.c_str());
                                                        else if(parameterKey == "movement_duration")
                                                            stats.duration = atof(parameterValue.c_str());
                                                        else if(parameterKey == "start_angle")
                                                            stats.startAngle = atof(parameterValue.c_str());
                                                        else if(parameterKey == "stop_angle")
                                                            stats.stopAngle = atof(parameterValue.c_str());
                                                        else if(parameterKey == "ship_orientation")
                                                            stats.orientation = atof(parameterValue.c_str());
                                                        else if(parameterKey == "orientation_start")
                                                            stats.orientStart = atof(parameterValue.c_str());
                                                        else if(parameterKey == "orientation_stop")
                                                            stats.orientStop = atof(parameterValue.c_str());
                                                        else if(parameterKey == "orientation_duration")
                                                            stats.orientDuration = atof(parameterValue.c_str());
                                                        else if(parameterKey == "stop_at_max")
                                                            stats.stopMax = atof(parameterValue.c_str());
                                                        else
                                                            Logger::writeMsg(1) << "Invalid scroll layer parameter: " << parameterKey;  //Variable not found
                                                    }
                                                }
                                                //Push new layer
                                                pathContentList.push_back(stats);

                                            }
                                        }


                                }
                                //Search enemyMap
                                if(enemyMap.find(enemyName) != enemyMap.end())
                                    Logger::writeMsg(1) << "Failed to load path \"" << targetPath << "\". Reason: Path key already in system";
                                else
                                {
                                    Path path(pathContentList);
                                    //Add to enemyMap
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
                                        else if(parameterKey == "explosion")
                                            pSysDeath = parameterValue;
                                        else if(parameterKey == "sprite_name")
                                            spriteName = parameterValue;
                                        else if(parameterKey == "path_name")
                                            pathName = parameterValue;
                                        else if(parameterKey == "hitbox_radius")
                                            radius = atof(parameterValue.c_str());
                                        else if(parameterKey == "life")
                                            life = atoi(parameterValue.c_str());
                                        else if(parameterKey == "scale_x")
                                            scale_x = atof(parameterValue.c_str());
                                        else if(parameterKey == "scale_y")
                                            scale_y = atof(parameterValue.c_str());
                                        else
                                            Logger::writeMsg(1) << "Invalid enemy parameter: " << parameterKey;  //Variable not found

                                    }
                                }
                                //Search enemyMap
                                if(enemyMap.find(enemyName) != enemyMap.end())
                                    Logger::writeMsg(1) << "Failed to load enemy \"" << enemyName << "\". Reason: Enemy key already in system";
                                else
                                {
                                    Enemy enemy(imgHandler,spriteName, getPath(pathName), radius, pSysDeath, life, scale_x, scale_y);

                                    //Add to enemyMap
                                    enemyMap[enemyName] = enemy;
                                    //Debug output
                                    Logger::writeMsg(1) << "Loaded enemy \"" << enemyName << "\" with filepath \"" << targetPath << "\"";
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
    void EnemyHandler::unloadAssets()
    {
        //FileHandler::unloadAssets(enemyMap);
        enemyMap.clear();
        pathList.clear();
        pathContentList.clear();
    }

    //Handle enemy requests
    sbe::Enemy EnemyHandler::getEnemy(const std::string& enemyKey)
    {
        //Search enemyMap
        if( enemyMap.find(enemyKey) != enemyMap.end() )
        {
            //Assign enemy
            return enemyMap[enemyKey];
        }
        else{
            //Assign error image
            return enemyMap["enemy1"];
        }
    }

    sbe::Enemy EnemyHandler::getEnemy(unsigned int index)
    {
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < index; i++)
            it++;

        return *it;
    }

    //Handle path requests
    sbe::Path EnemyHandler::getPath(const std::string& enemyKey)
    {
        //Search enemyMap
        if( pathList.find(enemyKey) != pathList.end() )
        {
            //Assign enemy
            return pathList[enemyKey];
        }
        else{
            //Assign error image
            return pathList["path1"];
        }
    }

    void EnemyHandler::spawnEnemies(const std::string& type, const int& amount, const float& interval, const float& spacing, const float& offset, const int& side)
    {
        float width = (amount-1)*spacing;
        if(side == 0)
        {
            for(int i=0; i<amount; i++){
                Enemy enm = getEnemy(type);
                enm.SetPosition(res.x + interval*i, (res.y-width)/2 + (i*spacing) + offset);
                Logger::writeMsg(1) << "Enemy"<<i<<" spawned at "<<res.x + interval*i<<","<<(res.y-width)/2 + (i*spacing) + offset;
                enemyList.push_back(enm);
            }
        }else if(side == 1)
        {
             for(int i=0; i<amount; i++){
                Enemy enm = getEnemy(type);
                enm.SetPosition((res.x-width)/2 + (i*spacing) + offset, res.y + interval*i);
                Logger::writeMsg(1) << "Enemy"<<i<<" spawned at "<<(res.x-width)/2 + (i*spacing) + offset<<","<<res.y + interval*i;
                enemyList.push_back(enm);
            }
        }else if(side == 2)
        {
            for(int i=0; i<amount; i++){
                Enemy enm = getEnemy(type);
                enm.SetPosition(0 - interval*i, (res.y-width)/2 + (i*spacing) + offset);
                Logger::writeMsg(1) << "Enemy"<<i<<" spawned at "<<0 - interval*i<<","<<(res.y-width)/2 + (i*spacing) + offset;
                enemyList.push_back(enm);
            }
        }else if(side == 3)
        {
            for(int i=0; i<amount; i++){
                Enemy enm = getEnemy(type);
                enm.SetPosition((res.x-width)/2 + (i*spacing) + offset, 0 - interval*i);
                Logger::writeMsg(1) << "Enemy"<<i<<" spawned at "<<(res.x-width)/2 + (i*spacing) + offset<<","<<0 - interval*i;
                enemyList.push_back(enm);
            }
        }


    }

    void EnemyHandler::Render(sf::RenderTarget& Target) const
    {
        for(std::list<Enemy>::const_iterator it = enemyList.begin(); it != enemyList.end(); it++)
        {
            Target.Draw(*it);
        }
    }

    void EnemyHandler::update(const float& elapsed)
    {
        /*for(std::list<Enemy>::iterator it = enemyList.begin(); it != enemyList.end(); it++)
        {
            it->update(elapsed);
            if(it->death())
            {
                std::list<Enemy>::iterator it2 = it;
                enemyList.erase(it2);
            }
        }*/

        bool kill = false;
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < enemyList.size(); i++)
        {
            it->update(elapsed);
            if(it->death())
            {
                kill = true;
                break;
            }
            it++;
        }

        if(kill) enemyList.erase(it);
    }

    int EnemyHandler::enemyListSize()
    {
        return enemyList.size();
    }

    float EnemyHandler::enemyRadius(unsigned int index)
    {
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < index; i++)
            it++;

        return it->returnRadius();
    }

    float EnemyHandler::enemyXpos(unsigned int index)
    {
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < index; i++)
            it++;

        return it->xPos();
    }

    float EnemyHandler::enemyYpos(unsigned int index)
    {
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < index; i++)
            it++;

        return it->yPos();
    }

    int EnemyHandler::hitEnemy(unsigned int index)
    {
        std::list<Enemy>::iterator it = enemyList.begin();
        for(unsigned int i = 0; i < index; i++)
            it++;

        if(it->readyToDie()) return -1;
        it->hit();
        if(it->isDead())
        {
            it->kill();
            deathSound.Play();
            return 0;
        }

        return 1;
    }

}
