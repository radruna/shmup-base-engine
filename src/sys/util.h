/*
/ Cool utils for memory management and stuff
/ Author: Victor Rådmark
/ File created: 2011-02-18
/ File updated: 2011-02-18
/ License: GPLv3
*/
#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

namespace sbe
{
    template<class pT>
    static void safeDelete(pT*& pointer)
    {
        if(pointer != NULL)
        {
            delete pointer;
            pointer = NULL;
        }
    }

    /*static sf::Vector2i const getScreenRes()
    {
        return sf::Vector2i(0, 0);
    }*/
}

#endif
