#include "../Paddle.h"
#include "../ElementType.h"

using namespace sfAkitsu;

Paddle::Paddle(int buff):
    mVelocity(0.0f, 0.0f),
    mElementType(ElementType::Hydro),
    mbuff(buff)
{
    mShape.setSize(sf::Vector2f(100.0f, 20.0f));
    mShape.setOrigin(mShape.getSize() / 2.0f);
    mShape.setFillColor(sf::Color::Blue);
    setPosition(sf::Vector2f(400.0f, 550.0f));
    buffTimer.restart();
}

void Paddle::setPosition(sf::Vector2f position) {
    mShape.setPosition(position);
}

void Paddle::setVelocity(sf::Vector2f velocity) {
    mVelocity = velocity;
}

void Paddle::setSize(sf::Vector2f size) {
    mShape.setSize(size);
}

void Paddle::setColor(sf::Color color) {
    mShape.setFillColor(color);
}

sf::Vector2f Paddle::getPosition() const {
    return mShape.getPosition();
}

sf::Vector2f Paddle::getVelocity() const {
    return mVelocity;
}

sf::Vector2f Paddle::getSize() const {
    return mShape.getSize();
}

sf::FloatRect Paddle::getBounds() const {
    return mShape.getGlobalBounds();
}

ElementType Paddle::getElementType() const {
    return mElementType;
}

void Paddle::setElementType(ElementType elementType)
{
    mElementType = elementType;
    if(elementType == ElementType::Cryo)
    {
        setColor(sf::Color::Cyan);
    }else if(elementType == ElementType::Electro)
    {
        //紫色
        setColor(sf::Color(128,0,128));
    }else if(elementType == ElementType::Hydro)
    {
        setColor(sf::Color::Blue);
    }else if(elementType == ElementType::Pyro)
    {
        setColor(sf::Color::Red);
    }
}

void Paddle::move(sf::Vector2f offset) {
    mShape.move(offset);
}

void Paddle::handleInput()
{
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
        if(mbuff == 3 && mElementType!= ElementType::Hydro)
        {
            mShape.setSize(sf::Vector2f(200.0f, 20.0f));
            buffTimer.restart();
        }
        setElementType(ElementType::Hydro);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
        if(mbuff == 3 && mElementType!= ElementType::Pyro)
        {
            mShape.setSize(sf::Vector2f(200.0f, 20.0f));
            buffTimer.restart();
        }
        setElementType(ElementType::Pyro);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
        if(mbuff == 3 && mElementType!= ElementType::Cryo)
        {
            mShape.setSize(sf::Vector2f(200.0f, 20.0f));
            buffTimer.restart();
        }
        setElementType(ElementType::Cryo);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
        setElementType(ElementType::Electro);
        if(mbuff == 3 && mElementType!= ElementType::Electro)
        {
            mShape.setSize(sf::Vector2f(200.0f, 20.0f));
            buffTimer.restart();
        }
        setElementType(ElementType::Electro);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        if(mbuff == 5)
        {
            mVelocity.x = -600.0f;
        }else
        {
            mVelocity.x = -500.0f;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        if(mbuff == 5)
        {
            mVelocity.x = 600.0f;
        }else
        {
            mVelocity.x = 500.0f;
        }
    } else {
        mVelocity.x = 0.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        if(mbuff == 5)
        {
            mVelocity.y = -600.0f;
        }else
        {
            mVelocity.y = -500.0f;
        }
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        if(mbuff == 5)
        {
            mVelocity.y = 600.0f;
        }else
        {
            mVelocity.y = 500.0f;
        }
    } else {
        mVelocity.y = 0.0f;
    }
}

void Paddle::update(sf::Time deltaTime) {
    move(mVelocity * deltaTime.asSeconds());
    if(buffTimer.getElapsedTime().asSeconds() > 10.0f)
    {
        mShape.setSize(sf::Vector2f(100.0f, 20.0f));
    }
}

void Paddle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mShape, states);
}

