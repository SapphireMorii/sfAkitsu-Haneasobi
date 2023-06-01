#include "../Bullet.h"

using namespace sfAkitsu;

Bullet::Bullet(sf::Vector2f position)
{
    mVelocity = sf::Vector2f(0.0f, -300.0f);
    mShape.setRadius(2.0f);
    mShape.setOrigin(mShape.getRadius(), mShape.getRadius());
    mShape.setFillColor(sf::Color::Yellow);
    setPosition(position);
    ishit = false;
    isLanched = false;
}

void Bullet::setPosition(sf::Vector2f position)
{
    mShape.setPosition(position);
}

void Bullet::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Bullet::setRadius(float radius)
{
    mShape.setRadius(radius);
    mShape.setOrigin(mShape.getRadius(), mShape.getRadius());
}

void Bullet::setColor(sf::Color color)
{
    mShape.setFillColor(color);
}

void Bullet::move(sf::Vector2f offset)
{
    mShape.move(offset);
}

void Bullet::update(sf::Time deltaTime)
{
    move(mVelocity * deltaTime.asSeconds());
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mShape, states);
}

sf::Vector2f Bullet::getPosition() const
{
    return mShape.getPosition();
}

sf::Vector2f Bullet::getVelocity() const
{
    return mVelocity;
}

float Bullet::getRadius() const
{
    return mShape.getRadius();
}

sf::FloatRect Bullet::getBounds() const
{
    return mShape.getGlobalBounds();
}

bool Bullet::checkBrickCollision(Brick& brick)
{
    if(getBounds().intersects(brick.getBounds()))
    {
        printf("Brick health: %d\n", brick.getHealth());
        brick.setHealth(brick.getHealth() - 1);
        printf("Brick health: %d\n", brick.getHealth());
        return true;
    }
    return false;
}

bool Bullet::getIshit() const
{
    return ishit;
}

void Bullet::setIshit(bool ishit)
{
    this->ishit = ishit;
}

bool Bullet::getIsLanched() const
{
    return isLanched;
}

void Bullet::setIsLanched(bool isLanched)
{
    this->isLanched = isLanched;
}

bool Bullet::getLeftOrright() const
{
    return leftOrright;
}

void Bullet::setLeftOrright(bool leftOrright)
{
    this->leftOrright = leftOrright;
}