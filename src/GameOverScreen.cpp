#include "../GameOverScreen.h"
#include "../Game.h"
#include "../MenuScreen.h"

using namespace sfAkitsu;

GameOverScreen::GameOverScreen(float time) :
    mFont(),
    mText()
{
    if (!mFont.loadFromFile("Fonts/85W.ttf"))
    {
        // Error loading font
        printf("GameOverScreen: Error loading font\n");
    }
    mText.setFont(mFont);
    mText.setString("Game Over\nTime: " + std::to_string(time) + "\nPress Enter to return to menu\nPress Escape to quit");
    mText.setCharacterSize(24);
    mText.setFillColor(sf::Color::Red);
    mText.setPosition(100.f, 100.f);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        // Go to game screen
        Game::Screen = std::make_shared<MenuScreen>();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        // Go to game screen
        window.close();
    }
}

void GameOverScreen::update(sf::Time delta)
{
}

void GameOverScreen::render(sf::RenderWindow& window)
{
    window.draw(mText);
}