/*
/ Base entity class
/ Authors: Felix Westin and Victor Rådmark
/ File created: 2010-12-07
/ File updated: 2010-12-24
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"
#include "filehandler.h" //Base class
#include "entity.h" //Header

namespace sbe
{
    Entity::Entity(const sf::Image& img)
    {
        /*
            Constructs the entity by setting the image.
        */
        SetImage(img);
    }

    Entity::Entity(const std::string& imgStr, ImageHandler* iHandler)
    {
        /*
            Constructs the entity by setting its image handler and its default image.
        */
        imgHandler = iHandler;
        SetImage(iHandler->getImage(imgStr));
    }

    Entity::~Entity()
    {
        //delete imgHandler;
    }

    void Entity::SetAlpha(int alpha)
    {
        if(alpha > 255)
            alpha = 255;
        else if(alpha < 0)
            alpha = 0;

        sf::Color col = GetColor();
        col.a = alpha;
        SetColor( col );
    }

    void Entity::SetDiffuseColor(const int& r, const int& g, const int& b)
    {
        sf::Color col = GetColor();
        col.r = r;
        col.g = g;
        col.b = b;
        SetColor( col );
    }

    void Entity::SetColorR(const int& r)
    {
        sf::Color col = GetColor();
        col.r = r;
        SetColor( col );
    }

    void Entity::SetColorG(const int& g)
    {
        sf::Color col = GetColor();
        col.g = g;
        SetColor( col );
    }

    void Entity::SetColorB(const int& b)
    {
        sf::Color col = GetColor();
        col.b = b;
        SetColor( col );
    }
}
