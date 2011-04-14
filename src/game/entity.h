/*
/ Base entity class
/ Authors: Felix Westin and Victor Rådmark
/ File created: 2010-12-07
/ File updated: 2011-01-29
/ License: GPLv3
*/
#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include <string>   //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../graphics/sprite.h"
#include "../graphics/imagehandler.h"

namespace sbe
{
    class Entity : public sbe::Sprite
    {
        /*
            Base entity class
        */
        public:
            Entity()
            {

            }
            Entity(const sf::Image& img);
            Entity(const std::string& imgStr, ImageHandler* iHandler);
            ~Entity();

            void setImage(const std::string& imgStr)
            {
                SetImage(imgHandler->getImage(imgStr));
            }

            //virtual void update(const float& elapsed) =0; //Or onThink(), whatever.
            void SetAlpha(int alpha);
            float GetAlpha();
            void SetDiffuseColor(const int& r, const int& g, const int& b);
            void SetColorR(const int& r);
            void SetColorG(const int& g);
            void SetColorB(const int& b);
        protected:
            ImageHandler* imgHandler;
    };
}

#endif
