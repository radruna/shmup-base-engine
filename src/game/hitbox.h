/*
/ Hitbox class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-04-12
/ File updated: 2011-04-12
/ License: GPLv3
*/
#ifndef HITBOX_H_INCLUDED
#define HITBOX_H_INCLUDED

namespace sbe
{
    class Hitbox
    {
        public:
            Hitbox(
                    float r
            );
            Hitbox(){}
            float returnRadie();
        protected:
            float radie;

    };
}

#endif

