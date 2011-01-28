/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-01-28
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <string> //For strings
#include <map> //For mapping objects
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp> //Graphics and everything above
#include <SFML/Audio.hpp> //hurr durr

#include "window.h" //Class def
#include "imagehandler.h" //For loading images
#include "audiohandler.h" //For loading and playing sound and music
#include "eventhandler.h" //Event handling
#include "particlesystem.h" //Particle system
#include "ship.h"
//#include "player.h"
#include "panel.h"
#include "logger.h"

namespace sbe
{
    Window::Window(sf::VideoMode Mode, const std::string& Title, const bool& showIntro, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, Title, WindowStyle, Params), res(Mode.Width, Mode.Height), pause(false), cCount(0)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        Logger::writeMsg(1) << "\nWindow loaded!";
        RenderWindow::Window::SetFramerateLimit(60);

        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        evtHandler = new EventHandler();
        Logger::writeMsg(1) << "Handlers loaded!";

        //mainMenu = new sbe::Panel();
        //Logger::writeMsg(1) << "Main menu loaded.";

        //ships = new std::map<std::string, Ship>;
        //ship
        Logger::writeMsg(1) << "Objects loaded!";

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
        delete testPanel;
        unloadFonts();
    }

    int Window::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */
        imgHandler->loadAssets("scripts/assets/images.ast");
        audHandler->loadSound("scripts/assets/sound.ast");
        audHandler->loadMusic("scripts/assets/music.ast");
        loadFonts("scripts/assets/fonts.ast");

        //Test stuff with a really kawaii ship AND A PARTICLE
        sf::Image img = imgHandler->getImage("testShip");
        sf::Image img2 = imgHandler->getImage("kawaiiShip");
        sf::Image img3 = imgHandler->getImage("smoke_01");

        testShip = new sbe::Ship(img);

        //*ships["testShip"] = *testShip;
        testShip->SetPosition(0.f, 0.f);
        testShip->SetScale(0.5, 0.5);

        testPanel = new sbe::Panel(sf::Vector2f(20, 600), sf::Vector2f(800, 750), sf::Color(50, 80, 80, 126), 1, sf::Color::White);
        testPanel->createString("testString", "hello i am a panel", fonts["inconsolata"], 24, sf::Vector2f(30, 610));
        testPanel->createButton("testButton", this, buttonClickedWrapper, sf::String("click", fonts["inconsolata"], 20), sf::Color(200, 200, 200, 255), sf::Vector2f(40, 710), sf::Vector2f(100, 740), sf::Color(80, 50, 80, 126));

        sf::Shape shot = sf::Shape::Line(0.f, 0.f, 0.f, 1000.f, 2.f, sf::Color::Yellow);
        sf::Shape shot2 = shot;
        shot2.SetColor(sf::Color::Yellow);

        int counter = 0;
        bool gun = true;
        int gunPosX = 0;

        sf::Sound laser(audHandler->getSound("laser"));

        sbe::Music loli;
        loli.OpenFromFile(audHandler->getMusic("loli2"));
        loli.Play();
        //Test particle system
        sbe::ParticleSystem *pSystem1 = new ParticleSystem("scripts/particles/particle_test.ast", imgHandler);
        pSystem1->SetPosition(500.f, 300.f);

        sf::String fps("0", fonts["inconsolata"], 20);
        fps.SetPosition(10, 10);
        fps.SetColor(sf::Color::White);
        std::stringstream fpsStr;

        while(IsOpened())
        {
            Logger::write();

            sf::Event event;
            while(GetEvent(event))
            {
                EventHandler::returnEvents(event, events);

                if (event.Type == sf::Event::Closed)
                    Close();
                if (events["Escape"])
                    Close();
                if (events["P"])
                {
                    if(loli.GetStatus() != sf::Music::Playing)
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

                if(event.Type == sf::Event::MouseButtonReleased)
                {
                    testPanel->click(sf::Vector2i(GetInput().GetMouseX(), GetInput().GetMouseY()));
                }

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

            //Particle system update test
            pSystem1->update(ElapsedTime);

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

                fpsStr << "fps: " << (int) ((1.f / ElapsedTime));
                fps.SetText(fpsStr.str());
                fpsStr.str("");
            }

            //Clear(c);
            Clear();

            // Draw stuff
            Draw(*testShip);
            Draw(*pSystem1);
            Draw(fps);
            Draw(*testPanel);

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

    void Window::loadFonts(const std::string& fontFile)
    {
        Logger::writeMsg(1) << "\nLoading assets from: \"" << fontFile << "\"...";
        //Open specified file
        fileReader.open(fontFile.c_str());
        if(!fileReader)
        {
            //Debug output
            Logger::writeMsg(1) << "The font handler was unable to open the specified asset file";
            return;
        }
        //Saving vars
        std::string output;
        std::string fontKey;
        std::string fontPath;

        while(getline(fileReader,output))
        {
            //Check if line is empty and perform string operation

            if(strReadLine(output, fontKey, fontPath))
            {
                //Search fonts
                if(fonts.find(fontKey) != fonts.end())
                    Logger::writeMsg(1) << "Failed to load font \"" << fontPath << "\". Reason: Font key already in system";
                else
                {
                    sf::Font fnt;
                    //Load font file
                    if(!fnt.LoadFromFile(fontPath))
                        Logger::writeMsg(1) << "Failed to load font \"" << fontPath << "\". Reason: Unable to open image file";
                    else
                    {
                        //Add to fonts
                        fonts[fontKey] = fnt;
                        //Debug output
                        Logger::writeMsg(1) << "Loaded font \"" << fontKey << "\" with filepath \"" << fontPath << "\"";;
                    }
                }
            }
        }

        //Debug output
        Logger::writeMsg(1) << "Finished loading fonts from \"" << fontFile << "\"";
        //Close file
        fileReader.close();
    }

    void Window::buttonClickedWrapper(void* object, const sf::Unicode::Text& text)
    {
        /*
            Purpose: Wrapper to callback function.
        */
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->buttonClicked(text);
    }

    void Window::buttonClicked(const sf::Unicode::Text& text)
    {
        testPanel->getString("testString").SetText(text);
    }
}
