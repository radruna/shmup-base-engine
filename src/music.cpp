/*
/ Copyable music in SFML
/ Author: Victor Rådmark
/ File created: 2010-11-17
/ File updated: 2010-11-18
/ License: GPLv3
*/
#include <iostream>

#include <SFML/Audio.hpp>

#include "music.h"

namespace sbe
{
    Music::Music()
        :   //myFile(NULL),
            myDuration(0.f)
    {
        sf::Music();
    }

    bool Music::OpenFromFile(const std::string& Filename)
    {
        /*
            Purpose: Open from file, since it calls some silly initialize function it needs to be reimplemented
        */
        sf::Music::OpenFromFile(Filename);

        //Initialize the stream
        sf::Music::Initialize(2, 44800);

        return true;
    }

    /*Music& Music::operator = (const Music& other)
    {

            Purpose: = operator, to copy the fucker over. Partly based on the Sound operator by Laurent Gomilla.

        //Detach the music instance from the previous buffer (if any)
        if(myBuffer)
        {
            Stop();
            myBuffer->DetachSound(this);
            myBuffer = NULL;
        }

        //Copy the music attributes
        if(other.myBuffer)
            SetBuffer(*other.myBuffer);

        SetLoop(other.GetLoop());
        SetPitch(Other.GetPitch());
        SetVolume(Other.GetVolume());
        SetPosition(Other.GetPosition())
        SetRelativeToListener(Other.IsRelativeToListener());
        SetMinDistance(Other.GetMinDistance());
        SetAttenuation(Other.GetAttenuation());

        return *this;
    }*/
}
