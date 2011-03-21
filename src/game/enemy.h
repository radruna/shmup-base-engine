/*
/ Enemy class
/ Author: Jonathan Orrö
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "ship.h"

namespace sbe
{
    class Enemy : public Ship
    {
        public:
            Enemy(){}
            Enemy(
                ImageHandler* imgHandler,
                const std::string spriteName
            );
            bool LoadFromFile(const std::string& Filename);
    };
}

#endif
