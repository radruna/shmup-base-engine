/*
/ Movable class which can move according to angle
/ Author: Victor Rådmark
/ File created: 2011-01-04
/ File updated: 2011-01-07
/ License: GPLv3
*/
#ifndef MOVABLE_H_INCLUDED
#define MOVABLE_H_INCLUDED

#include <cmath> //For calculating speed

#include "../sys/const.h" //Constants
#include "entity.h"

namespace sbe
{
    class Movable : public sbe::Entity
    {
        public:
            Movable() {}
            Movable(const sf::Image& img, const float& a = 0, const float& s = 0);
            Movable(const std::string& imgStr, ImageHandler* iHandler, const float& a = 0, const float& s = 0);
            ~Movable()
            {

            }

            void update(const float& elapsed);
            void push(const float& distance);
            void setSpeedFactor(float f);
            float getAngle()
            {
                return angle;
            }
            void setAngle(const float& a)
            {
                angle = a;
            }
        private:
            float speedFactor;
        protected:
            float angle,
                  speed;
    };
}

#endif
