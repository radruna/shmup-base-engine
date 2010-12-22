/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-12-22
/ License: GPLv3
*/
#include <iostream> //Debug
#include <fstream> //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Audio.hpp> //Audio header

#include "filehandler.h" //Abstract base class
#include "audiohandler.h" //Def
#include "music.h" //Copyable music, hurr

namespace sbe
{
    AudioHandler::AudioHandler(const int& s, const int& m)
        : sVol(s), mVol(m)//, curSong("")
    {

        //Add intro/menu sounds
    }

    void AudioHandler::loadSound(const std::string& soundFile)
    {
        /*
            Purpose: Load the sound assets into memory.
        */
        loadAudio(soundFile, Sound);
    }

    void AudioHandler::loadMusic(const std::string& musicFile)
    {
        /*
            Purpose: Load the music assets into memory.
        */
        loadAudio(musicFile, Music);
    }

    void AudioHandler::loadAudio(const std::string& audioFile, const LoadType& load)
    {
        /*
            Purpose: Load audio assets into memory, and then save them as either sound or music
            based on if it was called by loadSound() or loadMusic().
        */
        std::cout << std::endl << "Loading assets from: \"" << audioFile << "\"..." << std::endl;
        //Open specified file
        fileReader.open(audioFile.c_str());
        if(!fileReader)
        {
            //Debug output
            std::cout << "The audio handler was unable to open the specified asset file" << std::endl;
            return;
        }
        //Saving vars
        std::string output;
        std::string audioKey;
        std::string audioPath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation
            if(strReadLine(output, audioKey, audioPath))
            {
                //Load into memory as sound or music
                if(load == Sound)
                    saveSound(audioKey, audioPath);
                else
                    saveMusic(audioKey, audioPath);
            }
        }

        //Debug output
        std::cout << "Finished loading audio from \"" << audioFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    void AudioHandler::saveSound(const std::string& soundKey, const std::string& soundPath)
    {
        /*
            Purpose: Save file from loadAudio() as sound.
        */
        //Search soundList
        if(soundList.find(soundKey) != soundList.end())
            std::cout << "Failed to load sound \"" << soundPath << "\". Reason: Sound key already in system" << std::endl;
        else
        {
            //Create soundbuffer to assign sound from file
            sf::SoundBuffer *sndbfr = new sf::SoundBuffer();
            //Load sound file
            if(!(sndbfr->LoadFromFile(soundPath)))
                std::cout << "Failed to load sound \"" << soundPath << "\". Reason: Unable to open sound file" << std::endl;
            else
            {
                //Add to soundList
                soundList[soundKey] = *sndbfr;
                //Debug output
                std::cout << "Loaded sound \"" << soundKey << "\" with filepath \"" << soundPath << "\"" << std::endl;
            }

            delete sndbfr;
        }
    }

    void AudioHandler::saveMusic(const std::string& musicKey, const std::string& musicPath)
    {
        /*
            Purpose: Save file from loadAudio() as music.
        */
        //Search musicList
        if(musicList.find(musicKey) != musicList.end())
            std::cout << "Failed to load music \"" << musicPath << "\". Reason: Music key already in system" << std::endl;
        else
        {
            //Create music to test from filepath
            sbe::Music *msc = new sbe::Music();
            //Load music file
            if(!(msc->OpenFromFile(musicPath)))
                std::cout << "Failed to load music \"" << musicPath << "\". Reason: Unable to open music file" << std::endl;
            else
            {
                //Add to musicList
                musicList[musicKey] = musicPath;
                //Debug output
                std::cout << "Loaded music \"" << musicKey << "\" with filepath \"" << musicPath << "\"" << std::endl;
            }

            delete msc;
        }
    }

    sf::SoundBuffer& AudioHandler::getSound(const std::string& soundKey)
    {
        /*
            Purpose: Return a sound buffer which can then be assigned to a sound and then played or something.
        */
        sf::SoundBuffer *sndbfr = new sf::SoundBuffer();

        if(soundList.find(soundKey) == soundList.end())
        {
            std::cout << "Failed to get sound \"" << soundKey << "\"." << std::endl;
            sndbfr->LoadFromFile("assets/sound/error.wav");
            return *sndbfr;
        }
        else
        {
            return soundList[soundKey];
        }
    }

    void AudioHandler::setVolume(const short& v)
    {
        //Set master volume
        setSFXVol(v);
        setMusicVol(v);
    }

    void AudioHandler::setSFXVol(const short& s)
    {
        //Set SFX volume
        sVol = 100;
    }

    void AudioHandler::setMusicVol(const short& m)
    {
        //Set music volume
        mVol = 100;
    }

    /*bool AudioHandler::setMusic(const std::string& musicKey)
    {
        //Set current music playing.
        stopMusic();

        if(musicList.find(musicKey) == musicList.end())
        {
            std::cout << "Music not found";
            return 1;
        }

        musicList[musicKey].Initialize(2, 44100);
        musicList[musicKey].Play();
        curSong = musicKey;
        std::cout << "Music \"" << musicKey << "\" now playing.";

        return 0;
    }

    void AudioHandler::stopMusic()
    {
        //Stop current music.
        if(musicList[curSong].GetStatus() != sf::Sound::Stopped)
            musicList[curSong].Stop();
    }

    void AudioHandler::pauseMusic()
    {
        //Pause/play current music
        if(musicList[curSong].GetStatus() != sf::Sound::Playing)
            musicList[curSong].Play();
        else
            musicList[curSong].Pause();
    }

    void AudioHandler::setMusicLoop(bool loop)
    {
        musicList[curSong].SetLoop(loop);
    }*/

    void AudioHandler::getAudioList()
    {
        for(soundMap::iterator it = soundList.begin(); it != soundList.end(); it++)
            std::cout << (*it).first << " " << std::endl;
        for(musicMap::iterator it = musicList.begin(); it != musicList.end(); it++)
            std::cout << (*it).first << " " << std::endl;

    }
}
