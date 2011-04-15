/*
/ The main function
/ Authors: Victor Rådmark, Felix Westin, Jonathan Orrö
/ File created: 2010-11-14
/ File updated: 2011-02-18
/ License: GPLv3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "graphics/window.h"
#include "sys/configreader.h"
#include "sys/logger.h"
#include "sys/util.h"

int main()
{
    //Boot message
    sbe::Logger::setLevel(1);
    sbe::Logger::writeMsg(1) << " --- Shmup Base Engine version 0.x --- ";
    sbe::Logger::write();

    //Create the config reader
    sbe::ConfigReader *cfgReader = new sbe::ConfigReader();
    sbe::Logger::init(cfgReader->getSetting<int>("log"));
    sbe::Window *mainWindow;
    int respawn = 0;

    do
    {
        respawn = 0;
        //Create the main window
        if(cfgReader->getSetting<int>("fullscreen"))
            mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader, respawn, sf::Style::Fullscreen);
        else
            mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader, respawn);

        respawn = mainWindow->exec();

        safeDelete(mainWindow);
    }while(respawn != 0); //While the mainWindow wants to respawn

    sbe::Logger::close();

    delete cfgReader;

    return 0;
}
