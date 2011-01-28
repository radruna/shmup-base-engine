/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-28
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream> //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list> //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "particlesystem.h" //Class def
#include "imagehandler.h" //For loading images
#include "filehandler.h" //Base class
#include "particle.h" //Particle header
#include "logger.h" //Outputs debug in console and log

namespace sbe
{
    ParticleSystem::ParticleSystem(const std::string& particleSystemFile, ImageHandler* imgHandler)
    {
        Logger::writeMsg(1) << "\nLoading particle system \"" << particleSystemFile << "\"...";

        //Open specified file
        fileReader.open(particleSystemFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The particle handler was unable to open the specified particle system file";
            return;
        }

        //Set default values

        name = "none";
        spriteName = "default_particle";

        emissionType = 1;
        emissionMax = 100;
        emissionRate = 1;
        emissionAngleMin = 0;
        emissionAngleMax = 0;
        emissionForceMin = 0;
        emissionForceMax = 0;
        emissionFrictionMin = 1;
        emissionFrictionMax = 1;

        lifeSpanMin = 1;
        lifeSpanMax = 1;

        sizeMin = 1;
        sizeMax = 1;
        sizeRatio = 1;

        rotRateMin = 0;
        rotRateMax = 0;
        rotRandom = 0;
        rotAlign = 0;
        rotation = 0;

        fadeModifier.fadeInMin = 0;
        fadeModifier.fadeInMax = 0;
        fadeModifier.fadeOutMin = 0;
        fadeModifier.fadeOutMax = 0;

        sizeModifier.scalarRateMin = 1;
        sizeModifier.scalarRateMax = 1;
        sizeModifier.oscFreqMin = 0;
        sizeModifier.oscFreqMax = 0;
        sizeModifier.oscAmpMin = 0;
        sizeModifier.oscAmpMax = 0;
        sizeModifier.oscAmpOffset = 0;

        emissionAngleModifier.scalarRateMin = 0;
        emissionAngleModifier.scalarRateMax = 0;
        emissionAngleModifier.oscFreqMin = 0;
        emissionAngleModifier.oscFreqMax = 0;
        emissionAngleModifier.oscAmpMin = 0;
        emissionAngleModifier.oscAmpMax = 0;
        emissionAngleModifier.oscAmpOffset = 0;

        movementAngleMin = 0;
        movementAngleMax = 0;

        alphaMin = 255;
        alphaMax = 255;
        alphaModifier.scalarRateMin = 0;
        alphaModifier.scalarRateMax = 0;

        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation
            if(strReadLine(output,parameterKey,parameterValue))
            {
                //Assign parameter value based on the type of parameter.
                //Generic parameters
                if(parameterKey == "name")
                    name = parameterValue;
                else if(parameterKey == "sprite_name")
                    spriteName = parameterValue;
                else if(parameterKey == "internal_oscillation")
                    internalOsc = (bool) atoi(parameterValue.c_str());//Convert string to bool

                //Emission parameters
                else if(parameterKey == "emission_type")
                    emissionType = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_max")
                    emissionMax = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_rate")
                    emissionRate = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_min")
                    emissionAngleMin = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_angle_max")
                    emissionAngleMax = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "emission_force_min")
                    emissionForceMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_force_max")
                    emissionForceMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_friction_min")
                    emissionFrictionMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_friction_max")
                    emissionFrictionMax = atof(parameterValue.c_str());//Convert string to float

                //Lifespan parameters
                else if(parameterKey == "lifespan_min")
                    lifeSpanMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "lifespan_max")
                    lifeSpanMax = atof(parameterValue.c_str());//Convert string to float

                //Size parameters
                else if(parameterKey == "size_min")
                    sizeMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_max")
                    sizeMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_ratio")
                    sizeRatio = atof(parameterValue.c_str());//Convert string to float

                //Rotation parameters
                else if(parameterKey == "rotation_rate_min")
                    rotRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "rotation_rate_max")
                    rotRateMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "rotation_random")
                    rotRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool
                else if(parameterKey == "rotation_align")
                    rotAlign = (bool) atoi(parameterValue.c_str());//Convert string to bool
                else if(parameterKey == "rotation")
                    rotation = atof(parameterValue.c_str());//Convert string to float

                //Fade parameters
                else if(parameterKey == "fade_in_min")
                    fadeModifier.fadeInMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_in_max")
                    fadeModifier.fadeInMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_out_min")
                    fadeModifier.fadeOutMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_out_max")
                    fadeModifier.fadeOutMax = atof(parameterValue.c_str());//Convert string to float

                //Size modification parameters
                else if(parameterKey == "size_mod_scalar_rate_min")
                    sizeModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_scalar_rate_max")
                    sizeModifier.scalarRateMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_freq_min")
                    sizeModifier.oscFreqMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_freq_max")
                    sizeModifier.oscFreqMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_min")
                    sizeModifier.oscAmpMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_max")
                    sizeModifier.oscAmpMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude_offset")
                    sizeModifier.oscAmpOffset = atof(parameterValue.c_str());//Convert string to float

                //Emission angle modification parameters
                else if(parameterKey == "emission_angle_mod_scalar_rate_min")
                    emissionAngleModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_scalar_rate_max")
                    emissionAngleModifier.scalarRateMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_freq_min")
                    emissionAngleModifier.oscFreqMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_freq_max")
                    emissionAngleModifier.oscFreqMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_min")
                    emissionAngleModifier.oscAmpMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_max")
                    emissionAngleModifier.oscAmpMax = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "emission_angle_mod_oscillate_amplitude_offset")
                    emissionAngleModifier.oscAmpOffset = atof(parameterValue.c_str());//Convert string to float

                //Movement parameters move_mod_angle_min
                else if(parameterKey == "move_mod_angle_min")
                    movementAngleMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "move_mod_angle_max")
                    movementAngleMax = atof(parameterValue.c_str());//Convert string to float

                //Alpha parameters
                else if(parameterKey == "alpha_min")
                    alphaMin = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "alpha_max")
                    alphaMax = atoi(parameterValue.c_str());//Convert string to int
                else if(parameterKey == "alpha_mod_scalar_rate_min")
                    alphaModifier.scalarRateMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "alpha_mod_scalar_rate_max")
                    alphaModifier.scalarRateMax = atof(parameterValue.c_str());//Convert string to float

                /*
else if(parameterKey == "alpha_mod_oscillate_freq")
alphaModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
else if(parameterKey == "alpha_mod_oscillate_amplitude")
alphaModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
else if(parameterKey == "alpha_mod_oscillate_offset")
alphaModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float
*/

                //Parameter not found
                else
                    Logger::writeMsg(1) << "Invalid particle system parameter: " << parameterKey;
            }
        }

        //No name parameter found in script file
        if(name == "none" || name == "")
        {
            Logger::writeMsg(1) << "Particle system needs a name!";
        }

        //Set sprite to default particle if spriteName = empty
        if(spriteName == "")
            spriteName = "default_particle";

        //Debug output
        Logger::writeMsg(1) << "Finished loading particle system \"" << particleSystemFile << "\"";
        //Close file
        fileReader.close();
        sprite = imgHandler->getImage(spriteName);

        age = 0;
        counter = 0;

        srand(time(NULL));
    }

    void ParticleSystem::Render(sf::RenderTarget& Target) const
    {
        for(std::list<Particle>::const_iterator it = particleList.begin(); it != particleList.end(); it++)
        {
            Target.Draw(*it);
        }
    }

    //Remove all particles from system
    void ParticleSystem::remove()
    {
        particleList.clear();
    }

    void ParticleSystem::SetPosition(int x, int y) //Set particle system position
    {
        xPos = x;
        yPos = y;
    }

    void ParticleSystem::Move(int x, int y) //Move particle system
    {
        xPos += x;
        yPos += y;
    }

    template<class T>
    T ParticleSystem::boundsRand(T min, T max)
    {
        if(min > max) //Swap values if user = idiot
        {
            T temp = min;
            min = max;
            max = temp;
        }
        else if(min == max) //If same = one value
                return min;
            else //If different, value = random value between min and max
                return min + fmod(rand(), (max - min));

        return 0;
    }

    void ParticleSystem::update(const float& elapsed)
    {

        //Increase age
        age += elapsed;
        //Emit new particle
        if(counter > 1/emissionRate)
        {

            int prcPerFrame = counter / (1/emissionRate); //Check how many particles should be emitted this frame.
            for(int i = 0;i< prcPerFrame;i++) //Make sure that enough particles are emitted. This fixes the issue with particle systems being unable to emit faster than the framerate
            {

                if(emissionMax > 0 || emissionType != 2) //Check emission type and how many particles remain if type = 2
                {

                    //Spawn particle and assign appropriate values.

                    ParaMod sizeMod;
                    ParaMod emissionAngleMod;

                    //Get scale
                    float scale = boundsRand( sizeMin , sizeMax );
                    //Get rotation rate (divide by 10 for a nicer value)
                    float rotRate = boundsRand( rotRateMin, rotRateMax ) / 10;
                    //Get force
                    float emissionForce = boundsRand( emissionForceMin , emissionForceMax );
                    //Get friction
                    float emissionFriction = boundsRand( emissionFrictionMin , emissionFrictionMin );
                    //Get lifespan
                    float lifeSpan = boundsRand( lifeSpanMin , lifeSpanMax );
                    //Get fade in duration
                    float fadeInDur = boundsRand( fadeModifier.fadeInMin, fadeModifier.fadeInMax );
                    //Get fade out duration
                    float fadeOutDur = boundsRand( fadeModifier.fadeOutMin, fadeModifier.fadeOutMax );
                    //Get alpha
                    int alpha = boundsRand( alphaMin, alphaMax );

                    //Get scalar size mod rate
                    sizeMod.scalarRate = boundsRand( sizeModifier.scalarRateMin, sizeModifier.scalarRateMax );
                    //Get oscillating size mod frequency
                    sizeMod.frequency = boundsRand( sizeModifier.oscFreqMin, sizeModifier.oscFreqMax );
                    //Get oscillating size mod amplitude
                    sizeMod.amplitude = boundsRand( sizeModifier.oscAmpMin, sizeModifier.oscAmpMin );
                    //Get oscillating size mod offset
                    sizeMod.amplitudeOffset = sizeModifier.oscAmpOffset;

                    //Get scalar emission angle mod rate
                    emissionAngleMod.scalarRate = boundsRand( emissionAngleModifier.scalarRateMin, emissionAngleModifier.scalarRateMax );
                    //Get oscillating emission angle mod frequency
                    emissionAngleMod.frequency = boundsRand( emissionAngleModifier.oscFreqMin, emissionAngleModifier.oscFreqMax );
                    //Get oscillating emission angle mod amplitude
                    emissionAngleMod.amplitude = boundsRand( emissionAngleModifier.oscAmpMin, emissionAngleModifier.oscAmpMin );
                    //Get oscillating emission angle mod offset
                    emissionAngleMod.amplitudeOffset = emissionAngleModifier.oscAmpOffset;

                    //Get emission angle
                    float emissionAngle;
                    if(emissionAngleMod.frequency != 0)
                        emissionAngle = boundsRand( emissionAngleMin , emissionAngleMax ) + emissionAngleMod.amplitude * sin(age * emissionAngleMod.frequency) + emissionAngleMod.amplitudeOffset;
                    else
                        emissionAngle = boundsRand( emissionAngleMin , emissionAngleMax );

                    //Get movement mod
                    float movementModAngle = boundsRand( movementAngleMin, movementAngleMax );

                    particleList.push_back(Particle(
                                                    sprite, //Sprite to use
                                                    scale, //Width
                                                    scale * sizeRatio, //Height
                                                    emissionAngle,
                                                    emissionForce,
                                                    lifeSpan,
                                                    alpha,
                                                    fadeInDur,
                                                    fadeOutDur,
                                                    emissionFriction,
                                                    sizeMod, //Size modification data
                                                    movementModAngle,
                                                    age,
                                                    rotAlign,
                                                    internalOsc
                                                    )); //Add new particle to list
                    particleList.back().SetPosition( xPos , yPos ); //Set start position of particle to the particle system's coordinates //TODO(Fewes#2#) Add offset functionality
                    particleList.back().setRotRate( rotRate ); //Set rotation rate

                    //Handle rotation
                    if(rotAlign) //Should I align to emission angle?
                        particleList.back().SetRotation( emissionAngle * -1 + rotation ); //If yes, then do so + rotation
                    else if(rotRandom) //Should I start out with random rotation?
                        particleList.back().SetRotation( rand() % 360 );
                    else //Just spawn with rotation
                        particleList.back().SetRotation( rotation );


                    //Logger::writeMsg(1) << "New particle emitted. Angle: "<<emitAngle<<" Force: "<<emissionForce; //Debug

                    counter = 0; //Reset counter

                    if(emissionType == 2) //Particles remaining -1 if type = 2
                        emissionMax--;
                }
            }
        }
        else
            counter += elapsed; //Count time

        for(std::list<Particle>::iterator pIt = particleList.begin(); pIt != particleList.end(); pIt++) //Iterate through particle list
        {
            if(pIt->getLife() < 0) //Check if particle should die
                pIt = particleList.erase(pIt); //Erase particle
            else
                pIt->update(elapsed); //Update particle
        }
    }

}
