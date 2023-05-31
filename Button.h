#pragma once

#include <functional>
#include <SFML/Graphics.hpp>

namespace sfAkitsu
{
    class Button : public sf::Drawable {
    public:
        Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
        void setCallback(std::function<void()> callback);
        void handleInput(sf::Window& window);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::RectangleShape mBackground;
        sf::Text mText;
        std::function<void()> mCallback;
    };
}

