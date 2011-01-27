/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-27
/ License: GPLv3
//TODO (Fewes#1#): Cut down on the debug output. Add more parameters. Add basic move/manipulation functions
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <string> //For strings
#include <cstring> //For strcpy
#include <list>     //For lists
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "particlesystem.h" //Class def
#include "imagehandler.h" //For loading images
#include "filehandler.h" //Base class
#include "particle.h" //Particle header

namespace sbe
{
    ParticleSystem::ParticleSystem(const std::string& particleSystemFile, ImageHandler* imgHandler)
    {
        std::cout << std::endl << "Loading particle system \"" << particleSystemFile << "\"..." << std::endl;

        //Open specified file
        fileReader.open(particleSystemFile.c_str());
        if(!fileReader)
        {
            //Debug output
            std::cout << "The particle handler was unable to open the specified particle system file" << std::endl;
            return;
        }

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
                else if(parameterKey == "size_mod_oscillate_freq")
                    sizeModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude")
                    sizeModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_offset")
                    sizeModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float

                //Movement parameters   move_mod_angle_min
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
                else if(parameterKey == "alpha_mod_oscillate_freq")
                    alphaModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "alpha_mod_oscillate_amplitude")
                    alphaModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "alpha_mod_oscillate_offset")
                    alphaModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float

                //Parameter not found
                else
                    std::cout << "Invalid particle system parameter: " << parameterKey << std::endl;
            }
        }
        //Debug output
        std::cout << "Finished loading particle system \"" << particleSystemFile << "\"" << std::endl;
        //Close file
        fileReader.close();
        sprite = imgHandler->getImage(spriteName);

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

    void ParticleSystem::SetPosition(int x, int y)  //Set particle system position
    {
        xPos = x;
        yPos = y;
    }

    void ParticleSystem::Move(int x, int y)         //Move particle system
    {
        xPos += x;
        yPos += y;
    }

    template<class T>
    T ParticleSystem::boundsRand(T min, T max)
    {
        if(min > max)           //Swap values if user = idiot
        {
            T temp = min;
            min = max;
            max = temp;
        }
        else if(min == max)     //If same = one value
                return min;
            else                //If different, value = random value between min and max
                return min + fmod(rand(), (max - min));

        return 0;
    }

    void ParticleSystem::update(const float& elapsed)
    {
        //Emit new particle
        if(counter > 1/emissionRate)
        {
            int prcPerFrame = counter / (1/emissionRate);   //Check how many particles should be emitted this frame.
            for(int i = 0;i< prcPerFrame;i++)   //Make sure that enough particles are emitted. This fixes the issue with particle systems being unable to emit faster than the framerate
            {
                //Spawn particle and assign appropriate values. A weird mix between constructor parameters and set functions

                //Get scale
                float scale             = boundsRand( sizeMin , sizeMax );
                //Get emission angle
                int emissionAngle       = boundsRand( emissionAngleMin , emissionAngleMax );
                //Get rotation rate (divide by 10 for a nicer value)
                float rotRate           = boundsRand( rotRateMin, rotRateMax ) / 10;
                //Get force
                float emissionForce     = boundsRand( emissionForceMin , emissionForceMax );
                //Get friction
                float emissionFriction  = boundsRand( emissionFrictionMin , emissionFrictionMin );
                //Get lifespan
                float lifeSpan          = boundsRand( lifeSpanMin , lifeSpanMax );
                //Get fade in duration
                float fadeInDur         = boundsRand( fadeModifier.fadeInMin, fadeModifier.fadeInMax );
                //Get fade out duration
                float fadeOutDur        = boundsRand( fadeModifier.fadeOutMin, fadeModifier.fadeOutMax );
                //Get alpha
                int alpha               = boundsRand( alphaMin, alphaMax );
                //Get scalar size mod rate
                float sizeModScalar     = boundsRand( sizeModifier.scalarRateMin, sizeModifier.scalarRateMax );
                //Get movement mod
                float movementModAngle  = boundsRand( movementAngleMin, movementAngleMax );

                particleList.push_back(Particle(
                                                sprite,
                                                emissionAngle,
                                                emissionForce,
                                                lifeSpan,
                                                alpha,
                                                fadeInDur,
                                                fadeOutDur,
                                                emissionFriction,
                                                sizeModScalar,
                                                movementModAngle,
                                                rotAlign
                                                )); //Add new particle to list
                particleList.back().SetPosition( xPos , yPos );     //Set start position of particle to the particle system's coordinates //TODO(Fewes#2#) Add offset functionality
                particleList.back().setRotRate( rotRate );      //Set rotation rate
                particleList.back().SetCenter( particleList.back().GetSize().x / 2 , particleList.back().GetSize().y / 2 );     //Set center of sprite to get correct rotation //TODO(Someone#3#) Move this to entity constructor and make center default?
                particleList.back().SetScale( scale , scale * sizeRatio );      //Set scale

                //Handle rotation
                if(rotAlign)    //Should I align to emission angle?
                    particleList.back().SetRotation( emissionAngle * -1 + rotation );   //If yes, then do so + rotation
                else if(rotRandom)  //Should I start out with random rotation?
                    particleList.back().SetRotation( rand() % 360 );
                else    //Just spawn with rotation
                    particleList.back().SetRotation( rotation );


                //std::cout<<"New particle emitted. Angle: "<<emitAngle<<" Force: "<<emissionForce<<std::endl;  //Debug

                counter = 0;        //Reset counter
            }
        }
        else
            counter += elapsed;     //Count time

        for(std::list<Particle>::iterator pIt = particleList.begin(); pIt != particleList.end(); pIt++)     //Iterate through particle list
        {
            if(pIt->getLife() < 0)      //Check if particle should die
                pIt = particleList.erase(pIt);  //Erase particle
            else
                pIt->update(elapsed);   //Update particle
        }
    }

}
