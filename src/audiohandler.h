/*
/ Audio handler class
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-17
/ License: GPLv3
*/
#ifndef AUDIOHANDLER_H_INCLUDED
#define AUDIOHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>

#include <SFML/Audio.hpp> //Audio header

#include "filehandler.h" //Abstract base class

namespace sbe
{
    class AudioHandler : public FileHandler
    {
        /*
            Handles audio (sounds and music), loading, storing it and returning it upon request.
        */
        public:
            AudioHandler();
            ~AudioHandler()
            {
                unloadAudio();
            }

            //Load audio listed in the asset files
            void loadSound(const std::string& soundFile);
            void loadMusic(const std::string& musicFile);
            //Loading function
            void loadAudio(const std::string& soundFile, LoadType load);
            //Saving functions
            void saveSound(const std::string& soundKey, const std::string& soundPath, const std::string& output)
            void saveMusic(const std::string& musicKey, const std::string& musicPath, const std::string& output)
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
            sf::Sound getSound(const std::string& soundKey);
            //Set master volume
            void setVolume(short& v = 100);
            //Set SFX volume
            void setSFXVol(short& s = 100);
            //Set music volume
            void setMusicVol(short& m = 100);
            //Set current music playing.
            bool setMusic(const std::string& strM);
            //Stop current music.
            void stopMusic();
            //Pause/play current music
            void pauseMusic();
            //Set music to loop
            void setMusicLoop();

            enum LoadType
            {
                Sound,
                Music
            };

        private:
            //Sound list
            std::map<std::string, sf::Sound> soundList;
            //Music list
            std::map<std::string, sf::Music> musicList;
    };
}


#endif
