#include "../BuffSelectScreen.h"
#include "../GameScreen.h"
#include "../LevelSelectScreen.h"
#include "../Screen.h"
#include "../Game.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace sfAkitsu;

BuffSelectScreen::BuffSelectScreen(int level):level(level)
{
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    std::string text = "            Buff Select Screen";
    text += "\nPress the number of the buff you want to select";
    text += "\n\n1.Split ball";
    text += "\n\n2.Speed up ball";
    text += "\n\n3.increase the board width";
    text += "\n\n4.Temporary wall";
    text += "\n\n5.Speed up board";

    mText.setFont(mFont);
    mText.setString(text);
    mText.setCharacterSize(24);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(100, 100);
}

void BuffSelectScreen::handleInput(sf::RenderWindow& window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<GameScreen>(level,1);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<GameScreen>(level,2);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<GameScreen>(level,3);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<GameScreen>(level,4);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<GameScreen>(level,5);
    }
}

void BuffSelectScreen::update(sf::Time delta)
{
    
}

void BuffSelectScreen::render(sf::RenderWindow& window)
{
    window.draw(mText);
}