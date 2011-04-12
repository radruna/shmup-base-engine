/*
/ Console command class
/ Author: Victor Rådmark
/ Created: 2011-04-12
/ Updated: 2011-04-12
/ License: GPL v3
*/
#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED

#include <string>
#include <vector>

typedef std::vector<std::string> StrVec;

namespace sbe
{
    class Command
    {
        public:
            Command();
            Command(const std::string& description, void* callObject, void (*cmdFunction) (void* object, StrVec args));
            Command(const std::string& description, void* callObject, void (*cmdFunction) (void* object));
            ~Command()
            {

            }

            bool exec(StrVec args);

            std::string getDescription()
            {
                return desc;
            }

        private:
            std::string desc;
            void* object;
            void (*function) (void* object);
            void (*parFunction) (void* object, StrVec);
    };
}

#endif
