#include "../Game.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include "../MenuScreen.h"

using namespace sfAkitsu;

const sf::Time Game::TimePerFrame_ = sf::seconds(1.f/120.f);

std::shared_ptr<Screen> Game::Screen = std::make_shared<MenuScreen>();

Game::Game():
    mWindow(sf::VideoMode(800,600),"Akitsu Haneasobi")
{
    // Set the window background color to white
    mWindow.clear();
}

void Game::handleInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
    Game::Screen->handleInput(mWindow);
}

void Game::update(sf::Time deltaTime)
{
    Game::Screen->update(deltaTime);
}

void Game::render()
{
    mWindow.clear();
    Game::Screen->render(mWindow);
    mWindow.display();
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while(timeSinceLastUpdate > Game::TimePerFrame_)
        {
            timeSinceLastUpdate -= TimePerFrame_;
            handleInput();
            update(TimePerFrame_);
        }
        render();
    }
}