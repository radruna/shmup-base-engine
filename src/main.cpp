/*
/ The main function
/ Authors: Victor Rådmark, Felix Westin, Jonathan Orrö
/ File created: 2010-11-14
/ File updated: 2010-11-16
/ License: GPLv3
*/
#include <SFML/Graphics.hpp>

#include "window.h"

int main()
{
    // Create the main mainWindow
    sbe::Window mainWindow(sf::VideoMode(1024, 768), "SBE Window");

    return mainWindow.exec();
}
