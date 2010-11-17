/*
/ Abstract file handler class
/ Author: Victor Rådmark, Felix Westin
/ File created: 2010-11-17
/ File updated: 2010-11-17
/ License: GPLv3
*/
#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <fstream> //File I/O without the O

namespace sbe
{
    class FileHandler
    {
        /*
            Abstract base class for media handlers. Better system to be implemented shortly, with templates and stuff.
        */
        public:
            FileHandler() {}
            ~FileHandler() {}

            //Unload all media
            template <class genMedia>
            void unloadAssets(std::map<std::string, genMedia> genMap);

        protected:
            std::ifstream fileReader;
    };
}


#endif FILEHANDLER_H_INCLUDED
