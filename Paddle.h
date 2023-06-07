#pragma once

#include <SFML/Graphics.hpp>
#include "ElementType.h"


namespace sfAkitsu
{
    class Paddle {
    public:
        Paddle(int buff);

        void setPosition(sf::Vector2f position);
        void setVelocity(sf::Vector2f velocity);
        void setSize(sf::Vector2f size);
        void setColor(sf::Color color);

        sf::Vector2f getPosition() const;
        sf::Vector2f getVelocity() const;
        sf::Vector2f getSize() const;
        sf::FloatRect getBounds() const;
        ElementType getElementType() const;
        void setElementType(ElementType elementType);

        void move(sf::Vector2f offset);
        void handleInput();
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


    private:
        sf::RectangleShape mShape;
        sf::Vector2f mVelocity;
        ElementType mElementType;
        int mbuff;
        sf::Clock buffTimer;
    };
}
