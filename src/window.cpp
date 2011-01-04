/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-01-04
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
#include "eventhandler.h" //Event handling
#include "particlesystem.h" //Particle system
#include "ship.h"
//#include "player.h"
//#include "panel.h"

namespace sbe
{
    Window::Window(sf::VideoMode Mode, const std::string& Title, const bool& showIntro, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, Title, WindowStyle, Params), res(Mode.Width, Mode.Height), debug(false), cCount(0)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        std::cout << "Window loaded!" << std::endl;
        RenderWindow::Window::SetFramerateLimit(60);

        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        evtHandler = new EventHandler();
        std::cout << "Handlers loaded!" << std::endl;

        //mainMenu = new sbe::Panel();
        //std::cout << "Main menu loaded." << std::endl;

        //ships = new std::map<std::string, Ship>;
        //ship
        std::cout << "Objects loaded!" << std::endl;

        c = sf::Color(255, 105, 108);

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
        imgHandler->loadAssets("scripts/assets/images.ast");
        audHandler->loadSound("scripts/assets/sound.ast");
        audHandler->loadMusic("scripts/assets/music.ast");

        //Test stuff with a really kawaii ship AND A PARTICLE
        sf::Image img = imgHandler->getImage("testShip");
        sf::Image img2 = imgHandler->getImage("kawaiiShip");
        sf::Image img3 = imgHandler->getImage("smoke_01");

        testShip = new sbe::Ship(img);

        //*ships["testShip"] = *testShip;
        testShip->SetPosition(0.f, 0.f);
        testShip->SetScale(0.5, 0.5);

        sf::Shape shot = sf::Shape::Line(0.f, 0.f, 0.f, 1000.f, 2.f, sf::Color::Yellow);
        sf::Shape shot2 = shot;
        shot2.SetColor(sf::Color::Yellow);

        int counter = 0;
        bool gun = true;
        int gunPosX = 0;

        sf::Vector2f speed(0.f, 0.f);

        sf::Sound laser(audHandler->getSound("laser"));

        sbe::Music loli;
        loli.OpenFromFile(audHandler->getMusic("loli2"));
        loli.Play();

        //Test particle
        sbe::Particle *p;
        p = new sbe::Particle(img3,5,45);
        p->SetPosition(500.f, 50.f);
        p->SetCenter(p->GetSize().x / 2, p->GetSize().y / 2);
        float p_alpha = 255;

        while(IsOpened())
        {

            //Update test particle
            p->update();
            if(p_alpha > 1)
                p->SetColor(sf::Color(255, 255, 255, p_alpha-= 0.3));
            p->setAngle(p->getAngle()+2);
            p->Rotate(0.2);

            // Process events, to be replaced by evtHandler
            sf::Event event;
            while (GetEvent(event))
            {
                // Close mainWindow : exit
                EventHandler::returnEvents(event, events);
                // Close mainWindow : exit
                if (event.Type == sf::Event::Closed)
                    Close();
                if (events["Escape"])
                    Close();
                if (events["L"])
                {
                    if(loli.GetStatus() != sf::Sound::Playing)
                        loli.Play();
                    else
                        loli.Pause();
                }
                if(events["B"])
                {
                    testShip->SetImage(img2);

                    //audHandler->setMusic("8bitloli");
                    loli.Stop();
                    loli.OpenFromFile(audHandler->getMusic("8bitloli"));
                    loli.Play();
                }
                if (events["L"])
                    testShip->SetPosition(res.x / 2, res.y / 2);
                if (events["F1"])
                    debug = true;

                events.clear();

            }

            //Process inputs
            if(GetInput().IsKeyDown(sf::Key::LShift))
                testShip->setMod(30);
            else
                testShip->setMod(65);

            if(GetInput().IsKeyDown(sf::Key::Left))
                testShip->fly(Ship::LEFT);
            else if(GetInput().IsKeyDown(sf::Key::Right))
                testShip->fly(Ship::RIGHT);

            if(GetInput().IsKeyDown(sf::Key::Up))
                testShip->fly(Ship::UP);
            else if(GetInput().IsKeyDown(sf::Key::Down))
                testShip->fly(Ship::DOWN);

            //Get elapsed time since last frame to ensure constant speed
            float ElapsedTime = GetFrameTime();
            //Update the ship with the input data
            testShip->update(ElapsedTime);

            //TODO (Liag#5#) Add lasers and stuff to the Ship class.
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
            if(cCount++ % 20 == 0)
            {
                if(c == sf::Color(255, 105, 180))
                    c = sf::Color::Red;
                else if(c == sf::Color::Red)
                    c = sf::Color::Green;
                else if(c == sf::Color::Green)
                    c = sf::Color::Blue;
                else if(c == sf::Color::Blue)
                    c = sf::Color::Magenta;
                else
                    c = sf::Color(255, 105, 180);
            }

            //Clear(c);
            Clear();

            // Draw the ship AND THE PARTICLE
            Draw(*testShip);
            Draw(*p);

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
