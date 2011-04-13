/*
/ Enemy handler class
/ Author: Niklas Andréasson, Jonathan Orrö
/ File created: 2011-03-18
/ File updated: 2011-03-18
/ License: GPLv3
*/
#ifndef ENEMYHANDLER_H_INCLUDED
#define ENEMYHANDLER_H_INCLUDED

#include <fstream>   //Read script files
#include <map> //Map for objects
#include <string>
#include <list>

#include <SFML/Graphics.hpp> //Sfml stuff

#include "../sys/filehandler.h" //Abstract base class


#include "../game/enemy.h"
#include "../game/path.h"



namespace sbe
{
    class EnemyHandler : public FileHandler
    {
        /*
            Loads images, stores them and handles requests
        */
        public:
            EnemyHandler(ImageHandler* iHandler, ConfigReader* cfgReader);
            ~EnemyHandler()
            {
                unloadAssets();
            }

            //Load images listed in the asset file
            void loadAssets(const std::string& assetFile);
            //Load a single image without the use of an asset file
            void loadAsset(const std::string& enemyKey,const std::string& filePath);
            //Unload all enemies
            void unloadAssets();
            void spawnEnemies(const std::string& type, const int& amount, const float& interval, const float& spacing, const float& offset, const int& side);
            //Handle image requests
            Enemy& getEnemy(const std::string& enemyKey);
            Path& getPath(const std::string& enemyKey);
        private:
            //Enemy list
            std::map<std::string, Enemy> enemyMap;
            //Path list
            std::map<std::string, Path> pathList;
            std::list<Enemy> enemyList;
            std::vector <Path::pathContent> pathContentList;
            sf::Vector2i res;
            sbe::Enemy enm1;
        protected:
            ImageHandler* imgHandler;
            void Render(sf::RenderTarget& Target) const;
    };
}

#endif
