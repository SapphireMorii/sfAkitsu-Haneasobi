#include "../Button.h"

using namespace sfAkitsu;

Button::Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size) {
    mBackground.setSize(size);
    mBackground.setFillColor(sf::Color::White);
    mBackground.setOutlineThickness(2.0f);
    mBackground.setOutlineColor(sf::Color::Black);
    mBackground.setPosition(position);

    mText.setFont(font);
    mText.setString(text);
    mText.setCharacterSize(20);
    mText.setFillColor(sf::Color::Black);
    mText.setOrigin(mText.getLocalBounds().width / 2.0f, mText.getLocalBounds().height / 2.0f);
    mText.setPosition(position + size / 2.0f);
}

void Button::setCallback(std::function<void()> callback) {
    mCallback = callback;
}

void Button::handleInput(sf::Window& window) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
        if(mBackground.getGlobalBounds().contains(mousePositionF)) {
            mCallback();
        }
    }
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mBackground, states);
    target.draw(mText, states);
}