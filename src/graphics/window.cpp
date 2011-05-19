/*
/ The rendering window class
/ Author: Victor Rådmark
/ File created: 2010-11-14
/ File updated: 2011-05-19
/ License: GPLv3
*/
#include <string> //For strings
#include <map> //For mapping objects
#include <cstdlib>
#include <list> //For lists

#include <SFML/Graphics.hpp> //Graphics and everything above
#include <SFML/Audio.hpp> //hurr durr

#include "../sys/logger.h"
#include "../sys/util.h"
#include "../sys/eventhandler.h" //Event handling
#include "../sys/configreader.h" //Loads settings
#include "../audio/audiohandler.h" //For loading and playing sound and music
#include "../gui/gui.h"
#include "../game/entity.h"
#include "../game/ship.h"
//#include "../game/player.h"
#include "../game/weapon.h"
#include "drawable.h"
#include "imagehandler.h" //For loading images
#include "particlesystem.h" //Particle system
#include "window.h" //Class def

namespace sbe
{
    Window::Window(sf::VideoMode Mode, ConfigReader* reader, int r, unsigned long WindowStyle, const sf::WindowSettings& Params)
        : RenderWindow(Mode, reader->getSetting<std::string>("title"), WindowStyle, Params), res(reader->getRes()), respawn(0), pause(false)
    {
        /*
            Purpose: Constructor for sbe::Window.
        */
        bool respawned = false;
        if(r == 1) respawned = true;
        cfgReader = reader;
        SetFramerateLimit(cfgReader->getSetting<int>("limit_fps"));
        UseVerticalSync(cfgReader->getSetting<int>("vsync"));
        menu = cfgReader->getSetting<int>("show_menu");
        Logger::writeMsg(1) << "\nWindow loaded!";

        imgHandler = new ImageHandler();
        audHandler = new AudioHandler();
        enmHandler = new EnemyHandler(imgHandler, cfgReader);
        prcHandler = new ParticleHandler(cfgReader, imgHandler);
        audHandler->setMusicVol(cfgReader->getSetting<short>("music_volume"));
        audHandler->setSFXVol(cfgReader->getSetting<short>("sfx_volume"));
        evtHandler = new EventHandler();
        evtHandler->addAction("Console", sf::Key::Tab, this, console);
        gui = new Gui("scripts/assets/fonts.ast", res, this, exit);
        Logger::writeMsg(1) << "Handlers loaded!";

        imgHandler->loadAssets("scripts/assets/system_images.ast");
        Logger::writeMsg(1) << "\nAssets loaded!";
        testShip = NULL;
        pSystem2 = NULL;
        wpn1 = NULL;
        loli = NULL;
        scroll = NULL;
        enm1 = NULL;
        stage = NULL;

        text1 = new Movable(imgHandler->getImage("text_getready"));
        text1->SetCenter(text1->GetSize().x / 2, text1->GetSize().y / 2);
        text1->SetScale(20, 20);

        text2 = new Movable(imgHandler->getImage("text_go"));
        text2->SetCenter(text2->GetSize().x / 2, text2->GetSize().y / 2);
        text2->SetScale(20, 20);

        text1->SetPosition(cfgReader->getRes().x / 2, cfgReader->getRes().y / 2);
        text2->SetPosition(cfgReader->getRes().x / 2, cfgReader->getRes().y / 2);
        text2->SetAlpha(0);

        !respawned ? gui->createMainMenu(this, select, options, hiscore, credits, exit, "scripts/particles/menu/mainmenu.ast", imgHandler, cfgReader, res) : gui->createOptionsMenu(this, apply, back, "scripts/particles/menu/options.ast", imgHandler, cfgReader, res);
        renderList.push_back(gui);
        displayText = false;
    }

    Window::~Window()
    {
        /*
            Purpose: Deconstructor for sbe::Window
        */
        renderList.clear();
        delete imgHandler;
        delete audHandler;
        delete enmHandler;
        delete evtHandler;
        delete prcHandler;
        safeDelete(gui);
        safeDelete(testShip);
        safeDelete(enm1);
        safeDelete(stage);
        safeDelete(pSystem2);
        safeDelete(wpn1);
        safeDelete(loli);
    }

    int Window::exec()
    {
        /*
            Purpose: Main game loop, IsOpened with a nicer name basically
        */


        while(IsOpened())
        {
            Logger::write();

            if(displayText)
            {
                if(text1->GetScale().x > 1)
                    text1->SetScale(text1->GetScale().x * 0.9, text1->GetScale().y * 0.9);
                else if(text1->GetAlpha() > 0)
                    text1->SetAlpha(text1->GetAlpha() - 6);
                else if(text2->GetScale().x > 1)
                {
                    text2->SetAlpha(255);
                    text2->SetScale(text2->GetScale().x * 0.9, text2->GetScale().y * 0.9);
                }
                else if(text2->GetAlpha() > 0)
                    text2->SetAlpha(text2->GetAlpha() - 5);
            }

            sf::Event event;
            while(GetEvent(event))
            {
                evtHandler->processEvents(event, gui->consoleShown());

                if (event.Type == sf::Event::Closed)
                    Close();
                if(event.Type == sf::Event::MouseButtonReleased)
                    gui->click(sf::Vector2i(GetInput().GetMouseX(), GetInput().GetMouseY()));
                if(event.Type == sf::Event::TextEntered)
                    gui->type(event);
            }

            if(!gui->consoleShown()) evtHandler->processInput(GetInput());

            gui->hover(sf::Vector2i(GetInput().GetMouseX(), GetInput().GetMouseY()));

            if(pSystem2 != NULL && !pause) pSystem2->SetPosition(testShip->GetPosition().x + testShip->GetSize().x / 2, testShip->GetPosition().y + testShip->GetSize().y / 2);
            if(wpn1 != NULL && !pause) wpn1->SetPosition(testShip->GetPosition().x + testShip->GetSize().x / 2, testShip->GetPosition().y + testShip->GetSize().y / 2);

            //Get elapsed time since last frame to ensure constant speed
            float ElapsedTime = GetFrameTime();

            if(wpn1 != NULL)
            {
                int projectileSize = wpn1->projectileSize();
                int enemyListSize = enmHandler->enemyListSize();
                for(int i=0; i<projectileSize; i++)
                {
                    for(int n=0; n<enemyListSize; n++)
                    {
                        if((enmHandler->enemyRadius(n) + wpn1->projectileRadius(i)) >= sqrt(pow((enmHandler->enemyXpos(n) - wpn1->projectileXpos(i)),2) + pow((enmHandler->enemyYpos(n) - wpn1->projectileYpos(i)),2)))
                        {
                            Logger::writeMsg(1) << "Hit";

                            int hit = enmHandler->hitEnemy(n);
                            if(hit != -1)
                            {
                                wpn1->removeProjectile(i);
                                if(hit == 0) gui->increaseScore();
                            }
                        }
                    }
                }
            }

            if(testShip != NULL && !testShip->readyToDie())
            {
                int enemyListSize = enmHandler->enemyListSize();

                for(int i = 0; i < enemyListSize; i++)
                {
                    if((enmHandler->enemyRadius(i) + testShip->returnRadius()) >= sqrt(pow((enmHandler->enemyXpos(i) - testShip->GetPosition().x),2) + pow((enmHandler->enemyYpos(i) - testShip->GetPosition().y), 2)))
                    {
                        Clear(sf::Color(0, 0, 0, 100));
                        /*sf::String gameOver("Game Over", gui->getFont("consolas"), 40);
                        gameOver.SetPosition(res.x / 2, res.y / 2);
                        gameOver.SetColor(sf::Color(225, 200, 200, 255));
                        Draw(gameOver);*/
                        audHandler->stopMusic();
                        sf::Sleep(1.f);
                        return 2;
                    }
                }
            }

            //Update everything
            for(RenderList::iterator it = renderList.begin(); it != renderList.end(); it++)
                if(!pause) (*it)->update(ElapsedTime);
            audHandler->update(ElapsedTime);

            if(testShip != NULL)
            {
                if(testShip->GetPosition().x < -10) testShip->SetPosition(-10, testShip->GetPosition().y);
                if(testShip->GetPosition().x > (res.x - 100)) testShip->SetPosition(res.x - 100, testShip->GetPosition().y);
                if(testShip->GetPosition().y < 0) testShip->SetPosition(testShip->GetPosition().x, 0);
                if(testShip->GetPosition().y > (res.y - 105)) testShip->SetPosition(testShip->GetPosition().x, res.y - 105);
            }
            Clear();

            // Draw stuff
            for(RenderList::const_iterator it = renderList.begin(); it != renderList.end(); it++)
                if((*it) != NULL) Draw(**it);

            // Update the window
            Display();
        }

        return respawn;
    }

    void Window::select(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showSelect();
    }

    void Window::load(void* object, const std::string& map)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->loadStuff(map);
    }

    void Window::options(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showOptions();
    }

    void Window::hiscore(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showHiScore();
    }

    void Window::credits(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->showCredits();
    }

    void Window::exit(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->Close();
    }

    void Window::apply(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->applyOptions();
    }

    void Window::back(void* object)
    {
        //Explicitly cast to a pointer to Windowk
        Window* self = (Window*) object;

        //Call member
        self->goBack();
    }

    void Window::console(void* object)
    {
        //Explicitly cast to a pointer to Windowk
        Window* self = (Window*) object;

        //Call member
        self->showConsole();
    }

    void Window::pauseG(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->pauseGame();
    }

    void Window::flyR(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::RIGHT);
    }

    void Window::flyL(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::LEFT);
    }

    void Window::flyU(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::UP);
    }

    void Window::flyD(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->flyShip(Ship::DOWN);
    }

    void Window::startFire(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->shipFire();
    }

    void Window::stopFire(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->shipFire(0);
    }

    void Window::defShipMod(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->setShipMod(1);
    }

    void Window::othShipMod(void* object)
    {
        //Explicitly cast to a pointer to Window
        Window* self = (Window*) object;

        //Call member
        self->setShipMod();
    }

    void Window::showOptions()
    {
        gui->deleteMainMenu();
        gui->createOptionsMenu(this, apply, back, "scripts/particles/menu/options.ast", imgHandler, cfgReader, res, gui->getPSPos(), gui->getNextPSPos());
    }

    void Window::showSelect()
    {
        gui->deleteMainMenu();
        gui->createSelectMenu(this, load, back, cfgReader, res);
    }

    void Window::applyOptions()
    {
        respawn = 1;
        Close();
    }

    void Window::goBack()
    {
        gui->deleteOptionsMenu();
        gui->deleteSelectMenu();
        gui->createMainMenu(this, select, options, hiscore, credits, exit, "scripts/particles/menu/mainmenu.ast", imgHandler, cfgReader, res, gui->getPSPos(), gui->getNextPSPos());
    }

    void Window::pauseGame()
    {
        pause = !pause;
        audHandler->pauseMusic();
        gui->pause();
    }

    void Window::loadStuff(const std::string& map)
    {

        menu = false;
        gui->deleteSelectMenu();
        renderList.pop_back();

        std::string mapStr = "scripts/maps/" + map;
        stage = new Stage(cfgReader, imgHandler, audHandler, enmHandler, prcHandler, mapStr);
        enmHandler->loadSound(audHandler);

        //Custom stuff for each map, durr
        if(map.compare("test_map.ast") == 0)
        {
            displayText = true;

            testShip = new sbe::Ship("player_s", imgHandler, "explosion_01");
            testShip->SetPosition(75, cfgReader->getRes().y / 2 - testShip->GetSize().y / 2);
            testShip->SetScale(1.5,1.5);
            testShip->SetRotation(0);

            pSystem2 = new ParticleSystem("scripts/particles/plasma_blast.ast", imgHandler, cfgReader->getSetting<float>("ps_reload"));
            wpn1 = new Weapon("scripts/weapons/test_wpn.ast", imgHandler, cfgReader, audHandler);

            std::vector<std::string> diag;
            diag.push_back("In my restless dreams, I see that town...");
            diag.push_back("Silent Hill");
            diag.push_back("You promised you'd take me there again some day. But you never did.");
            diag.push_back("Well I'm alone now... In our 'special place'...");
            diag.push_back("Waiting for you...");
            gui->createDialogPanel(res, diag);
        }

        renderList.push_back(stage);
        renderList.push_back(testShip);
        renderList.push_back(wpn1);
        if(map == "test_map.ast") renderList.push_back(pSystem2);
        renderList.push_back(testShip);
        renderList.push_back(text1);
        renderList.push_back(text2);
        renderList.push_back(gui);

        evtHandler->addAction("Pause", sf::Key::P, this, pauseG);

        evtHandler->addInputAction("Mod", sf::Key::LShift, this, othShipMod, defShipMod);
        evtHandler->addInputAction("Right", sf::Key::Right, this, flyR);
        evtHandler->addInputAction("Left", sf::Key::Left, this, flyL);
        evtHandler->addInputAction("Up", sf::Key::Up, this, flyU);
        evtHandler->addInputAction("Down", sf::Key::Down, this, flyD);
        evtHandler->addInputAction("Fire", sf::Key::Space, this, startFire, stopFire);
    }
}
