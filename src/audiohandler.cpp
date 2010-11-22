/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-18
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
    AudioHandler::AudioHandler(int s, int m)
        : sVol(s), mVol(m), curSong("")
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
            Purpose: Load the sound assets into memory.
        */
        loadAudio(musicFile, Music);
    }

    void AudioHandler::loadAudio(const std::string& audioFile, LoadType load)
    {
        /*
            Purpose: Load audio assets into memory, and then save them as either sound or music
            based on if it was called by loadSound() or loadMusic().
        */
        std::cout << std::endl << "Loading assets from: \"" << audioFile << "\"..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, audioFile.c_str());
        //Open specified file
        fileReader.open(str);
        if(!fileReader)
        {
            //Debug output
            std::cout << "The audio handler was unable to open the specified asset file" << std::endl;
            return;
        }
        //Saving vars
        int tabPos;
        int spacePos;
        int commentPos;
        int lineVar = 0;
        std::string output;
        std::string audioKey;
        std::string audioPath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
             //Check line for comment
            if(output.find("//") != std::string::npos)
            {
                 //Find comment
                commentPos = output.find("//");
                //Cut comment
                output = output.substr(0,commentPos);
            }
            //Check if line is empty
            if(output != "")
            {
                //Register new line
                lineVar++;
                //Replace tabs with spaces
                while(output.find('\t') != std::string::npos)
                {
                    tabPos = output.find('\t');
                    output.replace(tabPos,1," ");
                }

                //Find first space
                if(output.find(' ' ) == std::string::npos)
                {
                    //If not found
                    std::cout << "Incorrect audio file on line " << lineVar << " in file \"" << audioFile << "\"" << std::endl;
                }
                else
                {
                    //Find first space
                    spacePos = output.find (' ');

                    //Set audio key
                    audioKey = output.substr(0,spacePos);
                    //Search and remove any spaces
                    FileHandler::stringStripSpace(audioKey);

                    //Set audio path
                    audioPath = output.substr(audioKey.length(),output.length());
                    //Search and remove any spaces
                    FileHandler::stringStripSpace(audioPath);

                    //Load into memory as sound or music
                    if(load == Sound)
                        saveSound(audioKey, audioPath, output);
                    else
                        saveMusic(audioKey, audioPath, output);
                }
            }
        }

        //Debug output
        std::cout << "Finished loading audio from \"" << audioFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    void AudioHandler::saveSound(std::string& soundKey, std::string& soundPath, std::string& output)
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
            sf::SoundBuffer sndbfr;
            //Load sound file
            if(!sndbfr.LoadFromFile(soundPath))
                std::cout << "Failed to load sound \"" << soundPath << "\". Reason: Unable to open sound file" << std::endl;
            else
            {
                //Create sound for saving to memory and assign it the loaded soundbuffer
                sf::Sound snd(sndbfr);
                //Set current volume, 100 at default
                snd.SetVolume(sVol);

                snd.Play();
                //Add to soundList
                soundList[soundKey] = snd;
                //Debug output
                std::cout << "Loaded sound \"" << soundKey << "\" with filepath \"" << soundPath << "\"" << std::endl;
            }
        }
    }

    void AudioHandler::saveMusic(std::string& musicKey, std::string& musicPath, std::string& output)
    {
        /*
            Purpose: Save file from loadAudio() as music.
        */
        //Search musicList
        if(musicList.find(musicKey) != musicList.end())
            std::cout << "Failed to load music \"" << musicPath << "\". Reason: Music key already in system" << std::endl;
        else
        {
            //Create music to assign from file
            sbe::Music msc;
            //Load music file
            if(!msc.OpenFromFile(musicPath))
                std::cout << "Failed to load music \"" << musicPath << "\". Reason: Unable to open music file" << std::endl;
            else
            {
                //Set current volume, 100 at default
                msc.SetVolume(mVol);
                //Add to musicList
                musicList.insert(std::pair<std::string, sbe::Music> (musicKey, msc));
                //String for quicker access
                curSong = musicKey;
                //Debug output
                std::cout << "Loaded music \"" << musicKey << "\" with filepath \"" << musicPath << "\"" << std::endl;
            }
        }
    }

    sf::Sound AudioHandler::getSound(const std::string& soundKey)
    {
        /*
            Purpose: Return a sound clip which can then be copied or played.
        */
        sf::Sound snd;

        if(soundList.find(soundKey) == soundList.end())
        {
            std::cout << "Failed to get sound \"" << soundKey << "\"." << std::endl;
            return snd;
        }
        else
            snd = soundList[soundKey];

        return snd;
    }

    void AudioHandler::setVolume(short v)
    {
        //Set master volume
        setSFXVol(v);
        setMusicVol(v);
    }

    void AudioHandler::setSFXVol(short s)
    {
        //Set SFX volume
        sVol = 100;

        soundMap::iterator it;

        if(!soundList.empty())
        {
            for(it = soundList.begin(); it != soundList.end(); it++)
                it->second.SetVolume(s);
        }
    }

    void AudioHandler::setMusicVol(short m)
    {
        //Set music volume
        mVol = 100;

        musicMap::iterator it;

        if(!musicList.empty())
        {
            for(it = musicList.begin(); it != musicList.end(); it++)
                it->second.SetVolume(m);
        }
    }

    bool AudioHandler::setMusic(const std::string& musicKey)
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
    }

    void AudioHandler::getAudioList()
    {
        for(soundMap::iterator it = soundList.begin(); it != soundList.end(); it++)
            std::cout << (*it).first << " " << std::endl;
        for(musicMap::iterator it = musicList.begin(); it != musicList.end(); it++)
            std::cout << (*it).first << " " << std::endl;

    }
}
