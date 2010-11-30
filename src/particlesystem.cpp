/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-22
/ License: GPLv3
//TODO (Fewes#1#): Cut down on the debug output. Add more parameters. Add basic move/manipulation functions
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "ParticleSystem.h"   //Class def
#include "filehandler.h" //Base class

namespace sbe
{
    ParticleSystem::ParticleSystem()
    {
    }

    //Load particle system. This does not work the same as the image or the audio handler as it stores parameters instead of objects
    void ParticleSystem::loadParticleSystem(const std::string& particleSystemFile)
    {
        std::cout << std::endl << "Loading particle \"" << particleSystemFile << "\"..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, particleSystemFile.c_str());
        //Open specified file
        fileReader.open(str);
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
                if(parameterKey == "sprite_name")
                    spriteName = parameterValue;
                if(parameterKey == "emission_type")
                    emissionType = atoi(parameterValue.c_str());//Convert string to int
                if(parameterKey == "emission_rate")
                    emissionRate = atof(parameterValue.c_str());//Convert string to float

                //Lifespan parameters
                if(parameterKey == "lifespan")
                    lifeSpan = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "lifespan_random")
                    lifeSpanRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool
                if(parameterKey == "lifespan_random_min")
                    lifeSpanRandomMin = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "lifespan_random_max")
                    lifeSpanRandomMax = atof(parameterValue.c_str());//Convert string to float

                //Size parameters
                if(parameterKey == "size")
                    size = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "size_random")
                    sizeRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool
                if(parameterKey == "size_random_min")
                    sizeRandomMin = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "size_random_max")
                    sizeRandomMax = atof(parameterValue.c_str());//Convert string to float

                //Rotation parameters
                if(parameterKey == "rotation_rate")
                    rotRate = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "rotation_random")
                    rotRandom = (bool) atoi(parameterValue.c_str());//Convert string to bool

                //Fade parameters
                if(parameterKey == "fade_in")
                    fadeModifier.fadeIn = (bool) atoi(parameterValue.c_str());//Convert string to bool
                if(parameterKey == "fade_out")
                    fadeModifier.fadeOut = (bool) atoi(parameterValue.c_str());//Convert string to bool
                if(parameterKey == "fade_in_time")
                    fadeModifier.fadeInTime = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "fade_out_time")
                    fadeModifier.fadeOutTime = atof(parameterValue.c_str());//Convert string to float

                if(parameterKey == "size_mod_scalar_rate")
                    sizeModifier.scalarRate = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "size_mod_oscillate_freq")
                    sizeModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "size_mod_oscillate_amplitude")
                    sizeModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "size_mod_oscillate_offset")
                    sizeModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float

                if(parameterKey == "alpha")
                    alpha = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "alpha_mod_scalar_rate")
                    alphaModifier.scalarRate = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "alpha_mod_oscillate_freq")
                    alphaModifier.oscFreq = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "alpha_mod_oscillate_amplitude")
                    alphaModifier.oscAmp = atof(parameterValue.c_str());//Convert string to float
                if(parameterKey == "alpha_mod_oscillate_offset")
                    alphaModifier.oscOffset = atof(parameterValue.c_str());//Convert string to float

            }
        }
        //Debug output
        std::cout << "Finished loading particle \"" << particleSystemFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    //Remove all particles from world
    void ParticleSystem::remove(){
        /* Particle remove code */
    }

}
