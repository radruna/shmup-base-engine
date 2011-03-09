/*
/ Class for action constructs
/ Author: Victor Rådmark
/ File created: 2011-03-08
/ File updated: 2010-03-08
/ License: GPLv3
*/
#include <string>

#include "action.h"

namespace sbe
{
    Action::Action(void* callObject, void (*callFunction) (void* object), const std::string& key)
        : key(key)
    {
        funcObject = callObject;
        actionFunc = callFunction;
    }
}
