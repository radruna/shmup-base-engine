/*
/ Copyable music
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-18
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
            void SetVolume(float Volume)
            {
                sf::Music::SetVolume(Volume);
            }
            void Play()
            {
                sf::Music::Play();
            }
            sf::Sound::Status GetStatus() const
            {
                return sf::SoundStream::GetStatus();
            }
            void Stop()
            {
                sf::SoundStream::Stop();
            }
            void Pause()
            {
                sf::SoundStream::Pause();
            }
            void SetLoop(bool Loop)
            {
                sf::SoundStream::SetLoop(Loop);
            }
            void Initialize(unsigned int ChannelsCount, unsigned int SampleRate)
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
