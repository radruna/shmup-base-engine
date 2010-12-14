/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-12-14
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
            std::string     name,                   //The particle system name
                            spriteName;             //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
            bool            sizeRandom,             //Particle size randomization
                            lifeSpanRandom,         //Particle lifetime randomization
                            rotRandom;              //Particle rotation randomization. Spawns the particles with random rotation
            int             emissionType,           //Particle system type
                            alpha,                  //Initial alpha of particles emitted by particle system. 0 = invisible, 255 = opaque. Manipulated alpha value should never go over this.
                            emissionAngleMin,       //Minimum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
                            emissionAngleMax;       //Maximum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
            float           size,                   //Initial size of particles emitted by particle system. 1 = 1:1 sprite pixel to screen pixel ratio
                            sizeRandomMin,          //If sizeRandom = 1, then this is set as the minimum value
                            sizeRandomMax,          //If sizeRandom = 1, then this is set as the maximum value
                            lifeSpan,               //Lifetime, in seconds
                            lifeSpanRandomMin,      //If lifeSpanRandom = 1, then this is set as the minimum value
                            lifeSpanRandomMax,      //If lifeSpanRandom = 1, then this is set as the maximum value
                            emissionRate,           //Emission rate
                            rotRate;                //Rotation speed
            ValueMod        sizeModifier,           //Size modifiers
                            alphaModifier;          //Alpha modifier
            FadeMod         fadeModifier;           //Fade parameters

            //Parameter list
            std::map<std::string, std::string> parameterList;   //TODO (Fewes#1#): PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT IN CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
    };
}

#endif

