/*
/ Particle handler class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-22
/ License: GPLv3
*/
#ifndef PARTICLEHANDLER_H_INCLUDED
#define PARTICLEHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "filehandler.h" //Abstract base class

namespace sbe
{
    class ParticleHandler : public FileHandler
    {
        /*
            Handles particle systems
        */
        public:
            ParticleHandler();
            ~ParticleHandler()
            {
                destroyAll();
            }

            //Remove all particles from world
            void destroyAll();
        private:
    };
}

#endif

