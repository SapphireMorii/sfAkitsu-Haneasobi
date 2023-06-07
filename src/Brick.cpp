#include "../Brick.h"

using namespace sfAkitsu;

Brick::Brick(sf::Vector2f position, ElementType elementType) : mHealth(2),originElementType(elementType) {
    mShape.setPosition(position);
    mShape.setSize(sf::Vector2f(25, 25));
    mShape.setOutlineThickness(1.0f);
    mShape.setOutlineColor(sf::Color::White);
    setElementType(elementType);
}

void Brick::setPosition(sf::Vector2f position) {
    mShape.setPosition(position);
}

void Brick::setSize(sf::Vector2f size) {
    mShape.setSize(size);
}

void Brick::setColor(sf::Color color) {
    mShape.setFillColor(color);
}

sf::Vector2f Brick::getPosition() const {
    return mShape.getPosition();
}

sf::Vector2f Brick::getSize() const {
    return mShape.getSize();
}

sf::FloatRect Brick::getBounds() const {
    return mShape.getGlobalBounds();
}

void Brick::update(sf::Time deltaTime) {
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mShape, states);
}

ElementType Brick::getElementType() const {
    return mElementType;
}

ElementType Brick::getOriginElementType() const {
    return originElementType;
}


void Brick::setElementType(ElementType elementType) {
    mElementType = elementType;
    switch (elementType) {
    case ElementType::none:
        //灰色
        mShape.setFillColor(sf::Color::Green);
        break;
    case ElementType::Hydro:
        mShape.setFillColor(sf::Color::Blue);
        break;
    case ElementType::Pyro:
        mShape.setFillColor(sf::Color::Red);
        break;
    case ElementType::Cryo:
        mShape.setFillColor(sf::Color::Cyan);
        break;
    case ElementType::Electro:
        //紫色
        mShape.setFillColor(sf::Color(128, 0, 128));
        break;
    case ElementType::Frozen:
        //白色
        mShape.setFillColor(sf::Color(255, 255, 255));
        break;
    case ElementType::ElectroCharged:
        if(originElementType == ElementType::Hydro)
        {
            //蓝色
            mShape.setFillColor(sf::Color::Blue);
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color(128, 0, 128));
        }
        else if(originElementType == ElementType::Electro)
        {
            mShape.setFillColor(sf::Color(128, 0, 128));
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color::Blue);
        }
        break;
    case ElementType::Overload:
        if(originElementType == ElementType::Pyro)
        {
            mShape.setFillColor(sf::Color::Red);
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color(128, 0, 128));
        }
        else if(originElementType == ElementType::Electro)
        {
            mShape.setFillColor(sf::Color(128, 0, 128));
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color::Red);
        }
        break;
    case ElementType::Superconduct:
        if(originElementType == ElementType::Cryo)
        {
            mShape.setFillColor(sf::Color::Cyan);
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color(128, 0, 128));
        }
        else if(originElementType == ElementType::Electro)
        {
            mShape.setFillColor(sf::Color(128, 0, 128));
            mShape.setOutlineThickness(1.0f);
            mShape.setOutlineColor(sf::Color::Cyan);
        }
        break;
    default:
        break;
    }
}

int Brick::getHealth() const {
    return mHealth;
}

void Brick::setHealth(int health) {
    mHealth = health;
}


