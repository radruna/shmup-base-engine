/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-02-11
/ License: GPLv3
*/
#include <iostream> //Debug output
#include <string> //For strings
#include <map> //For mapping objects
#include <cstdlib>
#include <sstream>
#include <list> //For lists

#include <SFML/Graphics.hpp> //Graphics and everything above
#include <SFML/Audio.hpp> //hurr durr

#include "window.h" //Class def
#include "imagehandler.h" //For loading images
#include "audiohandler.h" //For loading and playing sound and music
#include "eventhandler.h" //Event handling
#include "configreader.h" //Loads settings
#include "particlesystem.h" //Particle systemsf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y)
#include "ship.h"
#include "projectile.h"
//#include "player.h"
#include "panel.h"
#include "dialogpanel.h"
#include "logger.h"

namespace sbe
{
    Window::Window(sf::VideoMode Mode, ConfigReader* reader, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, reader->getSetting<std::string>("title"), WindowStyle, Params), res(Mode.Width, Mode.Height), pause(false), count(0)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        cfgReader = reader;
        SetFramerateLimit(cfgReader->getSetting<int>("limit_fps"));
        UseVerticalSync(cfgReader->getSetting<bool>("vsync"));
        Logger::writeMsg(1) << "\nWindow loaded!";

        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        audHandler->setMusicVol(cfgReader->getSetting<short>("music_volume"));
        audHandler->setSFXVol(cfgReader->getSetting<short>("sfx_volume"));
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
        imgHandler->loadAssets("scripts/assets/system_images.ast");
        imgHandler->loadAssets("scripts/assets/images.ast");
        audHandler->loadSound("scripts/assets/sound.ast");
        audHandler->loadMusic("scripts/assets/music.ast");
        loadFonts("scripts/assets/fonts.ast");

        testShip = new sbe::Ship("testShip", imgHandler);

        //*ships["testShip"] = *testShip;
        testShip->SetPosition(0.f, 0.f);
        testShip->SetScale(0.5, 0.5);
        testShip->SetAlpha(0);

        std::vector<std::string> diag;
        diag.push_back("OHAYO");
        diag.push_back("Sugoi sugoi!");
        diag.push_back("VN of the year all years");
        testPanel = new sbe::DialogPanel(res, diag, fonts["inconsolata"]);

        sf::Shape shot = sf::Shape::Line(0.f, 0.f, 0.f, 1000.f, 2.f, sf::Color::Yellow);
        sf::Shape shot2 = shot;
        shot2.SetColor(sf::Color::Yellow);

        int counter = 0;
        bool gun = true;
        int gunPosX = 0;

        sf::Sound laser(audHandler->getSound("laser"));

        sbe::Music loli;
        loli.OpenFromFile(audHandler->getMusic("loli2"));
        loli.SetVolume(audHandler->getMusicVol());
        loli.Play();
        //Test particle system
        sbe::ParticleSystem *pSystem1 = new ParticleSystem("scripts/particles/explosion/explosion1.ast", imgHandler, cfgReader->getSetting<float>("ps_reload"));
        sbe::ParticleSystem *pSystem2 = new ParticleSystem("scripts/particles/plasma_blast.ast", imgHandler, cfgReader->getSetting<float>("ps_reload"));
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
                    testShip->setImage("kawaiiShip");

                    //audHandler->setMusic("8bitloli");
                    loli.Stop();
                    loli.OpenFromFile(audHandler->getMusic("8bitloli"));
                    loli.Play();
                }
                if (events["L"])
                    testShip->SetPosition(res.x / 2, res.y / 2);

                if(events["R"])
                {   //Reload particle systems
                    pSystem1->reload();
                    pSystem2->reload();
                }

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
            pSystem2->SetPosition(testShip->GetPosition().x + testShip->GetSize().x / 2, testShip->GetPosition().y + testShip->GetSize().y / 2);

            //Particle system update test
            pSystem1->update(ElapsedTime);
            pSystem2->update(ElapsedTime);

            //TODO (Liag#5#) Add lasers and stuff to the Ship class.
            if(GetInput().IsKeyDown(sf::Key::Space) && counter < 2)
            {
                counter = 10;

                //projectileList.push_back(Projectile("/scripts/shots/shot_01.ast", imgHandler));

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
                //laser.Play();

            }
            else if(counter < 40)
            {
                shot.Move(0, (-2000 * ElapsedTime));
            }

            // Clear screen
            if(count++ % 4 == 0)
            {
                fpsStr << "fps: " << (int) ((1.f / ElapsedTime));
                fps.SetText(fpsStr.str());
                fpsStr.str("");

            }

            //Clear(c);
            Clear();

            // Draw stuff
            Draw(*testShip);
            Draw(*pSystem1);
            Draw(*pSystem2);
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
}
