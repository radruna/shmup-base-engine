/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-26
/ License: GPLv3
*/
#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>   //For strings
#include <list>     //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h" //For loading images
#include "filehandler.h" //Abstract base class
#include "particle.h" //Particle header

namespace sbe
{
    struct ValueMod
    {
        float scalarRate;       //Scalar modifier
        float oscFreq;          //Oscillation frequency
        float oscAmp;           //Oscillation amplitude
        float oscOffset;        //Oscillation offset
    };

    struct FadeMod
    {
        float fadeInMin;       //Fade in duration min
        float fadeInMax;       //Fade in duration max
        float fadeOutMin;      //Fade out duration min
        float fadeOutMax;      //Fade out duration max
    };


    class ParticleSystem : public FileHandler , public sf::Drawable
    {
        /*
            Particle system class
        */
        public:
            ParticleSystem(const std::string& particleSystemFile, ImageHandler* imgHandler);
            ~ParticleSystem()
            {
                remove();
            }

            //Remove particle system
            void remove();
            void SetPosition(int x, int y);
            void Move(int x, int y);
            void update(const float& elapsed);

        protected:
            void Render(sf::RenderTarget& Target) const;

        private:
            float boundsRand(float a, float b);
            int boundsRand(int a, int b);
            //Don't move these please
            int             xPos, yPos;
            float           counter;
            sf::Image       sprite;

            //Parameters
            std::string     name,                   //The particle system name
                            spriteName;             //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
            bool            rotRandom;              //Particle rotation randomization. Spawns the particles with random rotation
            int             emissionType,           //Particle system type. 1 = continuous, 2 = instant
                            emissionMax,            //Amount of particles to emit if type = 2
                            alphaMin,               //Initial alpha min. 0 = invisible, 255 = opaque.
                            alphaMax,               //Initial alpha max. 0 = invisible, 255 = opaque.
                            emissionAngleMin,       //Minimum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
                            emissionAngleMax;       //Maximum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
            float           sizeMin,                //Size min
                            sizeMax,                //Size max
                            lifeSpanMin,            //Lifespan min
                            lifeSpanMax,            //Lifespan max
                            emissionRate,           //Emission rate
                            emissionForceMin,       //Emission force min
                            emissionForceMax,       //Emission force max
                            emissionFriction,       //Emission friction
                            rotRateMin,             //Rotation speed min
                            rotRateMax,             //Rotation speed max
                            rotation;               //Particle rotation if not random
            ValueMod        sizeModifier,           //Size modifiers
                            alphaModifier;          //Alpha modifier
            FadeMod         fadeModifier;           //Fade parameters

            //Parameter list
            std::map<std::string, std::string> parameterList;   //TODO (Fewes#1#): PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT IN CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
            //Particle list
            std::list<Particle> particleList;
    };
}

#endif

