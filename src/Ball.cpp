#include "../Ball.h"
#include "../ElementType.h"
#include <math.h>

using namespace sfAkitsu;

std::map<std::pair<ElementType, ElementType>, ElementType> Ball::sElementReactions ={
    { {ElementType::Hydro, ElementType::Pyro}, ElementType::Vaporize },
    { {ElementType::Hydro, ElementType::Cryo}, ElementType::Frozen },
    { {ElementType::Hydro, ElementType::Electro}, ElementType::ElectroCharged },
    { {ElementType::Hydro, ElementType::Hydro}, ElementType::Hydro},
    { {ElementType::Pyro, ElementType::Hydro}, ElementType::Vaporize },
    { {ElementType::Pyro, ElementType::Cryo}, ElementType::Melt },
    { {ElementType::Pyro, ElementType::Electro}, ElementType::Overload },
    { {ElementType::Pyro, ElementType::Pyro}, ElementType::Pyro},
    { {ElementType::Cryo, ElementType::Hydro}, ElementType::Frozen },
    { {ElementType::Cryo, ElementType::Pyro}, ElementType::Melt },
    { {ElementType::Cryo, ElementType::Electro}, ElementType::Superconduct },
    { {ElementType::Cryo, ElementType::Cryo}, ElementType::Cryo},
    { {ElementType::Electro, ElementType::Hydro}, ElementType::ElectroCharged },
    { {ElementType::Electro, ElementType::Pyro}, ElementType::Overload },
    { {ElementType::Electro, ElementType::Cryo}, ElementType::Superconduct },
    { {ElementType::Electro, ElementType::Electro}, ElementType::Electro},
};

Ball::Ball(sf::Vector2f position, sf::Vector2f velocity, ElementType elementType) : mElementType(elementType) {
    mShape.setPosition(position);
    mShape.setRadius(10.0f);
    mShape.setOrigin(mShape.getRadius(), mShape.getRadius());
    mShape.setFillColor(sf::Color::Blue);
    mVelocity = velocity;
    islanuched = false;
}

void Ball::setPosition(sf::Vector2f position) {
    mShape.setPosition(position);
}

void Ball::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
    if(getSpeed()>2000)
        mVelocity = mVelocity / (getSpeed()/1000);
}

void Ball::setRadius(float radius) {
    mShape.setRadius(radius);
}

void Ball::setColor(sf::Color color) {
    mShape.setFillColor(color);
}

sf::Vector2f Ball::getPosition() const {
    return mShape.getPosition();
}

sf::Vector2f Ball::getVelocity() const {
    return mVelocity;
}

float Ball::getSpeed() const {
    return sqrt(mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y);
}

float Ball::getRadius() const {
    return mShape.getRadius();
}

sf::FloatRect Ball::getBounds() const {
    return mShape.getGlobalBounds();
}

void Ball::move(sf::Vector2f offset) {
    mShape.move(offset);
}

void Ball::launch(sf::Vector2f velocity) {
    mVelocity = velocity;
    islanuched = true;
}

bool Ball::isLaunched() const {
    return islanuched;
}

void Ball::update(sf::Time deltaTime) {
    mShape.move(mVelocity * deltaTime.asSeconds());
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mShape, states);
}

bool Ball::isfrozen() const
{
    return isFrozen;
}

void Ball::setFrozen(bool frozen)
{
    isFrozen = frozen;
}

float Ball::getFrozenTimer() const
{
    return mFrozenTimer;
}

void Ball::setFrozenTimer(float frozenTimer)
{
    mFrozenTimer = frozenTimer;
}

ElementType Ball::getElementType() const
{
    return mElementType;
}

void Ball::setElementType(ElementType elementType)
{
    mElementType = elementType;
    switch (elementType)
    {
    case ElementType::Hydro:
        mShape.setFillColor(sf::Color::Blue);
        mShape.setOutlineThickness(0);
        break;
    case ElementType::Pyro:
        mShape.setFillColor(sf::Color::Red);
         mShape.setOutlineThickness(0);
        break;
    case ElementType::Cryo:
        mShape.setFillColor(sf::Color::Cyan);
         mShape.setOutlineThickness(0);
        break;
    case ElementType::Electro:
        //紫色
        mShape.setFillColor(sf::Color(128, 0, 128));
         mShape.setOutlineThickness(0);
        break;
    case ElementType::Frozen:
        //白色
        mShape.setFillColor(sf::Color::White);
        mShape.setOutlineThickness(0);
        islanuched = false;
        isFrozen = true;
        mFrozenTimer = 3.0;
        break;
    case ElementType::Superconduct:
        mShape.setFillColor(sf::Color(128, 0, 128));
        mShape.setOutlineThickness(2.0f);
        mShape.setOutlineColor(sf::Color::White);
        break;
    case ElementType::Overload:
        mShape.setFillColor(sf::Color::Red);
        mShape.setOutlineThickness(2.0f);
        mShape.setOutlineColor(sf::Color::Yellow);
        break;
    case ElementType::ElectroCharged:
        mShape.setFillColor(sf::Color::Blue);
        mShape.setOutlineThickness(2.0f);
        mShape.setOutlineColor(sf::Color(128, 0, 128));
        break;
    default:
        break;
    }
}

void Ball::CheckPaddleCollision(Paddle& paddle)
{
    if(getBounds().intersects(paddle.getBounds()))
    {
        sf::FloatRect ballBounds = getBounds();
        sf::FloatRect paddleBounds = paddle.getBounds();

        // Calculate the overlap between the ball and paddle
        float overlapLeft = ballBounds.left + ballBounds.width - paddleBounds.left;
        float overlapRight = paddleBounds.left + paddleBounds.width - ballBounds.left;
        float overlapTop = ballBounds.top + ballBounds.height - paddleBounds.top;
        float overlapBottom = paddleBounds.top + paddleBounds.height - ballBounds.top;

        // Find the minimum overlap
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        // Determine which side the collision occurred on
        if (minOverlapX < minOverlapY) {
            if (overlapLeft < overlapRight) {
                // Collision occurred on the left side of the paddle
                sf::Vector2f ComponentVelocity = sf::Vector2f(getVelocity().x, getVelocity().y);
                ComponentVelocity.x += paddle.getVelocity().x;
                ComponentVelocity.y += paddle.getVelocity().y;
                float speed = sqrt(ComponentVelocity.x * ComponentVelocity.x + ComponentVelocity.y * ComponentVelocity.y);
                sf::Vector2f newVelocity = sf::Vector2f(ComponentVelocity.x / speed * getSpeed(), ComponentVelocity.y / speed * getSpeed());
                setVelocity(newVelocity);
                setPosition(sf::Vector2f(paddle.getPosition().x - getRadius() - paddle.getSize().x / 2.f - 1.f, getPosition().y));
            }
            else {
                // Collision occurred on the right side of the paddle
                sf::Vector2f ComponentVelocity = sf::Vector2f(-mVelocity.x, mVelocity.y);
                ComponentVelocity.x += paddle.getVelocity().x;
                ComponentVelocity.y += paddle.getVelocity().y;
                float speed = sqrt(ComponentVelocity.x * ComponentVelocity.x + ComponentVelocity.y * ComponentVelocity.y);
                sf::Vector2f newVelocity = sf::Vector2f(ComponentVelocity.x / speed * getSpeed(), ComponentVelocity.y / speed * getSpeed());
                setVelocity(newVelocity);
                setPosition(sf::Vector2f(paddle.getPosition().x + paddle.getSize().x + getRadius() + paddle.getSize().x / 2.f + 1.f, getPosition().y));
            }
        }
        else {
            if (overlapTop < overlapBottom) {
                // Collision occurred on the top side of the paddle
                sf::Vector2f ComponentVelocity = sf::Vector2f(mVelocity.x, -mVelocity.y);
                ComponentVelocity.x += paddle.getVelocity().x;
                ComponentVelocity.y += paddle.getVelocity().y;
                float speed = sqrt(ComponentVelocity.x * ComponentVelocity.x + ComponentVelocity.y * ComponentVelocity.y);
                sf::Vector2f newVelocity = sf::Vector2f(ComponentVelocity.x / speed * getSpeed(), ComponentVelocity.y / speed * getSpeed());
                setVelocity(newVelocity);
                setPosition(sf::Vector2f(getPosition().x, paddle.getPosition().y - getRadius() - paddle.getSize().y / 2.f - 1.f));
            }
            else {
                // Collision occurred on the bottom side of the paddle
            }
        }
        if(sElementReactions.find(std::make_pair(getElementType(), paddle.getElementType())) != sElementReactions.end())
        {
            ElementType reactionelement = sElementReactions[std::make_pair(getElementType(), paddle.getElementType())];
            if(reactionelement == ElementType::Melt||reactionelement == ElementType::Vaporize)
            {
                setElementType(paddle.getElementType());
            }else
            {
                setElementType(reactionelement);
            }
        }else
        {
            setElementType(paddle.getElementType());
        }
    }
}

void Ball::CheckBrickCollision(Brick& brick)
{
    if(getBounds().intersects(brick.getBounds()))
    {
        ElementType reactionelement = sElementReactions[std::make_pair(getElementType(), brick.getElementType())];
        if(reactionelement == ElementType::Hydro)
        {
            brick.setHealth(brick.getHealth() - 1);
        }else if (reactionelement == ElementType::Pyro)
        {
            brick.setHealth(brick.getHealth() - 1);
        }else if (reactionelement == ElementType::Cryo)
        {
            brick.setHealth(brick.getHealth() - 1);
        }else if(reactionelement == ElementType::Electro)
        {
            brick.setHealth(brick.getHealth() - 1);
        }else if(reactionelement == ElementType::Frozen)
        {
            brick.setHealth(brick.getHealth() - 1);
            brick.setElementType(ElementType::Frozen);
        }else if(reactionelement == ElementType::Superconduct)
        {
            brick.setHealth(brick.getHealth() - 2);
            brick.setElementType(ElementType::Superconduct);
        }else if(reactionelement == ElementType::Overload)
        {
            brick.setHealth(brick.getHealth() - 2);
            brick.setElementType(ElementType::Overload);
        }else if(reactionelement == ElementType::ElectroCharged)
        {
            brick.setHealth(brick.getHealth() - 2);
            brick.setElementType(ElementType::ElectroCharged);
        }else if(reactionelement == ElementType::Vaporize)
        {
            brick.setHealth(brick.getHealth() - 2);
            brick.setElementType(ElementType::Vaporize);
        }else if(reactionelement == ElementType::Melt)
        {
            brick.setHealth(brick.getHealth() - 2);
        }else
        {
            if(mElementType == ElementType::Superconduct)
            {
                brick.setHealth(brick.getHealth() - 2);
                brick.setElementType(ElementType::Superconduct);
            }else if(mElementType == ElementType::Overload)
            {
                brick.setHealth(brick.getHealth() - 2);
                brick.setElementType(ElementType::Overload);
            }else if(mElementType == ElementType::ElectroCharged)
            {
                brick.setHealth(brick.getHealth() - 1);
                brick.setElementType(ElementType::ElectroCharged);
            }else
            {
                brick.setHealth(brick.getHealth() - 1);
            }
        }
        if(mElementType != ElementType::Superconduct)
        {
            sf::FloatRect ballBounds = getBounds();
            sf::FloatRect brickBounds = brick.getBounds();

            // Calculate the overlap between the ball and brick
            float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
            float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
            float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
            float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

            // Find the minimum overlap
            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            // Determine which side the collision occurred on
            if (minOverlapX < minOverlapY) {
                if (overlapLeft < overlapRight) {
                    // Collision occurred on the left side of the brick
                    mVelocity.x = -mVelocity.x;
                    setPosition(sf::Vector2f(brick.getPosition().x - getRadius() - brick.getSize().x / 2.f - 1.f, getPosition().y));
                }
                else {
                    // Collision occurred on the right side of the brick
                    mVelocity.x = -mVelocity.x;
                    setPosition(sf::Vector2f(brick.getPosition().x + brick.getSize().x + getRadius() + brick.getSize().x / 2.f + 1.f, getPosition().y));
                }
            }
            else {
                if (overlapTop < overlapBottom) {
                    // Collision occurred on the top side of the brick
                    mVelocity.y = -mVelocity.y;
                    setPosition(sf::Vector2f(getPosition().x, brick.getPosition().y - getRadius() - brick.getSize().y / 2.f - 1.f));
                }
                else {
                    // Collision occurred on the bottom side of the brick
                    mVelocity.y = -mVelocity.y;
                    setPosition(sf::Vector2f(getPosition().x, brick.getPosition().y + brick.getSize().y + getRadius() + brick.getSize().y / 2.f + 1.f));
                }
            }

        }
    }
}
