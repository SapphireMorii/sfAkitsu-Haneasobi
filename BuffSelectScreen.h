#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "LevelSelectScreen.h"

namespace sfAkitsu
{
    class BuffSelectScreen : public Screen
    {
    public:
        BuffSelectScreen(int level);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font mFont;
        sf::Text mText;
        int level;
    };
}