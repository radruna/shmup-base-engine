/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-25
/ License: GPLv3
*/
#ifndef AUDIOHANDLER_H_INCLUDED
#define AUDIOHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Audio.hpp> //Audio header

#include "filehandler.h" //Abstract base class
#include "music.h" //Copyable music

typedef std::map<std::string, sf::SoundBuffer> soundMap;
typedef std::map<std::string, std::string> musicMap;

namespace sbe
{
    class AudioHandler : public FileHandler
    {
        /*
            Handles audio (sounds and music), loading, storing it and returning it upon request.
        */
        public:
            enum LoadType
            {
                Sound,
                Music
            };

            AudioHandler(int s = 100, int m = 100);
            ~AudioHandler()
            {
                unloadAudio();
            }

            //Load audio listed in the asset files
            void loadSound(const std::string& soundFile);
            void loadMusic(const std::string& musicFile);
            //Loading function
            void loadAudio(const std::string& audioFile, LoadType load);
            //Saving functions
            void saveSound( std::string& soundKey,  std::string& soundPath,  std::string& output);
            void saveMusic( std::string& musicKey,  std::string& musicPath,  std::string& output);
            //Unload all sound
            void unloadSound()
            {
                soundList.clear();
            }
            void unloadMusic()
            {
                musicList.clear();
            }
            void unloadAudio()
            {
                unloadSound();
                unloadMusic();
            }
            //Get sound
            sf::SoundBuffer getSound(const std::string& soundKey);
            //Get music path
            std::string getMusic(const std::string& musicKey)
            {
                return musicList[musicKey];
            }
            //Set master volume
            void setVolume(short v = 100);
            //Set SFX volume
            void setSFXVol(short s = 100);
            //Set music volume
            void setMusicVol(short m = 100);
            /*//Set current music playing.
            bool setMusic(const std::string& strM);
            //Stop current music.
            void stopMusic();
            //Pause/play current music
            void pauseMusic();
            //Set music to loop
            void setMusicLoop(bool loop);*/
            void getAudioList();

        private:
            //Sound list
            soundMap soundList;
            //Music list
            musicMap musicList;

            int sVol,
                mVol;
            //std::string curSong;
    };
}


#endif
