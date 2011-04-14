/*
/ Stage class
/ Author: Felix Westin
/ File created: 2011-03-14
/ File updated: 2011-03-15
/ License: GPLv3
*/
#include <iostream> //Debug output

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/const.h" //Constants
#include "../sys/logger.h" //Outputs debug in console and log
#include "../game/movable.h" //Base entity class
#include "../game/stage.h"   //Header
//#include "../graphics/layer.h"   //Layer class
//#include "../audio/audiohandler.h"
#include <list> //For lists
//#include "../graphics/background.h" // Background

namespace sbe
{

    Stage::Stage
    (
        ConfigReader* configReader,
        ImageHandler* imageHandler,
        AudioHandler* audioHandler,
        EnemyHandler* enemyHandler,
        ParticleHandler* particleHandler,
        const std::string& stageScriptFile
    )

    {
        //Save config reader pointer
        cfgReader = configReader;
        //Save image handler pointer
        imgHandler = imageHandler;
        //Save audio handler pointer
        audHandler = audioHandler;
        //Save enemy handler pointer
        enmHandler = enemyHandler;
        //Save particle handler pointer
        prcHandler = particleHandler;
        //Save stage file
        stageFile = stageScriptFile;

        eventPos = 0;
        eventCounter = 0;

        bg = NULL;
        //Load stage
        load();
    }

    void Stage::load()
    {
        std::ifstream fileReader;

        Logger::writeMsg(1) << "\nLoading stage" << stageFile;

        //Set default values
        bg = NULL;

        //Open specified file
        fileReader.open(stageFile.c_str());

        if(!fileReader.is_open())
        {
            //Debug output
            Logger::writeMsg(1) << "Couldn't open the specified stage file";
            fileReader.close();
            return; //Um, can I do this?
        }

        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);

            //If line == "info"...
            while( strStripSpace(output) == "info" )
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
                            /*
                            //Assign parameter values
                            if(parameterKey == "name")
                                info_name = parameterValue;
                            else if(parameterKey == "mod")
                                info_mod = parameterValue;
                            else if(parameterKey == "chapter")
                                info_chapter = atoi(parameterValue.c_str());
                            else
                                Logger::writeMsg(1) << "Invalid map info parameter: " << parameterKey;  //Variable not found
                            */
                        }
                    }
                }
            }

            //If line == "data"...
            while( strStripSpace(output) == "data" )
            {
                //Read line
                getline(fileReader,output);

                //...look for bracket and start reading data
                if( strStripSpace(output) == "{" )
                {
                    Logger::writeMsg(1) << "\nLoading data...";
                    //Read until bracket ends data input

                    std::string bgFile = "";

                    while( strStripSpace(output) != "}" )
                    {
                        //Read line
                        getline(fileReader,output);
                        //Check if line is empty and perform string operation
                        if(strReadLine(output,parameterKey,parameterValue))
                        {
                            //Assign parameter values
                            if(parameterKey == "background")
                                bgFile = parameterValue;
                            if(parameterKey == "images")
                                imgHandler->loadAssets(parameterValue); //Load image asset file using image handler
                            else if(parameterKey == "sounds")
                                audHandler->loadSound(parameterValue); //Load sound asset file using audio handler
                            else if(parameterKey == "music")
                                audHandler->loadMusic(parameterValue); //Load music asset file using audio handler
                            else if(parameterKey == "enemies")
                                enmHandler->loadAssets(parameterValue); //Load enemies + paths using enemy handler
                            else if(parameterKey == "particles")
                                prcHandler->loadAssets(parameterValue);
                            else
                                Logger::writeMsg(1) << "Invalid map asset parameter: " << parameterKey;  //Variable not found
                        }
                    }

                    if( bgFile == "")
                    {}
                    else
                        bg = new Background(cfgReader, bgFile, imgHandler);

                    Logger::writeMsg(1) << "\nData loaded";
                }
            }

            //If line == "map"...
            while( strStripSpace(output) == "map" )
            {
                //Read line
                getline(fileReader,output);

                //...look for bracket and start reading data
                if( strStripSpace(output) == "{" )
                {
                    Logger::writeMsg(1) << "\nLoading map data...";
                    //Read until bracket ends data input

                    while( strStripSpace(output) != "}" )
                    {
                        //Read line
                        getline(fileReader,output);
                        //Check if line is empty
                        if(output != "")
                        {
                            eventList.push_back(output);
                        }
                    }

                    Logger::writeMsg(1) << "\nData loaded";
                }
            }
        }
    }

    void Stage::Render(sf::RenderTarget& Target) const
    {
        if(bg != NULL)
            Target.Draw(*bg);   //Update background

        Target.Draw(*enmHandler);
    }

    void Stage::update(const float& elapsed)
    {
        if(bg != NULL)
            bg->update(elapsed);    //Update background

        eventCounter -= elapsed;    //Count time

        if(eventCounter <= 0 && eventList.size() > eventPos)
        {
            if(eventList.at(eventPos) == "")
            {}
            else
            {
                std::string quote = nextQuote(eventList.at(eventPos));
                if(quote != "")
                {
                    if(quote == "break")
                    {
                        float timeAdd = atof( nextQuote(eventList.at(eventPos)).c_str() );
                        //eventCounter = atof( nextQuote(eventList.at(eventPos)).c_str() );
                        Logger::writeMsg(1) << "Break! More time added to map counter: " << timeAdd;
                        eventCounter = timeAdd;
                        //eventPos++;
                    }
                    else if(quote == "pause_music")
                    {
                        audHandler->pauseMusic();
                    }
                    else if(quote == "fade_out_music")
                    {
                        float fade = atof( nextQuote(eventList.at(eventPos)).c_str());
                        audHandler->fadeOut(elapsed, "", fade);
                        Logger::writeMsg(1) << "Fading out for " << fade << " seconds.";
                    }
                    else if(quote == "crossfade_music")
                    {
                        std::string newSong = nextQuote(eventList.at(eventPos));
                        float fade = atof( nextQuote(eventList.at(eventPos)).c_str());
                        audHandler->fadeOut(elapsed, newSong, fade);
                        Logger::writeMsg(1) << "Fading out for " << fade << " seconds.";
                    }
                    else if(quote == "change_music")
                    {
                        std::string piss = nextQuote(eventList.at(eventPos));
                        Logger::writeMsg(1) << piss;
                        audHandler->setMusic( piss );
                    }
                    else if(quote == "enemy")
                    {
                        enmHandler->spawnEnemies("enemy1",4,100,100,100,1);
                    }
                    else if(quote == "bg_speed")
                    {
                        float piss = atof( nextQuote(eventList.at(eventPos)).c_str() );
                        bg->setSpeedFactor( piss );
                    }
                    else if(quote == "fin")
                    {
                        //HOLY SHIT YOU WON
                    }
                }
                eventPos++;
            }
        }
        enmHandler->update(elapsed);
    }

    std::string Stage::nextQuote(std::string& strSource)
    {
        //Quotation mark position array
        int qPos[2];

        //Find first quotation mark
        qPos[0] = strSource.find("\"");
        if(qPos[0] == -1)
            return "";

        //Find second quotation mark
        qPos[1] = strSource.find("\"",  qPos[0] + 1);
        if(qPos[1] == -1)
            return "";

        std::string newStr = strSource.substr(qPos[0] + 1,qPos[1] - qPos[0] -1);
        strSource = strSource.substr( qPos[1] + 1, strSource.length() - newStr.length() );
        return newStr;
    }
}
