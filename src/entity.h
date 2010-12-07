/*
/ Base entity class
/ Author: Felix Westin
/ File created: 2010-12-07
/ File updated: 2010-12-07
/ License: GPLv3
*/
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <fstream>   //Read script files
#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

namespace sbe
{
    class Entity : public sf::Sprite
    {
        /*
            Base entity class
        */
        public:
            Entity();
            virtual void onThink() =0;
        private:
            int z;
    };
}

#endif
