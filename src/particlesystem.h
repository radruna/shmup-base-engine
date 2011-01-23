/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-04
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
        bool fadeIn;            //Should particles fade in?
        bool fadeOut;           //Should particles fade out?
        float fadeInTime;       //Time, in seconds, for particles to fade in
        float fadeOutTime;      //Time, in seconds, for particles to fade out
    };


    class ParticleSystem : public FileHandler , public sf::Drawable
    {
        /*
            Particle system class
        */
        public:
            ParticleSystem(const std::string& particleSystemFile, ImageHandler& imgHandler);
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
            virtual void Render(sf::RenderTarget& Target) const;

        private:
            std::list<Particle> particleList;       //Particle list
            //Don't move these please
            int             xPos, yPos;
            float           counter;
            sf::Image       sprite;

            //Parameters
            std::string     name,                   //The particle system name
                            spriteName;             //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
            bool            sizeRandom,             //Particle size randomization
                            lifeSpanRandom,         //Particle lifetime randomization
                            rotRandom;              //Particle rotation randomization. Spawns the particles with random rotation
            int             emissionType,           //Particle system type. 1 = continuous, 2 = instant
                            emissionMax,            //Amount of particles to emit if type = 2
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
                            emissionForce,          //Emission force
                            emissionFriction,       //Emission friction
                            rotRate;                //Rotation speed
            ValueMod        sizeModifier,           //Size modifiers
                            alphaModifier;          //Alpha modifier
            FadeMod         fadeModifier;           //Fade parameters

            //Parameter list
            std::map<std::string, std::string> parameterList;   //TODO (Fewes#1#): PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT IN CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
    };
}

#endif

