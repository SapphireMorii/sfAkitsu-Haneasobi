#include <memory>

#include "../GameScreen.h"
#include "../MenuScreen.h"
#include "../Game.h"

using namespace sfAkitsu;

MenuScreen::MenuScreen()
{
    mFont.loadFromFile("Fonts/85W.ttf");
    mText.setFont(mFont);
    Button startButton(mFont, "Start", sf::Vector2f(400, 300), sf::Vector2f(100, 50));
    startButton.setCallback([]() {
        Game::Screen = std::make_shared<GameScreen>();
    });
    mButtons.push_back(startButton);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    Game::Screen = std::make_shared<GameScreen>();
    for (auto& button : mButtons) {
        button.handleInput(window);
    }
}

void MenuScreen::update(sf::Time delta)
{

}

void MenuScreen::render(sf::RenderWindow& window)
{
    for (auto& button : mButtons) {
        window.draw(button);
    }
}



