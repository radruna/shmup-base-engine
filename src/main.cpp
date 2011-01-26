/*
/ The main function
/ Authors: Victor Rådmark, Felix Westin, Jonathan Orrö
/ File created: 2010-11-14
/ File updated: 2010-01-25
/ License: GPLv3
*/
#include <SFML/Graphics.hpp>

#include "window.h"
#include "configreader.h"

int main()
{
    //Boot message
    std::cout << " --- Shmup Base Engine version 0.x --- " << std::endl;

    //Create the config reader
    sbe::ConfigReader *cfgReader = new sbe::ConfigReader();

    sbe::Window *mainWindow;

    //Create the main window
    if(cfgReader->getFS())
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader->getTitle(), true, sf::Style::Fullscreen);
    else
        mainWindow = new sbe::Window(sf::VideoMode(cfgReader->getRes().x, cfgReader->getRes().y), cfgReader->getTitle(), true);


    mainWindow->exec();

    delete mainWindow;

    return 0;
}
