/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-12-22
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

            AudioHandler(const int& s = 100, const int& m = 100);
            ~AudioHandler()
            {
                unloadAudio();
            }

            //Load audio listed in the asset files
            void loadSound(const std::string& soundFile);
            void loadMusic(const std::string& musicFile);
            //Loading function
            void loadAudio(const std::string& audioFile, const LoadType& load);
            //Saving functions
            void saveSound(const std::string& soundKey,  const std::string& soundPath);
            void saveMusic(const std::string& musicKey,  const std::string& musicPath);
            //Unload all sound
            inline void unloadSound()
            {
                soundList.clear();
            }
            inline void unloadMusic()
            {
                musicList.clear();
            }
            inline void unloadAudio()
            {
                unloadSound();
                unloadMusic();
            }
            //Get sound
            sf::SoundBuffer& getSound(const std::string& soundKey);
            //Get music path
            inline std::string getMusic(const std::string& musicKey)
            {
                return musicList[musicKey];
            }
            //Set master volume
            void setVolume(const short& v = 100);
            //Set SFX volume
            void setSFXVol(const short& s = 100);
            //Set music volume
            void setMusicVol(const short& m = 100);
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
