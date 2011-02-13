/*
/ The main function
/ Authors: Victor Rådmark, Felix Westin, Jonathan Orrö
/ File created: 2010-11-14
/ File updated: 2011-02-13
/ License: GPLv3
*/
#include <string>

#include <SFML/Graphics.hpp>

#include "window.h"
#include "configreader.h"
#include "logger.h"

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

    //Create the main window
    if(cfgReader->getSetting<int>("fullscreen"))
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader, sf::Style::Fullscreen);
    else
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader);

    mainWindow->exec();

    delete mainWindow;

    sbe::Logger::close();

    return 0;
}
