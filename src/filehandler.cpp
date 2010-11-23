/*
/ Abstract file handler class
/ Author: Victor Rådmark, Felix Westin
/ File created: 2010-11-17
/ File updated: 2010-11-17
/ License: GPLv3
*/

#include <iostream> //Debug
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
    void FileHandler::strStripSpace(std::string& stripper)
    {
        int spacePos;
        while(stripper.find(' ') != std::string::npos)
        {
            spacePos = stripper.find(' ');
            stripper.erase(spacePos,1);
        }
    }
    //Read line and output two strings
    int FileHandler::strReadLine(std::string& strSource, std::string& strKey, std::string& strValue)
    {

        int tabPos;
        int spacePos;
        int commentPos;

        if(strSource.find("//") != std::string::npos)
        {
             //Find comment
            commentPos = strSource.find("//");
            //Is comment at the start of the line? If so: skip this line
            if(commentPos == 0)
                return -1;
                //TODO (Fewes#3#): Fix so that it's possible to have tabs/spaces before a line starting with '//'
            //Cut comment
            strSource = strSource.substr(0,commentPos);
        }
        //Replace tabs with spaces
        while(strSource.find('\t') != std::string::npos)
        {
            tabPos = strSource.find('\t');
            strSource.replace(tabPos,1," ");
        }

        //Find first space
        if(strSource.find(' ') == std::string::npos)
                return -1;
        else
        {
            //Find first space
            spacePos = strSource.find (' ');

            //Set first string
            strKey = strSource.substr(0,spacePos);
            //Search and remove any spaces
            FileHandler::strStripSpace(strKey);

            //Set image path
            strValue = strSource.substr(strKey.length(),strSource.length());
            //Search and remove any spaces
            FileHandler::strStripSpace(strValue);
        }

    }
}
