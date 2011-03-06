////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

/*
/ Sprite class which inherits from sbe::Drawable instead, and thus has an z value.
/ Based on the sf::Sprite class from the SFML library by Laurent Gomila.
/ Author: Victor Rådmark
/ File created: 2011-03-05
/ File updated: 2011-03-05
/ License: GPLv3
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/GraphicsContext.hpp>

#include "sprite.h"

namespace sbe
{

////////////////////////////////////////////////////////////
/// Check the last OpenGL error
///
////////////////////////////////////////////////////////////
inline void GLCheckError(const std::string& File, unsigned int Line)
{
    // Get the last error
    GLenum ErrorCode = glGetError();

    if (ErrorCode != GL_NO_ERROR)
    {
        std::string Error = "unknown error";
        std::string Desc  = "no description";

        // Decode the error code
        switch (ErrorCode)
        {
            case GL_INVALID_ENUM :
            {
                Error = "GL_INVALID_ENUM";
                Desc  = "an unacceptable value has been specified for an enumerated argument";
                break;
            }

            case GL_INVALID_VALUE :
            {
                Error = "GL_INVALID_VALUE";
                Desc  = "a numeric argument is out of range";
                break;
            }

            case GL_INVALID_OPERATION :
            {
                Error = "GL_INVALID_OPERATION";
                Desc  = "the specified operation is not allowed in the current state";
                break;
            }

            case GL_STACK_OVERFLOW :
            {
                Error = "GL_STACK_OVERFLOW";
                Desc  = "this command would cause a stack overflow";
                break;
            }

            case GL_STACK_UNDERFLOW :
            {
                Error = "GL_STACK_UNDERFLOW";
                Desc  = "this command would cause a stack underflow";
                break;
            }

            case GL_OUT_OF_MEMORY :
            {
                Error = "GL_OUT_OF_MEMORY";
                Desc  = "there is not enough memory left to execute the command";
                break;
            }

            case GL_INVALID_FRAMEBUFFER_OPERATION_EXT :
            {
                Error = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
                Desc  = "the object bound to FRAMEBUFFER_BINDING_EXT is not \"framebuffer complete\"";
                break;
            }
        }

        // Log the error
        std::cerr << "An internal OpenGL call failed in "
                  << File.substr(File.find_last_of("\\/") + 1) << " (" << Line << ") : "
                  << Error << ", " << Desc
                  << std::endl;
    }
}
////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
Sprite::Sprite() :
mySubRect   (0, 0, 1, 1),
myIsFlippedX(false),
myIsFlippedY(false)
{

}


////////////////////////////////////////////////////////////
/// Construct the sprite from a source image
////////////////////////////////////////////////////////////
Sprite::Sprite(const sf::Image& Img, const sf::Vector2f& Position, const sf::Vector2f& Scale, float Rotation, const sf::Color& Col) :
Drawable    (Position, Scale, Rotation, Col),
mySubRect   (0, 0, 1, 1),
myIsFlippedX(false),
myIsFlippedY(false)
{
    SetImage(Img);
}


////////////////////////////////////////////////////////////
/// Set the image of the sprite
////////////////////////////////////////////////////////////
void Sprite::SetImage(const sf::Image& Img)
{
    // If there was no source image before and the new image is valid, adjust the source rectangle
    if (!myImage && (Img.GetWidth() > 0) && (Img.GetHeight() > 0))
    {
        SetSubRect(sf::IntRect(0, 0, Img.GetWidth(), Img.GetHeight()));
    }

    // Assign the new image
    myImage = &Img;
}


////////////////////////////////////////////////////////////
/// Set the sub-rectangle of the sprite inside the source image
////////////////////////////////////////////////////////////
void Sprite::SetSubRect(const sf::IntRect& SubRect)
{
    mySubRect = SubRect;
}


////////////////////////////////////////////////////////////
/// Resize the sprite (by changing its scale factors) (take 2 values).
/// The default size is defined by the subrect
////////////////////////////////////////////////////////////
void Sprite::Resize(float Width, float Height)
{
    int LocalWidth  = mySubRect.GetWidth();
    int LocalHeight = mySubRect.GetHeight();

    if ((LocalWidth > 0) && (LocalHeight > 0))
        SetScale(Width / LocalWidth, Height / LocalHeight);
}


////////////////////////////////////////////////////////////
/// Resize the object (by changing its scale factors) (take a 2D vector)
/// The default size is defined by the subrect
////////////////////////////////////////////////////////////
void Sprite::Resize(const sf::Vector2f& Size)
{
    Resize(Size.x, Size.y);
}


////////////////////////////////////////////////////////////
/// Flip the sprite horizontally
////////////////////////////////////////////////////////////
void Sprite::FlipX(bool Flipped)
{
    myIsFlippedX = Flipped;
}


////////////////////////////////////////////////////////////
/// Flip the sprite vertically
////////////////////////////////////////////////////////////
void Sprite::FlipY(bool Flipped)
{
    myIsFlippedY = Flipped;
}


////////////////////////////////////////////////////////////
/// Get the source image of the sprite
////////////////////////////////////////////////////////////
const sf::Image* Sprite::GetImage() const
{
    return myImage;
}


////////////////////////////////////////////////////////////
/// Get the sub-rectangle of the sprite inside the source image
////////////////////////////////////////////////////////////
const sf::IntRect& Sprite::GetSubRect() const
{
    return mySubRect;
}


////////////////////////////////////////////////////////////
/// Get the sprite size
////////////////////////////////////////////////////////////
sf::Vector2f Sprite::GetSize() const
{
    return sf::Vector2f(mySubRect.GetWidth() * GetScale().x, mySubRect.GetHeight() * GetScale().y);
}


////////////////////////////////////////////////////////////
/// Get the color of a given pixel in the sprite
/// (point is in local coordinates)
////////////////////////////////////////////////////////////
sf::Color Sprite::GetPixel(unsigned int X, unsigned int Y) const
{
    if (myImage)
    {
        unsigned int ImageX = mySubRect.Left + X;
        unsigned int ImageY = mySubRect.Top  + Y;

        if (myIsFlippedX) ImageX = mySubRect.GetWidth()  - ImageX - 1;
        if (myIsFlippedY) ImageY = mySubRect.GetHeight() - ImageY - 1;

        return myImage->GetPixel(ImageX, ImageY) * GetColor();
    }
    else
    {
        return GetColor();
    }
}


////////////////////////////////////////////////////////////
/// /see sfDrawable::Render
////////////////////////////////////////////////////////////
void Sprite::Render(sf::RenderTarget&) const
{
    // Get the sprite size
    float Width  = static_cast<float>(mySubRect.GetWidth());
    float Height = static_cast<float>(mySubRect.GetHeight());

    // Check if the image is valid
    if (myImage && (myImage->GetWidth() > 0) && (myImage->GetHeight() > 0))
    {
        // Use the "offset trick" to get pixel-perfect rendering
        // see http://www.opengl.org/resources/faq/technical/transformations.htm#tran0030
        GLCheck(glTranslatef(0.375f, 0.375f, 0.f));

        // Bind the texture
        myImage->Bind();

        // Calculate the texture coordinates
        sf::FloatRect TexCoords = myImage->GetTexCoords(mySubRect);
        sf::FloatRect Rect(myIsFlippedX ? TexCoords.Right  : TexCoords.Left,
                       myIsFlippedY ? TexCoords.Bottom : TexCoords.Top,
                       myIsFlippedX ? TexCoords.Left   : TexCoords.Right,
                       myIsFlippedY ? TexCoords.Top    : TexCoords.Bottom);

        // Draw the sprite's triangles
        glBegin(GL_QUADS);
            glTexCoord2f(Rect.Left,  Rect.Top);    glVertex2f(0,     0);
            glTexCoord2f(Rect.Left,  Rect.Bottom); glVertex2f(0,     Height);
            glTexCoord2f(Rect.Right, Rect.Bottom); glVertex2f(Width, Height);
            glTexCoord2f(Rect.Right, Rect.Top);    glVertex2f(Width, 0) ;
        glEnd();
    }
    else
    {
        // Disable texturing
        GLCheck(glDisable(GL_TEXTURE_2D));

        // Draw the sprite's triangles
        glBegin(GL_QUADS);
            glVertex2f(0,     0);
            glVertex2f(0,     Height);
            glVertex2f(Width, Height);
            glVertex2f(Width, 0);
        glEnd();
    }
}

} // namespace sf

