#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screen.h"

namespace sfAkitsu
{
    class GameOverScreen : public Screen
    {
    public:
        GameOverScreen(float time, int MaxComb);

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font mFont;
        sf::Text mText;
    };
}
