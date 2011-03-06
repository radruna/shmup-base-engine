/*
/ Abstract file handler class
/ Author: Victor Rådmark, Felix Westin
/ File created: 2010-11-17
/ File updated: 2010-11-25
/ License: GPLv3
*/
#ifndef FILEHANDLER_H_INCLUDED
#define FILEHANDLER_H_INCLUDED

#include <map>
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

            template <class genMedia>
            //Unload all media
            void unloadAssets(std::map<std::string, genMedia>& genMap);
            //Search and remove any spaces
            static void strStripSpace(std::string& stripper);
            //Read line and output two strings
            static bool strReadLine(std::string& strSource, std::string& strKey, std::string& strValue);

        protected:
            //std::ifstream fileReader;     //Removed because it keeps fucking my shit up
    };
}


#endif
