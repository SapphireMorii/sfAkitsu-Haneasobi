#pragma once

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"


namespace sfAkitsu
{
    class MenuScreen : public Screen
    {
    public:
        MenuScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font mFont;
        sf::Text mText;
        std::vector<Button> mButtons;
    };
}