/*
/ Abstract file handler class
/ Author: Victor Rådmark, Felix Westin
/ File created: 2010-11-17
/ File updated: 2010-11-17
/ License: GPLv3
*/

#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include "filehandler.h"

namespace sbe
{
    template <class genMedia>
    //Unload all assets
    void FileHandler::unloadAssets(std::map<std::string, genMedia> genMap)
    {
        genMap.clear();
    }
    //Search and remove any spaces
    void FileHandler::stringStripSpace(std::string& stripper)
    {
        int spacePos;
        while(stripper.find(' ') != std::string::npos)
                {
                    spacePos = stripper.find(' ');
                    stripper.erase(spacePos,1);
                }
    }
}
