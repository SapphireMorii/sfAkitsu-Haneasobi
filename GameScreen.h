#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Screen.h"
#include "Brick.h"
#include "Ball.h"
#include "Paddle.h"

namespace sfAkitsu
{
    class GameScreen : public Screen
    {
    public:
        GameScreen();

        void handleInput(sf::RenderWindow& window) override;
        void update(sf::Time delta) override;
        void render(sf::RenderWindow& window) override;

    private:
        sf::Font mFont;
        sf::Text mText;
        int mycurrentLevel;
        int levelcount;
        sf::Clock mTimer;
        std::vector<Brick> mBricks;
        std::vector<Ball> mBalls;
        Paddle mPaddle;
        std::vector<sf::RectangleShape> mBorder;
    };
} 
