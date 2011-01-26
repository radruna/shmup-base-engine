/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2011-01-26
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
                //Assign parameter value based on the type of parameter. There's no fancier way than just looping through all possible cases so DEAL WITH IT
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
                else if(parameterKey == "emission_friction")
                    emissionFriction = atof(parameterValue.c_str());//Convert string to float

                //Lifespan parameters
                else if(parameterKey == "lifespan_min")
                    lifeSpanMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "lifespan_max")
                    lifeSpanMax = atof(parameterValue.c_str());//Convert string to float

                //Size parameters
                else if(parameterKey == "size")
                    size = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_random")
                    sizeRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool
                else if(parameterKey == "size_random_min")
                    sizeRandomMin = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_random_max")
                    sizeRandomMax = atof(parameterValue.c_str());//Convert string to float

                //Rotation parameters
                else if(parameterKey == "rotation_rate")
                    rotRate = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "rotation_random")
                    rotRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool

                //Fade parameters
                else if(parameterKey == "fade_in_duration")
                    fadeModifier.fadeInDuration = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "fade_out_duration")
                    fadeModifier.fadeOutDuration = atof(parameterValue.c_str());//Convert string to float

                //Size modification parameters
                else if(parameterKey == "size_mod_scalar_rate")
                    sizeModifier.scalarRate = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_freq")
                    sizeModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_amplitude")
                    sizeModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "size_mod_oscillate_offset")
                    sizeModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float

                //Alpha parameters
                else if(parameterKey == "alpha")
                    alpha = atoi(parameterValue.c_str());//Convert string to float
                else if(parameterKey == "alpha_mod_scalar_rate")
                    alphaModifier.scalarRate = atof(parameterValue.c_str());//Convert string to float
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
        std::cout << "Finished loading particle \"" << particleSystemFile << "\"" << std::endl;
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

    void ParticleSystem::SetPosition(int x, int y)
    {
        xPos = x;
        yPos = y;
    }

    void ParticleSystem::Move(int x, int y)
    {
        xPos += x;
        yPos += y;
    }

    float ParticleSystem::boundsRand(float min, float max)
    {
        if(min == max)    //If same = one value
            {
                return min;
            }else   //If different, value = random value between min and max
            {
                return min + fmod(rand(), (max - min));
            }
    }

    int ParticleSystem::boundsRand(int min, int max)
    {
        if(min == max)    //If same = one value
            {
                return min;
            }else   //If different, value = random value between min and max
            {
                return min + rand() % (max - min);
            }
    }

    void ParticleSystem::update(const float& elapsed)
    {
        //Emit new particle
        if(counter > 1/emissionRate)
        {

            int emitAngle           = boundsRand(emissionAngleMin, emissionAngleMax); //Generate angle
            float emissionForce     = boundsRand(emissionForceMin, emissionForceMax); //Generate force
            float lifeSpan          = boundsRand(lifeSpanMin, lifeSpanMax); //Generate lifespan

            particleList.push_back(Particle(sprite, emitAngle - 90, emissionForce, lifeSpan)); //Add new particle to list
            particleList.back().SetPosition(xPos, yPos);
            std::cout<<"New particle emitted. Angle: "<<emitAngle<<" Force: "<<emissionForce<<std::endl;

            counter = 0;
            //TODO(Liag#2#) Add removal calculation (when out of bounds, etc)
        }
        else
        {
            counter += elapsed;
        }

        for(std::list<Particle>::iterator pIt = particleList.begin(); pIt != particleList.end(); pIt++)
        {
            if(pIt->getLife() < 0)
            {
                pIt = particleList.erase(pIt);
                //particleList.erase(pIt);
                std::cout<<"Particle died! =("<<std::endl;
            }
            else
            {
                pIt->update(elapsed);
            }
        }
    }

}
