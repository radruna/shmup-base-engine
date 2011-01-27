/*
/ Base entity class
/ Authors: Felix Westin and Victor Rådmark
/ File created: 2010-12-07
/ File updated: 2010-12-24
/ License: GPLv3
*/
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"

namespace sbe
{
    class Entity : public sf::Sprite
    {
        /*
            Base entity class
        */
        public:
            Entity()
            {

            }
            Entity(const sf::Image& img);
            Entity(const std::string& imgStr, ImageHandler& iHandler);
            ~Entity();

            void setImage(const std::string& imgStr)
            {
                SetImage(imgHandler->getImage(imgStr));
            }

            virtual void update(const float& elapsed) =0; //Or onThink(), whatever.
            void SetAlpha(int alpha);
            int GetAlpha();
        protected:
            int z;
            ImageHandler* imgHandler;
    };
}

#endif
