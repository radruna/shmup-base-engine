/*
/ Particle system class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-22
/ License: GPLv3
*/
#ifndef PARTICLESYSTEM_H_INCLUDED
#define PARTICLESYSTEM_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "filehandler.h" //Abstract base class

namespace sbe
{
    class ParticleSystem : public FileHandler
    {
        /*
            Particle system class
        */
        public:
            ParticleSystem();
            ~ParticleSystem()
            {
                remove();
            }

            //Remove particle system
            void remove();
            void loadParticleSystem(const std::string& particleSystemFile);

            //Parameters should go here. There'll probably be a lot of them. Using a map for now
            //The particle system name
            std::string name;
            //ImageKey name of the sprite to be loaded. See imagehandler for further info on how this works
            std::string spriteName;
            //Initial size of particles emitted by particle system. 1 = 1:1 sprite pixel to screen pixel ratio
            int size;
        private:
            //Parameter list
            std::map<std::string, std::string> parameterList;   //PARAMETERS SHOULD NOT BE STORED IN A MAP, BUT CLASS VARIABLES. I left this in here so the program would compile oorrectly. Should be fixed ASAP
    };
}

#endif

