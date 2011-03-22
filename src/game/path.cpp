/*
/ Path class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-22
/ File updated: 2011-03-22
/ License: GPLv3
*/

#include "path.h"

namespace sbe
{
    Path::Path(float spd)
    {
        speed = spd;
    }

    float Path::getSpeed()
    {
        return speed;
    }
}

