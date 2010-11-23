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

        int tabPos;
        int spacePos;
        int commentPos;
        int lineVar = 0;
        std::string output;
        std::string parameterKey;
        std::string parameterValue;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty and perform string operation
            if(output != "" && strReadLine(output,parameterKey,parameterValue) != -1)
            {
                //Assign parameter value based on the type of parameter. There's no fancier way than just looping through all possible cases so DEAL WITH IT
                if(parameterKey == "name")
                    name = parameterValue;
                if(parameterKey == "sprite")
                    spriteName = parameterValue;
                if(parameterKey == "size")
                    size = atoi(parameterValue.c_str());    //Convert string to int

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
