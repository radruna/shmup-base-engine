/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2011-01-30
/ License: GPLv3
*/
#include <iostream> //Debug
#include <fstream> //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Audio.hpp> //Audio header

#include "../sys/filehandler.h" //Abstract base class
#include "audiohandler.h" //Def
#include "music.h" //Copyable music, hurr
#include "../sys/logger.h" //Outputs debug in console and log

namespace sbe
{
    AudioHandler::AudioHandler(const int& s, const int& m)
        : sVol(s), mVol(m)//, curSong("")
    {
        song = NULL;
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
        std::ifstream fileReader;
        /*
            Purpose: Load audio assets into memory, and then save them as either sound or music
            based on if it was called by loadSound() or loadMusic().
        */
        Logger::writeMsg(1) << "\nLoading assets from: \"" << audioFile << "\"...";
        //Open specified file
        fileReader.open(audioFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The audio handler was unable to open the specified asset file";
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
        Logger::writeMsg(1) << "Finished loading audio from \"" << audioFile << "\"";
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
            Logger::writeMsg(1) << "Failed to load sound \"" << soundPath << "\". Reason: Sound key already in system";
        else
        {
            //Create soundbuffer to assign sound from file
            sf::SoundBuffer *sndbfr = new sf::SoundBuffer();
            //Load sound file
            if(!(sndbfr->LoadFromFile(soundPath)))
                Logger::writeMsg(1) << "Failed to load sound \"" << soundPath << "\". Reason: Unable to open sound file";
            else
            {
                //Add to soundList
                soundList[soundKey] = *sndbfr;
                //Debug output
                Logger::writeMsg(1) << "Loaded sound \"" << soundKey << "\" with filepath \"" << soundPath << "\"";
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
            Logger::writeMsg(1) << "Failed to load music \"" << musicPath << "\". Reason: Music key already in system";
        else
        {
            //Create music to test from filepath
            sbe::Music *msc = new sbe::Music();
            //Load music file
            if(!(msc->OpenFromFile(musicPath)))
                Logger::writeMsg(1) << "Failed to load music \"" << musicPath << "\". Reason: Unable to open music file";
            else
            {
                //Add to musicList
                musicList[musicKey] = musicPath;
                //Debug output
                Logger::writeMsg(1) << "Loaded music \"" << musicKey << "\" with filepath \"" << musicPath << "\"";
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
            Logger::writeMsg(1) << "Failed to get sound \"" << soundKey << "\".";
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
        sVol = s;
    }

    void AudioHandler::setMusicVol(const short& m)
    {
        //Set music volume
        mVol = m;
    }

    bool AudioHandler::setMusic(const std::string& musicKey)
    {
        //Set current music playing.
        //stopMusic();

        if(musicList.find(musicKey) == musicList.end())
        {
            Logger::writeMsg(1) << "Music not found: " << musicKey;
            return true;
        }

        song = new sbe::Music();
        if(!song->OpenFromFile(musicList[musicKey]))
        {
            Logger::writeMsg(1) << "Music could not be loaded!";
            safeDelete(song);
            return true;
        }
        song->SetVolume(mVol);
        song->Initialize(2, 44100);
        song->Play();
        Logger::writeMsg(1) << "Music \"" << musicKey << "\" now playing.";

        return false;
    }

    /*void AudioHandler::stopMusic()
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
