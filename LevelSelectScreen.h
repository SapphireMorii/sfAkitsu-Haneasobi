#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfAkitsu
{
    class LevelSelectScreen : public Screen
    {
        private:
        sf::Font mFont;
        sf::Text mText;
        // std::vector<Button> mButtons;
        Button Button1;
        Button Button2;
        public:
        LevelSelectScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;
    };
}