#pragma once

#include <SFML/Graphics.hpp>
#include "Brick.h"

namespace sfAkitsu
{
    class Bullet
    {
        public:    
            Bullet(sf::Vector2f position);

            void setPosition(sf::Vector2f position);
            void setVelocity(sf::Vector2f velocity);
            void setRadius(float radius);
            void setColor(sf::Color color);

            void move(sf::Vector2f offset);
            void update(sf::Time deltaTime);
            void draw(sf::RenderTarget& target, sf::RenderStates states) const;

            sf::Vector2f getPosition() const;
            sf::Vector2f getVelocity() const;
            float getRadius() const;
            sf::FloatRect getBounds() const;

            bool checkBrickCollision(Brick& Brick);

            bool getIshit() const;
            void setIshit(bool ishit);

            bool getIsLanched() const;
            void setIsLanched(bool isLanched);

            bool getLeftOrright() const;
            void setLeftOrright(bool leftOrright);

        private:
            sf::CircleShape mShape;
            sf::Vector2f mPosition;
            sf::Vector2f mVelocity;
            bool ishit;
            bool isLanched;
            bool leftOrright;
    };
    
}