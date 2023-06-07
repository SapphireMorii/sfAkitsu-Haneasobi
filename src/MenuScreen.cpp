#include <memory>

#include "../Button.h"
#include "../GameScreen.h"
#include "../MenuScreen.h"
#include "../Game.h"
#include "../LevelSelectScreen.h"

using namespace sfAkitsu;

MenuScreen::MenuScreen()
{
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    mText.setFont(mFont);
    mText.setString("Akitsu Haneasobi");
    mText.setCharacterSize(30);
    mText.setFillColor(sf::Color::White);
    mText.setPosition(275, 100);
    Button startButton(mFont, "Start", sf::Vector2f(350, 300), sf::Vector2f(100, 50));
    Button quitButton(mFont,"Quit",sf::Vector2f(350,400),sf::Vector2f(100,50));
    startButton.setCallback([](sf::RenderWindow& window) {
        window.clear();
        Game::Screen = std::make_shared<LevelSelectScreen>();
    });
    quitButton.setCallback([](sf::RenderWindow& window) {
        window.close();
    });
    mButtons.push_back(startButton);
    mButtons.push_back(quitButton);
}

void MenuScreen:: handleInput(sf::RenderWindow& window)
{
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    // {
    //     Game::Screen = std::make_shared<LevelSelectScreen>();
    // }
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    // {
    //     window.close();
    // }
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
    window.draw(mText);
}



