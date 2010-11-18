/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2010-11-18
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <string> //For strings
#include <map> //For mapping objects

#include <SFML/Graphics.hpp> //Graphics and everything above
#include <SFML/Audio.hpp> //hurr durr

#include "window.h" //Class def
#include "imagehandler.h" //For loading images
#include "audiohandler.h" //For loading and playing sound and music
//#include "eventhandler.h" //Not done yet
//#include "panel.h"

namespace sbe
{
    Window::Window(sf::VideoMode Mode, const std::string& Title, const bool& showIntro, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, Title, WindowStyle, Params), debug(false)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        std::cout << "Window loaded!" << std::endl;
        RenderWindow::Window::SetFramerateLimit(60);
        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        //evtHandler = new sbe::EventHandler();
        std::cout << "Handlers loaded!" << std::endl;
        //mainMenu = new sbe::Panel();
        //std::cout << "Main menu loaded." << std::endl;
        ships = new std::map<std::string, sf::Sprite>;
        std::cout << "Objects loaded" << std::endl;
    }

    Window::~Window()
    {
        /*
            Purpose: Deconstructor for sbe::Window
        */
        delete imgHandler;
        delete audHandler;
        delete ships;
        delete testShip;
    }

    int Window::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */
        imgHandler->loadAssets("scripts/assets/test.ast");
        audHandler->loadSound("scripts/assets/sound.ast");
        audHandler->loadMusic("scripts/assets/music.ast");
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
        double speedVar = 5;
        int counter = 0;
        bool gun = true;
        int gunPosX = 0;

        sf::Vector2f speed(0.f, 0.f);

        /*audHandler->setMusic("loli");
        sf::Sound laser = audHandler->getSound("laser");*/
        sf::Music loli;
        loli.OpenFromFile("assets/music/loli.ogg");
        loli.Play();
        sf::SoundBuffer lsrBfr;
        lsrBfr.LoadFromFile("assets/sound/durr.wav");
        sf::Sound laser(lsrBfr);

        while(IsOpened())
        {
            // Process events, to be replaced by evtHandler
            sf::Event Event;
            while (GetEvent(Event))
            {
                // Close mainWindow : exit
                if (Event.Type == sf::Event::Closed)
                    Close();
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::Escape))
                    Close();
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::L))
                {
                    audHandler->pauseMusic();
                }
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::B))
                {
                    testShip->SetImage(img2);

                    //audHandler->setMusic("8bitloli");
                    loli.Stop();
                    loli.OpenFromFile("assets/music/8bitloli.ogg");
                    loli.Play();
                }
                if ((Event.Type == sf::Event::KeyReleased) && (Event.Key.Code == sf::Key::F1))
                    debug = true;
            }

            // Get elapsed time
            float ElapsedTime = GetFrameTime();
            //Process inputs, to be replaced by evtHandler
            if(GetInput().IsKeyDown(sf::Key::LShift))
                speedVar = 1;
            else
                speedVar = 10;

            // Move the sprite
            /*
            if (GetInput().IsKeyDown(sf::Key::Left))  testShip->Move((-speed - (acc++ * 10)) * ElapsedTime, 0);
            if (GetInput().IsKeyDown(sf::Key::Right)) testShip->Move((speed + (acc++ * 10)) * ElapsedTime, 0);
            if (GetInput().IsKeyDown(sf::Key::Up))    testShip->Move(0, (-speed - (acc++ * 10)) * ElapsedTime);
            if (GetInput().IsKeyDown(sf::Key::Down))  testShip->Move(0,  (speed + (acc++ * 10)) * ElapsedTime);
            */

            if (GetInput().IsKeyDown(sf::Key::Left) && speed.x > -15){
                speed.x -= speedVar;
            }else if(GetInput().IsKeyDown(sf::Key::Right) && speed.x < 15){
                speed.x += speedVar;
            }else{
                if(speed.x < 0) speed.x++;
                if(speed.x > 0) speed.x--;
            }
            if (GetInput().IsKeyDown(sf::Key::Up) && speed.y > -15){
                speed.y -= speedVar;
            }else if (GetInput().IsKeyDown(sf::Key::Down) && speed.y < 15){
                speed.y += speedVar;
            }else{
                if(speed.y < 0) speed.y++;
                if(speed.y > 0) speed.y--;
            }

            testShip->Move(speed.x * ElapsedTime * 50, speed.y * ElapsedTime * 50);

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
        }

        return 0;
    }
}
