/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-17
/ License: GPLv3
*/
#include <iostream> //Debug
#include <fstream> //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Audio.hpp> //Audio header

#include "filehandler.h" //Abstract base class
#include "audiohandler.h" //Def

namespace sbe
{
    AudioHandler::AudioHandler()
    {
        //Add intro/menu sounds
    }

    void AudioHandler::loadSound(const std::string& soundKey)
    {
        /*
            Purpose: Load the sound assets into memory.
        */
        loadAudio(soundKey, Sound);
    }

    void AudioHandler::loadMusic(const std::string& musicKey)
    {
        /*
            Purpose: Load the sound assets into memory.
        */
        loadAudio(soundKey, Sound);
    }

    void AudioHandler::loadAudio(const std::string& audioKey, LoadType load)
    {
        /*
            Purpose: Load audio assets into memory, and then save them as either sound or music
            based on if it was called by loadSound() or loadMusic().
        */
        std::cout << std::endl << "Loading assets from: \"" << assetFile << "\"..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, assetFile.c_str());
        //Open specified file
        if(!fileReader.open(str))
        {
            //Debug output
            std::cout << "The audio handler was unable to open the specified asset file" << std::endl;
            return;
        }

        int spacePos;
        std::string output;
        std::string audioKey;
        std::string audioPath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty
            if(output != "")
            {
                //Find space
                spacePos = output.find (' ');
                //Set audio key
                audioKey = output.substr(0,spacePos);
                //Load into memory as sound or memory
                if(load == Sound)
                    saveSound(audioKey, audioPath, output);
                else
                    saveMusic(audioKey, audioPath, output);
            }
        }

        //Debug output
        std::cout << "Finished loading audio from \"" << assetFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    void AudioHandler::saveSound(const std::string& soundKey, const std::string& soundPath, const std::string& output)
    {
        /*
            Purpose: Save file from loadAudio() as sound.
        */
        //Search soundList
        if(soundList.find(soundKey) != soundList.end())
            std::cout << "Failed to load sound \"" << soundPath << "\". Reason: Sound key already in system" << std::endl;
        else
        {
            //Set sound file path
            soundPath = output.substr(spacePos + 1, output.length() - (spacePos + 1));
            //Create soundbuffer to assign sound from file
            sf::SoundBuffer sndbfr;
            //Load sound file
            if(!sndbfr.LoadFromFile(soundPath))
                std::cout << "Failed to load sound \"" << soundPath << "\". Reason: Unable to open sound file" << std::endl;
            else
            {
                //Create sound for saving to memory and assign it the loaded soundbuffer
                sf::Sound snd(sndbfr);
                //Add to soundList
                soundList[soundKey] = sndbfr;
                //Debug output
                std::cout << "Loaded sound \"" << soundKey << "\" with filepath \"" << soundPath << "\"" << std::endl;
            }
        }
    }

    void AudioHandler::saveMusic(const std::string& musicKey, const std::string& musicPath, const std::string& output)
    {
        /*
            Purpose: Save file from loadAudio() as music.
        */
        //Search musicList
        if(musicList.find(musicKey) != musicList.end())
            std::cout << "Failed to load music \"" << musicPath << "\". Reason: Music key already in system" << std::endl;
        else
        {
            //Set music file path
            musicPath = output.substr(spacePos + 1, output.length() - (spacePos + 1));
            //Create music to assign from file
            sf::Music msc;
            //Load music file
            if(!msc.LoadFromFile(musicPath))
                std::cout << "Failed to load music \"" << musicPath << "\". Reason: Unable to open music file" << std::endl;
            else
            {
                //Add to musicList
                musicList[musicKey] = msc;
                //Debug output
                std::cout << "Loaded music \"" << musicKey << "\" with filepath \"" << musicPath << "\"" << std::endl;
            }
        }
    }

    sf::Sound AudioHandler::getSound(const std::string& soundKey)
    {
        sf::Sound snd;

        if(soundList.find(soundKey) == soundList.end())
        {
            std::cout << "Failed to get sound \"" << soundKey << "\""".
            return;
        }
        else
        {

        }

    }
}
