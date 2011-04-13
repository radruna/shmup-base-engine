/*
/ Hitbox class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-04-12
/ File updated: 2011-04-12
/ License: GPLv3
*/

#include "hitbox.h"

namespace sbe
{
    Hitbox::Hitbox(float r)
    {
        radius = r;
    }


    float Hitbox::returnRadius()
    {
        return radius;
    }
}


