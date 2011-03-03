/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-27
/ License: GPLv3
*/
#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED

#include <fstream> //Read script files
#include <map> //Map for objects
#include <string> //For strings
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Abstract base class
#include "../graphics/imagehandler.h" //For loading images
#include "projectile.h" //Projectile header

namespace sbe
{
    class Weapon : public FileHandler , public sf::Drawable
    {
        /*
        Particle system class
        */
        public:
            Weapon(const std::string& weaponFile, ImageHandler* imgHandler);
            ~Weapon()
            {
            }

            void SetPosition(float x, float y);
            float GetPositionX();
            float GetPositionY();
            void Move(float x, float y);
            void update(const float& elapsed);
            void clear();
            void load();
            void fire();

        protected:
            void Render(sf::RenderTarget& Target) const;

        private:
            ImageHandler *imageHandler;
            std::string scriptFile;
            std::string pSystem1,
                        pSystem2,
                        pSystem3,
                        pSystem4;

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
                        fadeInOffsetMin, //Fade in offset min
                        fadeInOffsetMax, //Fade in offset max
                        fadeOutMin, //Fade out duration min
                        fadeOutMax; //Fade out duration max
            };

            template<class T>
            T boundsRand(T a, T b);
            //Don't move these please
            float xPos, yPos;
            float xPosOld, yPosOld;
            float           counter,
                            age,
                            emissionAngle,
                            reloadInterval,
                            firingInterval;

            bool            firing,
                            randEmissionAngle;

            int             shotsPerWave,
                            wavesPerAttack,
                            wavesLeft;

            float           waveInterval;

            sf::Image sprite;

            //Parameters
            std::string     name,                   //The particle system name
                            spriteName;
            bool            rotRandom,              //Particle rotation randomization. Spawns the particles with random rotation. Is overridden by rotation alignment
                            rotAlign,               //Align rotation to emission angle. Use rotation parameter to adjust. Overrides random rotation
                            internalOsc;            //Controls how parameter values oscillate. 1 = particles use their internal clock, 0 = particles use particle system's global clock.
            int             alphaMin,               //Initial alpha min. 0 = invisible, 255 = opaque.
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

            //Projectile list
            std::list<Projectile> projectileList;
    };
}

#endif
