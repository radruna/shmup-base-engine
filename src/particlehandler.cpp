/*
/ Particle handler class
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

#include "particlehandler.h"   //Class def
#include "filehandler.h" //Base class

namespace sbe
{
    ParticleHandler::ParticleHandler()
    {
        //Load intro or menu stuff
    }

    //Remove all particles from world
    void ParticleHandler::destroyAll(){
        /* Remove all particles code */
    }

}
