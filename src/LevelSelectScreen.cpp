#include "../LevelSelectScreen.h"
#include "../GameScreen.h"
#include "../Game.h"
#include "../Button.h"
#include "../MenuScreen.h"
#include "../BuffSelectScreen.h"

using namespace sfAkitsu;

LevelSelectScreen::LevelSelectScreen()
{
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    mText.setFont(mFont);
    //选择关卡标题
    mText.setString("Select Level");
    mText.setPosition(400 - mText.getLocalBounds().width / 2, 100 - mText.getLocalBounds().height / 2);
    //按钮
    Button Level1_Button(mFont,"Level 1",sf::Vector2f(250,400),sf::Vector2f(100,50));
    Button Level2_Button(mFont,"Level 2",sf::Vector2f(450,400),sf::Vector2f(100,50));
    Level1_Button.setCallback([](sf::RenderWindow& window) {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<BuffSelectScreen>(1);
    });
    Level2_Button.setCallback([](sf::RenderWindow& window) {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<BuffSelectScreen>(2);
    });
    Button1 = Level1_Button;
    Button2 = Level2_Button;
    // mButtons.push_back(Level2_Button);
    // mButtons.push_back(Level1_Button);
}

void LevelSelectScreen::handleInput(sf::RenderWindow& window)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<MenuScreen>();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<BuffSelectScreen>(1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2))
    {
        window.clear();
        window.display();
        Game::Screen = std::make_shared<BuffSelectScreen>(2);
    }
    // for(auto& button : mButtons)
    // {
    //     button.handleInput(window);
    // }
    Button1.handleInput(window);
    Button2.handleInput(window);
}

void LevelSelectScreen::update(sf::Time delta)
{

}

void LevelSelectScreen::render(sf::RenderWindow& window)
{
    //选择关卡提示
    sf::Text selectLevelText;
    selectLevelText.setFont(mFont);
    selectLevelText.setString("Click button to select level");
    selectLevelText.setPosition(400 - selectLevelText.getLocalBounds().width / 2, 300 - selectLevelText.getLocalBounds().height / 2);
    window.draw(selectLevelText);
    //选择关卡标题
    window.draw(mText);
    // for (auto& button : mButtons) {
    //     window.draw(button);
    // }
    window.draw(Button1);
    window.draw(Button2);
}