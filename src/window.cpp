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
#include <SFML/Audio.hpp> //hurr durr

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
        imgHandler = new ImageHandler();
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
        imgHandler->loadAssets("scripts/assets/test.ast");
        //Test stuff with a really kawaii ship
        sf::Image img = imgHandler->getImage("testShip");
        sf::Image img2 = imgHandler->getImage("kawaiiShip");
        testShip = new sf::Sprite(img);
        //*ships["testShip"] = *testShip;
        testShip->SetPosition(0.f, 0.f);
        testShip->SetScale(0.5, 0.5);

        sf::Shape shot = sf::Shape::Line(0.f, 0.f, 0.f, 1000.f, 2.f, sf::Color::Yellow);
        sf::Shape shot2 = shot;
        shot2.SetColor(sf::Color::Yellow);
        double speed = 5;
        int counter = 0;
        bool gun = true;
        int gunPosX = 0;

        double speedX = 0;
        double speedY = 0;

        sf::Music loli;

        if(!loli.OpenFromFile("assets/music/loli.ogg"))
            std::cout << ":<";

        loli.Play();

        sf::SoundBuffer laserBuffer;
        if(!laserBuffer.LoadFromFile("assets/sound/durr.wav"))
            std::cout << ":<";

        sf::Sound laser(laserBuffer);

        while(IsOpened())
        {
            // Process events, to be replaced by evtHandler
            sf::Event Event;
            while (GetEvent(Event))
            {
                // Close mainWindow : exit
                if (Event.Type == sf::Event::Closed)
                    Close();
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::L))
                {
                    if(loli.GetStatus() == sf::Sound::Playing)
                        loli.Pause();
                    else
                        loli.Play();
                }
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::B))
                {
                    testShip->SetImage(img2);

                    loli.Stop();

                    if(!loli.OpenFromFile("assets/music/8bitloli.ogg"))
                        std::cout << "3:";

                    loli.Play();
                }
            }

            // Get elapsed time
            float ElapsedTime = GetFrameTime();

            if(GetInput().IsKeyDown(sf::Key::LShift))
            {
                speed = 1;
            }
            else
                speed = 10;

            // Move the sprite
            /*
            if (GetInput().IsKeyDown(sf::Key::Left))  testShip->Move((-speed - (acc++ * 10)) * ElapsedTime, 0);
            if (GetInput().IsKeyDown(sf::Key::Right)) testShip->Move((speed + (acc++ * 10)) * ElapsedTime, 0);
            if (GetInput().IsKeyDown(sf::Key::Up))    testShip->Move(0, (-speed - (acc++ * 10)) * ElapsedTime);
            if (GetInput().IsKeyDown(sf::Key::Down))  testShip->Move(0,  (speed + (acc++ * 10)) * ElapsedTime);
            */

            if (GetInput().IsKeyDown(sf::Key::Left) && speedX > -15){
                speedX -= speed;
            }else if(GetInput().IsKeyDown(sf::Key::Right) && speedX < 15){
                speedX += speed;
            }else{
                if(speedX < 0) speedX++;
                if(speedX > 0) speedX--;
            }
            if (GetInput().IsKeyDown(sf::Key::Up) && speedY > -15){
                speedY -= speed;
            }else if (GetInput().IsKeyDown(sf::Key::Down) && speedY < 15){
                speedY += speed;
            }else{
                if(speedY < 0) speedY++;
                if(speedY > 0) speedY--;
            }

            testShip->Move(speedX,speedY);

            if(GetInput().IsKeyDown(sf::Key::Z) && counter < 10)
            {
                counter = 100;
                shot.SetCenter(0, 1000.f);
                if(gun)
                {
                    shot.SetColor(sf::Color::Yellow);
                    gun = false;
                    gunPosX = 42;
                }
                else
                {
                    shot.SetColor(sf::Color::Cyan);
                    gun = true;
                    gunPosX = 80;
                }

                shot.SetPosition(testShip->GetPosition().x + gunPosX, testShip->GetPosition().y + 58);
                laser.Play();
            }
            else if(counter < 40)
            {
                shot.Move(0, (-2000 * ElapsedTime));
            }


            // Clear screen
            Clear();

            // Draw the ship
            Draw(*testShip);

            if(counter > 0)
            {
                --counter;
                Draw(shot);
            }

            // Update the window
            Display();

            //Display the intro and then the main menu
            //evtHandler.Handle(); //hurr!!!
        }

        return 0;
    }
}
