#include "../LevelSelectScreen.h"
#include "../GameScreen.h"
#include "../Game.h"
#include "../Button.h"
#include "../MenuScreen.h"


using namespace sfAkitsu;

LevelSelectScreen::LevelSelectScreen()
{
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    mText.setFont(mFont);
    //选择关卡标题
    mText.setString("Select Level");
    mText.setPosition(400 - mText.getLocalBounds().width / 2, 100 - mText.getLocalBounds().height / 2);
    //按钮
    Button Level1_Button(mFont, "Level 1", sf::Vector2f(350, 300), sf::Vector2f(100, 50));
    Button Level2_Button(mFont,"Level 2",sf::Vector2f(350,400),sf::Vector2f(100,50));
    Level1_Button.setCallback([]() {
        Game::Screen = std::make_shared<GameScreen>(1);
    });
    Level2_Button.setCallback([]() {
        Game::Screen = std::make_shared<GameScreen>(2);
    });
    mButtons.push_back(Level1_Button);
    mButtons.push_back(Level2_Button);
}

void LevelSelectScreen::handleInput(sf::RenderWindow& window)
{
    for (auto& button : mButtons) {
        button.handleInput(window);
    }
}

void LevelSelectScreen::update(sf::Time delta)
{

}

void LevelSelectScreen::render(sf::RenderWindow& window)
{
    window.draw(mText);
    for (auto& button : mButtons) {
        window.draw(button);
    }
}