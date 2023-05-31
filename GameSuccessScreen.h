#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Screen.h"

namespace sfAkitsu
{
    class GameSuccessScreen : public Screen
    {
        public:
            GameSuccessScreen(float time);

            void handleInput(sf::RenderWindow& window) override;
            void update(sf::Time delta) override;
            void render(sf::RenderWindow& window) override;
        
        private:
            sf::Font mFont;
            sf::Text mText;
    };
    
}