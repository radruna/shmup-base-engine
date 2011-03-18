/*
/ Enemy class
/ Author: Jonathan Orrö
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include "enemy.h"

namespace sbe
{
    Enemy::Enemy
    (
        const std::string&     spriteName,
        ImageHandler* imgHandler
    )
    : Ship(spriteName, imgHandler)
    {

    }
}
