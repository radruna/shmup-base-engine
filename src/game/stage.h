/*
/ Stage class
/ Author: Felix Westin
/ File created: 2011-03-14
/ File updated: 2011-03-15
/ License: GPLv3
*/
#ifndef STAGE_H_INCLUDED
#define STAGE_H_INCLUDED

#include <iostream> //Debug output
#include <sstream> //Test
#include <list> //For lists

#include <SFML/Graphics.hpp> //Sfml stuff
#include <vector>

#include "../graphics/drawable.h"
#include "../sys/filehandler.h" //Base class def
#include "../sys/configreader.h"
#include "../audio/audiohandler.h"
#include "../game/enemyhandler.h"   //Enemy handler
#include "../graphics/imagehandler.h"
#include "../graphics/particlehandler.h"
#include "../graphics/background.h" // Background

namespace sbe
{
    class Stage : public FileHandler , public sbe::Drawable
    {
        /*
            Stage class
        */
        public:
            Stage
            (
                ConfigReader* configReader,
                ImageHandler* imageHandler,
                AudioHandler* audioHandler,
                EnemyHandler* enemyHandler,
                ParticleHandler* particleHandler,
                const std::string& stageFile
            );
            ~Stage()
            {
            }
            void load();
            void update(const float& elapsed);
        private:
            std::string nextQuote(std::string& strSource);
            std::string stageFile;
            void Render(sf::RenderTarget& Target) const;
            AudioHandler *audHandler;
            ConfigReader *cfgReader;
            ImageHandler *imgHandler;
            EnemyHandler *enmHandler;
            ParticleHandler *prcHandler;
            sbe::Background *bg; // test
            std::vector <std::string> eventList;
            unsigned int eventPos;
            float eventCounter;

    };
}

#endif
