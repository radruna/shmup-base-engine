/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <string> //For strings
#include <map> //For mapping objects

#include <SFML/Graphics.hpp> //Graphics and everything above

#include "window.h" //Class def
#include "imagehandler.h"
//#include "eventhandler.h" //Not done yet
//#include "panel.h"

namespace sbe
{
    Window::Window(sf::VideoMode Mode, const std::string& Title, const bool& showIntro, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, Title, WindowStyle, Params)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        RenderWindow::Window::SetFramerateLimit(60);
        imgHandler = new sbe::ImageHandler();
        //evtHandler = new sbe::EventHandler();
        //mainMenu = new sbe::Panel();
        ships = new std::map<std::string, sf::Sprite>;
    }

    Window::~Window()
    {
        delete imgHandler;
        delete ships;
        delete testShip;
    }

    int Window::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */
        sf::Clock clock; //For frame checking etc
        //Test stuff with a really kawaii ship
        testShip = new sf::Sprite(imgHandler->getImage("testShip"));
        //*ships["testShip"] = *testShip;
        testShip->SetPosition(0.f, 0.f);
        testShip->SetCenter(128, 128);
        testShip->SetScale(0.25,0.25);

        int temp = 0;
        while(IsOpened())
        {
            // Process events, to be replaced by evtHandler
            sf::Event Event;
            while (GetEvent(Event))
            {
                // Close mainWindow : exit
                if (Event.Type == sf::Event::Closed)
                    Close();
            }

            testShip->SetRotation(testShip->GetRotation() + temp);
            testShip->SetX(testShip->GetPosition().x + temp);
            testShip->SetY(testShip->GetPosition().y + temp++);

            // Clear screen
            Clear();

            // Draw the ship
            Draw(*testShip);

            // Update the window
            Display();

            //Display the intro and then the main menu
            //evtHandler.Handle(); //hurr!!!
        }

        return 0;
    }
}
