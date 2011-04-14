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

#include "../graphics/particlesystem.h" //Particle system

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
                float r,
                std::string pSysDeath,

                int l,

                float scale_x,
                float scale_y

            );
            ~Enemy();
            void update(const float elapsed);
            void kill(float s = 0.5);
            float xPos();
            float yPos();
            bool death()
            {
                if(deathTimer != -1 && deathTimer <= 0) return true;

                return false;
            }
            bool readyToDie()
            {
                if(deathTimer != -1) return true;

                return false;
            }
            float isDead();
            void hit();
        private:

            ParticleSystem *pSysDeath;
            std::string pSysDeath_f;

            //Hitbox* hitbox;
            Path path;
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
                        speed,
                        deathTimer,
                        deathDelay;
            int         orientDir,
                        dir,
                        life;
            unsigned    i;
        protected:
            void Render(sf::RenderTarget& Target) const;
    };
}

#endif
