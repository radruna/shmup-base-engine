/*
/ Enemy class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include "enemy.h"

namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName)
    : Ship(spriteName, imgHandler)
    {

    }

}
