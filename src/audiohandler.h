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

#include <SFML/Graphics.hpp> //Sfml stuff

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

            //Load audio listed in the asset file
            void loadAudio(const std::string& soundFile);
            void loadMusic(const std::string& soundFile);
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
            void setVolume(short int& v = 100);
            //Set SFX volume
            void setSFXVol(short int& s = 100);
            //Set music volume
            void setMusicVol(short int& m = 100);
            //Set current music playing.
            bool setMusic(const string& strM);
            //Stop current music.
            void stopMusic();
            //Pause/play current music
            void pauseMusic();
            //Set music to loop
            void setMusicLoop();
        private:
            //Sound list
            std::map<std::string, sf::Sound> soundList;
            //Music list
            std::map<std::string, sf::Music> musicList;
    };
}


#endif AUDIOHANDLER_H_INCLUDED
