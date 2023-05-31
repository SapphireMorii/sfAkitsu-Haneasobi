#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <memory>
#include <vector>

#include "Screen.h"

namespace sfAkitsu
{    
    class Game
    {
        public:
            Game();

            void run();

            void handleInput();
            void update(sf::Time deltaTime);
            void render();

            static const int Width = 800;
            static const int Height = 600;

            static std::shared_ptr<Screen> Screen;

        private:
            sf::RenderWindow mWindow;
            sf::Music mbgMusic;

            static const sf::Time TimePerFrame_;
    };
}