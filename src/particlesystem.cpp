/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-22
/ License: GPLv3
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
            //Check if line is empty
            if(output != "")
            {
                //Register new line
                lineVar++;
                //Replace tabs with spaces
                while(output.find('\t') != std::string::npos)
                {
                    tabPos = output.find('\t');
                    output.replace(tabPos,1," ");
                }

                //Find first space
                if(output.find(' ' ) == std::string::npos)
                        //If not found
                        std::cout << "Incorrect asset on line " << lineVar << " in file \"" << particleSystemFile << "\"" << std::endl;
                else
                {
                    //Find first space
                    spacePos = output.find (' ');
                    if(output.find("//") != std::string::npos)
                    {
                         //Find comment
                        commentPos = output.find("//");
                        //Cut comment
                        output = output.substr(0,commentPos);
                    }

                    //Set parameter
                    parameterKey = output.substr(0,spacePos);
                    //Search and remove any spaces
                    FileHandler::stringStripSpace(parameterKey);

                    //Set parameter value
                    parameterValue = output.substr(parameterKey.length(),output.length());
                    //Search and remove any spaces
                    FileHandler::stringStripSpace(parameterValue);

                    //Search particle parameter list
                    if(parameterList.find(parameterKey) != parameterList.end())
                        std::cout << "Failed to load image \"" << parameterValue << "\". Reason: Image key already in system" << std::endl;
                    else
                    {
                        //Add to parameterList
                        parameterList[parameterKey] = parameterValue;
                        //Debug output
                        std::cout << "Loaded particle \"" << parameterKey << "\" with filepath \"" << parameterValue << "\"" << std::endl;
                    }
                }
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