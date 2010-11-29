/*
/ Copyable music
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-29
/ License: GPLv3
*/
#ifndef MUSIC_H_INCLUDED
#define MUSIC_H_INCLUDED

#include <SFML/Audio.hpp>

namespace sbe
{
    /*namespace priv
    {
        class SoundFile;
    }*/
    /*
        Copyable music class, derived from sf::Music and overriding NonCopyable with the second constructor.
    */
    class Music : sf::Music
    {
        public:
            Music();
            //Override NonCopyable
            Music(const Music& rhs) {}

            //Reimplement stuff
            bool OpenFromFile(const std::string& Filename);
            inline void SetVolume(float Volume)
            {
                sf::Music::SetVolume(Volume);
            }
            inline void Play()
            {
                sf::Music::Play();
            }
            inline sf::Sound::Status GetStatus() const
            {
                return sf::SoundStream::GetStatus();
            }
            inline void Stop()
            {
                sf::SoundStream::Stop();
            }
            inline void Pause()
            {
                sf::SoundStream::Pause();
            }
            inline void SetLoop(bool Loop)
            {
                sf::SoundStream::SetLoop(Loop);
            }
            inline void Initialize(unsigned int ChannelsCount, unsigned int SampleRate)
            {
                sf::Music::Initialize(ChannelsCount, SampleRate);
            }

            /*void Disconnect(sf::ResourcePtr<sbe::Music&> hurr) const
            {

            }*/
            //Awww yeah OPERATORS - NOT WORKING
            //Music& operator = (const Music& other);
        private:
            //priv::SoundFile*   myFile;
            //sf::ResourcePtr<Music> myBuffer;
    };
}

#endif
