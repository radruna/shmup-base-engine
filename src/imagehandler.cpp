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

namespace sbe
{
    ImageHandler::ImageHandler()
    {

    }

    //Load images listed in the asset file
    void ImageHandler::loadAssets(const std::string& assetFile){
        std::cout << std::endl << "Loading assets from: '" << assetFile << "'..." << std::endl;
        char str[255];
        //Convert string to char array
        strcpy(str, assetFile.c_str());
        //Open specified file
        fileReader.open(str);
        if(fileReader.is_open())
        {
            int spacePos;
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
                    //Find space
                    spacePos = output.find (' ');
                    //Set image key
                    imageKey = output.substr(0,spacePos);

                    //Search imageList
                    if( imageList.find(imageKey) != imageList.end() )
                    {
                        std::cout << "Image key '" << imageKey << "' already in system. Skipping..." << std::endl;
                    }else{
                        //Set image path
                        imagePath = output.substr(spacePos+1,output.length() - (spacePos + 1));
                        //Debug output
                        std::cout << "Loaded image: '" << imageKey << "' with filepath: '" << imagePath << "'" << std::endl;
                        sf::Image img;
                        //Load image file
                        img.LoadFromFile(imagePath);
                        //Add to imageList
                        imageList[imageKey] = img;
                    }
                }
            }
            //Debug output
            std::cout << "Finished loading assets from: '" << assetFile << "'" << std::endl;
        }else
        {
            //Debug output
            std::cout << "The image handler was unable to open the specified asset file." << std::endl;
        }
        //Close file
        fileReader.close();
    }

    //Unload all images
    void ImageHandler::unloadAssets(){
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
