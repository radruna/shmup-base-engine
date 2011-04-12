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

    Command::Command(const std::string& description, void* callObject, void (*cmdFunction) (void* object, StrVec args))
        : desc(description)
    {
        object = callObject;
        parFunction = cmdFunction;
        function = NULL;
    }

    Command::Command(const std::string& description, void* callObject, void (*cmdFunction) (void* object))
        : desc(description)
    {
        object = callObject;
        function = cmdFunction;
        parFunction = NULL;
    }

    bool Command::exec(const StrVec args)
    {
        if(function != NULL)
            function(object);
        else
        {
            if(args.empty()) return false;
            parFunction(object, args);
        }

        return true;
    }
}
