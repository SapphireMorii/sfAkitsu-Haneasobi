#pragma once

#include <functional>
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace sfAkitsu
{
    class Button : public sf::Drawable {
    public:
        Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
        Button();
        void setCallback(std::function<void(sf::RenderWindow&)> callback);
        void handleInput(sf::RenderWindow& window);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        // int isClicked(sf::RenderWindow& window);
    private:
        sf::RectangleShape mBackground;
        sf::Text mText;
        std::function<void(sf::RenderWindow&)> mCallback;
        bool isValid;
    };
}

