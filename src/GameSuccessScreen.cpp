#include "../GameSuccessScreen.h"
#include "../Game.h"
#include "../MenuScreen.h"

using namespace sfAkitsu;

GameSuccessScreen::GameSuccessScreen(float time,int MaxComb) 
{
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    mText.setFont(mFont);
    std::string text = "You win! Your time was " + std::to_string(time) + " seconds.";
    text+= "\nMax Comb: " + std::to_string(MaxComb) + "\nPress Enter to return to menu\nPress Escape to quit";
    mText.setString(text);
    mText.setPosition(400 - mText.getLocalBounds().width / 2, 300 - mText.getLocalBounds().height / 2);
}

void GameSuccessScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        // Go to game screen
        Game::Screen = std::make_shared<MenuScreen>();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        // exit game
        window.close();
    }
}

void GameSuccessScreen::update(sf::Time delta)
{
}

void GameSuccessScreen::render(sf::RenderWindow& window)
{
    window.draw(mText);
}
