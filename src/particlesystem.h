/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-27
/ License: GPLv3
*/
#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <fstream> //Read script files
#include <map> //Map for objects
#include <string> //For strings
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h" //For loading images
#include "filehandler.h" //Abstract base class
#include "particle.h" //Particle header


namespace sbe
{
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

            std::ifstream fileReader2;
            ImageHandler *imageHandler;
            std::string scriptFile;
            std::string fileContents;
            std::string fileMd5;
            std::string fileMd5Old;
            int md5Counter;
            bool firstRun;
            void reload();
            ParticleSystem *pSystemChild1;
            ParticleSystem *pSystemChild2;
            ParticleSystem *pSystemChild3;
            ParticleSystem *pSystemChild4;

            struct ValueMod
            {
                float   scalarRateMin, //Scalar modifier min
                        scalarRateMax, //Scalar modifier max
                        scalarRateOffset, //Scalar modifier offset
                        oscFreqMin, //Oscillation frequency min
                        oscFreqMax, //Oscillation frequency max
                        oscAmpMin, //Oscillation amplitude
                        oscAmpMax, //Oscillation amplitude
                        oscAmpOffset; //Oscillation amplitude offset
            };

            struct FadeMod
            {
                float   fadeInMin, //Fade in duration min
                        fadeInMax, //Fade in duration max
                        fadeOutMin, //Fade out duration min
                        fadeOutMax; //Fade out duration max
            };

            template<class T>
            T boundsRand(T a, T b);
            //Don't move these please
            int xPos, yPos;
            float           counter,
                            age,
                            emissionAngle;
            sf::Image sprite;

            //Parameters
            std::string     name,                   //The particle system name
                            spriteName,             //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
                            child1,                 //Child's name (another particle system)
                            child2,
                            child3,
                            child4;
            bool            rotRandom,              //Particle rotation randomization. Spawns the particles with random rotation. Is overridden by rotation alignment
                            rotAlign,               //Align rotation to emission angle. Use rotation parameter to adjust. Overrides random rotation
                            internalOsc;            //Controls how parameter values oscillate. 1 = particles use their internal clock, 0 = particles use particle system's global clock.
            int             emissionType,           //Particle system type. 1 = continuous, 2 = instant
                            emissionMax,            //Amount of particles to emit if type = 2
                            alphaMin,               //Initial alpha min. 0 = invisible, 255 = opaque.
                            alphaMax,               //Initial alpha max. 0 = invisible, 255 = opaque.
                            emissionAngleMin,       //Minimum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
                            emissionAngleMax;       //Maximum angle at which particles are emitted. 0 = straight upwards, 180 = straight downwards
            float           sizeMin,                //Size min
                            sizeMax,                //Size max
                            sizeRatio,              //Size ratio
                            lifeSpanMin,            //Lifespan min
                            lifeSpanMax,            //Lifespan max
                            emissionRate,           //Emission rate
                            emissionForceMin,       //Emission force min
                            emissionForceMax,       //Emission force max
                            emissionFrictionMin,    //Emission friction min
                            emissionFrictionMax,    //Emission friction max
                            rotRateMin,             //Rotation speed min
                            rotRateMax,             //Rotation speed max
                            rotation,               //Particle rotation if not random
                            movementAngleMin,
                            movementAngleMax;
            ValueMod        sizeModifier,           //Size modifiers
                            emissionAngleModifier,  //Emission angle modifier
                            alphaModifier;          //Alpha modifier
            FadeMod         fadeModifier;           //Fade parameters
            Particle::DiffColor         colorInitial,
                                        colorModified;
            Particle::ColModData        colorModData;

            //Parameter list
            //std::map<std::string, std::string> parameterList; //TODO (Fewes#1#): PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT IN CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
            //Particle list
            std::list<Particle> particleList;
    };
}

#endif
