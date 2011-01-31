/*
/ Dialog panels, for dialogue.
/ Author: Victor Rådmark
/ Created: 2011-01-31
/ Updated: 2011-01-31
/ License: GPL v3
*/
#ifndef DIALOGPANEL_H_INCLUDED
#define DIALOGPANEL_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "panel.h"

namespace sbe
{
    class DialogPanel : public sbe::Panel
    {
        public:
            DialogPanel(const sf::Vector2i& res, const sf::Color& color = sf::Color(50, 80, 80, 126), const float& outline = 1, const sf::Color& outlineColor = sf::Color::White);
            ~DialogPanel() {}
            //TODO(Liag#9#): Finish implementing dialogues.
            void createButton(const std::string& name,
                  const std::vector<std::string>& dialog,
                  const sf::Color& txtCol = sf::Color(200, 200, 220, 255),
                  const sf::Color& color = sf::Color(80, 50, 80, 126),
                  const float& outline = 1,
                  const sf::Color& outlineColor = sf::Color(200, 200, 220, 255));
        private:
            void next();
    };
}

#endif
