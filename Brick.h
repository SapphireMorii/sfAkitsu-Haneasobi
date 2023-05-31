#pragma once

#include <SFML/Graphics.hpp>
#include "ElementType.h"


namespace sfAkitsu
{
    class Brick {
    public:
        Brick(sf::Vector2f position,ElementType elementType);

        void setPosition(sf::Vector2f position);
        void setSize(sf::Vector2f size);
        void setColor(sf::Color color);

        sf::Vector2f getPosition() const;
        sf::Vector2f getSize() const;
        sf::FloatRect getBounds() const;

        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        ElementType getElementType() const;
        void setElementType(ElementType elementType);

        int getHealth() const;
        void setHealth(int health);
    private:
        sf::RectangleShape mShape;
        sf::Vector2f mpPosition;
        ElementType mElementType;
        int mHealth;
    };
}
