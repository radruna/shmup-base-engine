/*
/ Path class
/ Author: Jonathan Orrö, Niklas Andréasson
/ File created: 2011-03-22
/ File updated: 2011-03-22
/ License: GPLv3
*/
#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED


namespace sbe
{
    class Path
    {
        public:
            Path(){}
            Path(
                float speed
            );
            float getSpeed();

        private:
            float speed;

    };
}

#endif
