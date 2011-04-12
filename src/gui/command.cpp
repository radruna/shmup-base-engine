/*
/ Console command class
/ Author: Victor Rådmark
/ Created: 2011-04-12
/ Updated: 2011-04-12
/ License: GPL v3
*/
#include <string>
#include <vector>

#include "command.h"

namespace sbe
{
    Command::Command()
    {
        object = NULL;
        function = NULL;
        parFunction = NULL;
    }

    Command::Command(void* callObject, void (*cmdFunction) (void* object, StrVec args))
    {
        object = callObject;
        parFunction = cmdFunction;
        function = NULL;
    }

    Command::Command(void* callObject, void (*cmdFunction) (void* object))
    {
        object = callObject;
        function = cmdFunction;
        parFunction = NULL;
    }

    void Command::exec(const StrVec args)
    {
        (function != NULL) ? function(object) : parFunction(object, args);
    }
}
