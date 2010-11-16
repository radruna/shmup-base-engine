/*
/ The main function
/ Author: Victor Rådmark, Felix Westin, Jonathan Orrö
/ File created: 2010-11-14
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <SFML/Graphics.hpp>

#include "window.h"

int main()
{
    // Create the main mainWindow
    sbe::Window mainWindow(sf::VideoMode(1024, 768), "SBE Window");

    // Load a sprite to display
    sf::Image Image;
    if (!Image.LoadFromFile("assets/jet.png"))
        return EXIT_FAILURE;

    sf::Sprite Sprite(Image);
    Sprite.SetPosition(0.f, 0.f);
    Sprite.SetCenter(128, 128);
    Sprite.SetScale(0.25,0.25);

    mainWindow.SetFramerateLimit(60);

	// Start the game loop
	int temp = 0;
    while (mainWindow.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (mainWindow.GetEvent(Event))
        {
            // Close mainWindow : exit
            if (Event.Type == sf::Event::Closed)
                mainWindow.Close();
        }

        //Rotate image
        //Sprite.Rotate(-20);
        Sprite.SetRotation(Sprite.GetRotation() + temp);
        Sprite.SetX(Sprite.GetPosition().x + temp);
        Sprite.SetY(Sprite.GetPosition().y + temp++);
        // Clear screen
        mainWindow.Clear();

        // Draw the sprite
        mainWindow.Draw(Sprite);

        // Update the mainWindow
        mainWindow.Display();
    }

    return EXIT_SUCCESS;
}
