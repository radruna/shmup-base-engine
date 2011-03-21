/*
/ Enemy class
/ Author: Jonathan Orrö
/ File created: 2011-03-04
/ File updated: 2011-03-04
/ License: GPLv3
*/
#include "enemy.h"

namespace sbe
{
    Enemy::Enemy(ImageHandler* imgHandler, const std::string spriteName)
    : Ship(spriteName, imgHandler)
    {

    }

    bool Enemy::LoadFromFile(const std::string& Filename)
    {
        // Let the image loader load the image into our pixel array
        /*bool Success = priv::ImageLoader::GetInstance().LoadImageFromFile(Filename, myPixels, myWidth, myHeight);

        if (Success)
        {
            // Loading succeeded : we can create the texture
            if (CreateTexture())
                return true;
        }

        // Oops... something failed
        Reset();*/

        return false;
    }
}
