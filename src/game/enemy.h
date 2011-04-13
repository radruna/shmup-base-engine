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
#include "path.h"
#include "hitbox.h"

namespace sbe
{
    class Enemy : public Ship
    {
        public:
            Enemy()
                //: hitbox(NULL)
            {}
            Enemy(
                ImageHandler* imgHandler,
                const std::string spriteName,
                Path pth,
                float r
            );
            ~Enemy();
            int returnRadius();
            void update(const float& elapsed);
        private:
            float hitBoxRadius;
            //Hitbox* hitbox;
            Path path;
            sf::Clock   MoveClock,
                        OrientClock;
            float       Time,
                        OrientTime,
                        maxangle,
                        duration,
                        orientation,
                        orientDuration,
                        orientStart,
                        orientStop,
                        orientmax,
                        orientmin,
                        startAngle,
                        stopAngle,
                        stopMax,
                        rotationTime,
                        angleTime,
                        angle,
                        speed;
            int         orientDir,
                        dir;
            unsigned    i;
    };
}

#endif
