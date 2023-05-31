#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "ElementType.h"
#include "Brick.h"
#include "Paddle.h"

namespace sfAkitsu
{
class Ball {
    public:
        Ball(sf::Vector2f position, sf::Vector2f velocity, ElementType elementType);

        void setPosition(sf::Vector2f position);
        void setVelocity(sf::Vector2f velocity);
        void setRadius(float radius);
        void setColor(sf::Color color);

        sf::Vector2f getPosition() const;
        sf::Vector2f getVelocity() const;
        float getSpeed() const;
        float getRadius() const;
        sf::FloatRect getBounds() const;
        void launch(sf::Vector2f velocity);
        bool isLaunched() const;

        void move(sf::Vector2f offset);
        void update(sf::Time deltaTime);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        void CheckBrickCollision(Brick& brick);
        void CheckPaddleCollision(Paddle& paddle);

        ElementType getElementType() const;
        void setElementType(ElementType elementType);
        
    private:
        sf::CircleShape mShape;
        sf::Vector2f mPosition;
        sf::Color mColor;
        sf::Vector2f mVelocity;
        ElementType mElementType;
        bool islanuched;
        static std::map<std::pair<ElementType, ElementType>, ElementType> sElementReactions;
    };
} 

