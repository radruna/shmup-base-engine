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

namespace sbe
{
    class Enemy : public Ship
    {
        public:
            Enemy(){}
            Enemy(
                ImageHandler* imgHandler,
                const std::string spriteName,
                Path& pth
            );

        private:
            void update(const float& elapsed);

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
