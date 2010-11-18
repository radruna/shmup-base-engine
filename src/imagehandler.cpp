/*
/ Image handler class
/ Author: Felix Westin
/ File created: 2010-11-16
/ File updated: 2010-11-17
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string> //For strings

#include <SFML/Graphics.hpp> //Sfml stuff

#include "imagehandler.h"   //Class def
#include "filehandler.h" //Base class

namespace sbe
{
    ImageHandler::ImageHandler()
    {
        //Load intro or menu stuff
    }

    //Load images listed in the asset file
    void ImageHandler::loadAssets(const std::string& assetFile)
    {
        std::cout << std::endl << "Loading assets from: \"" << assetFile << "\"..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, assetFile.c_str());
        //Open specified file
        fileReader.open(str);
        if(!fileReader)
        {
            //Debug output
            std::cout << "The image handler was unable to open the specified asset file" << std::endl;
            return;
        }

        int tabPos;
        int spacePos;
        int commentPos;
        int lineVar = 0;
        std::string output;
        std::string imageKey;
        std::string imagePath;

        //Loop until end of file
        while(!fileReader.eof())
        {
            //Read line
            getline(fileReader,output);
            //Check if line is empty
            if(output != "")
            {
                //Register new line
                lineVar++;
                //Replace tabs with spaces
                while(output.find('\t') != std::string::npos)
                {
                    tabPos = output.find('\t');
                    output.replace(tabPos,1," ");
                }

                //Find first space
                if(output.find(' ' ) == std::string::npos)
                        //If not found
                        std::cout << "Incorrect asset on line " << lineVar << " in file \"" << assetFile << "\"" << std::endl;
                else
                {
                    //Find first space
                    spacePos = output.find (' ');
                    if(output.find("//") != std::string::npos)
                    {
                         //Find comment
                        commentPos = output.find("//");
                        //Cut comment
                        output = output.substr(0,commentPos);
                    }

                    //Set image key
                    imageKey = output.substr(0,spacePos);
                    //Search and remove any spaces. Should be replaced by a stringStripSpace function.
                    imageKey.erase(std::remove(imageKey.begin(), imageKey.end(), ' '), imageKey.end());

                    //Set image path
                    imagePath = output.substr(imageKey.length(),output.length());
                    //Search and remove any spaces or tabs. Should be replaced by a stringStripSpace function.
                    imagePath.erase(std::remove(imagePath.begin(), imagePath.end(), ' '), imagePath.end());

                    //Search imageList
                    if(imageList.find(imageKey) != imageList.end())
                        std::cout << "Failed to load image \"" << imagePath << "\". Reason: Image key already in system" << std::endl;
                    else
                    {
                        sf::Image img;
                        //Load image file
                        if(!img.LoadFromFile(imagePath))
                        {
                            /*
                            //This is already handled by SFML
                            std::cout << "Failed to load image \"" << imagePath << "\". Reason: Unable to open image file" << std::endl;
                            */
                        }
                        else
                        {
                            //Add to imageList
                            imageList[imageKey] = img;
                            //Debug output
                            std::cout << "Loaded image \"" << imageKey << "\" with filepath \"" << imagePath << "\"" << std::endl;
                        }
                    }
                }
            }
        }
        //Debug output
        std::cout << "Finished loading images from \"" << assetFile << "\"" << std::endl;
        //Close file
        fileReader.close();
    }

    //Unload all images
    void ImageHandler::unloadAssets(){
        //FileHandler::unloadAssets(imageList);
        imageList.clear();
    }

    //Handle image requests
    sf::Image ImageHandler::getImage(const std::string& imageKey){
        sf::Image img;
        //Search imageList
        if( imageList.find(imageKey) != imageList.end() )
        {
            //Assign image
            img = imageList[imageKey];
        }else{
            //Assign error image
            img.LoadFromFile("assets/debug/error.png");
        }
        return img;
    }
}
