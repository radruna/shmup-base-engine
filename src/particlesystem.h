/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-22
/ License: GPLv3
*/
#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "filehandler.h" //Abstract base class

struct ValueMod
{
    float scalarRate;       //Scalar modifier
    float oscFreq;          //Oscillation frequency
    float oscAmp;           //Oscillation amplitude
    float oscOffset;        //Oscillation offset
};

struct FadeMod
{
    bool fadeIn;            //Should particles fade in?
    bool fadeOut;           //Should particles fade out?
    float fadeInTime;       //Time, in seconds, for particles to fade in
    float fadeOutTime;      //Time, in seconds, for particles to fade out
};

namespace sbe
{
    class ParticleSystem : public FileHandler
    {
        /*
            Particle system class
        */
        public:
            ParticleSystem();
            ~ParticleSystem()
            {
                remove();
            }

            //Remove particle system
            void remove();
            void loadParticleSystem(const std::string& particleSystemFile);
        private:
            //Parameters
            std::string     name;                   //The particle system name
            std::string     spriteName;             //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
            bool            sizeRandom;             //Particle size randomization
            bool            lifeSpanRandom;         //Particle size randomization
            bool            rotRandom;              //Particle rotation randomization
            int             emissionType;           //Particle system type
            int             alpha;                  //Initial alpha of particles emitted by particle system. 0 = invisible, 255 = opaque
            float           size;                   //Initial size of particles emitted by particle system. 1 = 1:1 sprite pixel to screen pixel ratio
            float           sizeRandomMin;          //If sizeRandom = 1, then this is set as the minimum value
            float           sizeRandomMax;          //If sizeRandom = 1, then this is set as the maximum value
            float           lifeSpan;               //Lifetime, in seconds
            float           lifeSpanRandomMin;      //If lifeSpanRandom = 1, then this is set as the minimum value
            float           lifeSpanRandomMax;      //If lifeSpanRandom = 1, then this is set as the maximum value
            float           emissionRate;           //Emission rate
            float           rotRate;                //Rotation speed
            ValueMod        sizeModifier;           //Size modifiers
            ValueMod        alphaModifier;          //Alpha modifier
            FadeMod         fadeModifier;           //Fade parameters

            //Parameter list
            std::map<std::string, std::string> parameterList;   //TODO (Fewes#1#): PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT IN CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
    };
}

#endif

