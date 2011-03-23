/*
/ Path class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-22
/ File updated: 2011-03-22
/ License: GPLv3
*/
#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#include <vector>

namespace sbe
{
    class Path
    {
        public:
            struct pathContent {
                float startAngle,
                      stopAngle,
                      moveSpeed,
                      duration,
                      orientation,
                      orientStart,
                      orientStop,
                      orientDuration,
                      stopMax;
            };


            Path(){}
            Path(
                std::vector <Path::pathContent>& pathContentList
            );
            std::vector <Path::pathContent>  getVector();

            std::vector <Path::pathContent> vektor;
    };
}

#endif
