#include "../GameScreen.h"
#include "../LevelLoader.h"
#include "../ElementType.h"
#include "../GameOverScreen.h"
#include "../Game.h"
#include "../GameSuccessScreen.h"
#include "../MenuScreen.h"
#include <random>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BORDER_WIDTH 10

using namespace sfAkitsu;

GameScreen::GameScreen(int level,int selectbuff) : mycurrentLevel(level),buff(selectbuff),mPaddle(selectbuff){
    // Load font
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    levelcount = 2;
    // Load level
    LevelLoader::loadLevel("../src/Levels/level" + std::to_string(mycurrentLevel) + ".txt",mBricks);
    sf::Vector2f ballinitialposition = sf::Vector2f(mPaddle.getPosition().x, mPaddle.getPosition().y - 20);
    mBalls.push_back(Ball(ballinitialposition,mPaddle.getVelocity(),mPaddle.getElementType()));
    // Create the border
    sf::RectangleShape border(sf::Vector2f(SCREEN_WIDTH , BORDER_WIDTH));
    //top
    border.setPosition(sf::Vector2f(0,BORDER_WIDTH));
    border.setFillColor(sf::Color(139, 69, 19)); // Brown color
    mBorder.push_back(border);
    //left
    border.setSize(sf::Vector2f(BORDER_WIDTH, SCREEN_HEIGHT - BORDER_WIDTH));
    border.setPosition(sf::Vector2f(0, BORDER_WIDTH));
    mBorder.push_back(border);
    //right
    border.setPosition(sf::Vector2f(SCREEN_WIDTH-BORDER_WIDTH, BORDER_WIDTH));
    mBorder.push_back(border);
    //bottom
    border.setSize(sf::Vector2f(SCREEN_WIDTH-2*BORDER_WIDTH, BORDER_WIDTH));
    border.setPosition(sf::Vector2f(BORDER_WIDTH, SCREEN_HEIGHT-BORDER_WIDTH));
    mBorder.push_back(border);
    //init the comb
    mComb = mMaxComb = 0;
    //init the timer
    mTimer.restart();
    mCombTimer.restart();
    // init the bullet
    isGetBullet = 0;
    // init the buffcomb
    combforbuff = 1;
    buff1 = 0;
    buff2 = 0;
    wall = 0;
}

void GameScreen::handleInput(sf::RenderWindow& window) {
    mPaddle.handleInput();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		Game::Screen = std::make_shared<MenuScreen>();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        for(auto& ball : mBalls)
        {
            if(!ball.isLaunched())
            {
                ball.launch(sf::Vector2f(0,-500));
            }
        }
    }
}

void GameScreen::update(sf::Time delta)
{
    // Update paddle
    if(mPaddle.getPosition().y + mPaddle.getVelocity().y*delta.asSeconds() < SCREEN_HEIGHT - 150)
    {
        mPaddle.setVelocity(sf::Vector2f(0,0));
    }else if(mPaddle.getPosition().y + mPaddle.getVelocity().y*delta.asSeconds() > SCREEN_HEIGHT - mPaddle.getSize().y)
    {
        mPaddle.setVelocity(sf::Vector2f(0,0));
    }else if(mPaddle.getPosition().x + mPaddle.getVelocity().x*delta.asSeconds() < 0)
    {
        mPaddle.setVelocity(sf::Vector2f(0,0));
    }else if(mPaddle.getPosition().x + mPaddle.getVelocity().x*delta.asSeconds() > SCREEN_WIDTH)
    {
        mPaddle.setVelocity(sf::Vector2f(0,0));
    }
    mPaddle.update(delta);
    // Check if the paddle is out of the screen
    for(auto it = mBalls.begin(); it != mBalls.end();)
    {
        if(it->getPosition().y - it->getRadius() > SCREEN_HEIGHT)
        {
            it = mBalls.erase(it);
        }else
        {
            ++it;
        }
    }

    // Update balls
    for (auto& ball : mBalls) {
        if(ball.isLaunched())
        {
            ball.update(delta);
        }else
        {
            if(ball.isfrozen())
            {
                // Update the freeze timer
                ball.setFrozenTimer(ball.getFrozenTimer() - delta.asSeconds());
                if (ball.getFrozenTimer() <= 0.f) {
                    ball.setFrozen(false);
                    ball.launch(sf::Vector2f(0.f, -500.f));
                }
                ball.move(mPaddle.getVelocity()*delta.asSeconds());
            }else
            {
                ball.setPosition(sf::Vector2f(mPaddle.getPosition().x, mPaddle.getPosition().y - 20));
                ball.setElementType(mPaddle.getElementType());
            }
        }
    }

    // Check if the ball is hit the wall
    for (auto& ball : mBalls) {
        sf::Vector2f ballPosition = ball.getPosition();
        float ballRadius = ball.getRadius();

        if (ballPosition.x - ballRadius < BORDER_WIDTH) {
            // Ball hit the left wall
            ball.setPosition(sf::Vector2f(BORDER_WIDTH + ballRadius, ballPosition.y));
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y));
        }
        else if (ballPosition.x + ballRadius > SCREEN_WIDTH + BORDER_WIDTH) {
            // Ball hit the right wall
            ball.setPosition(sf::Vector2f(SCREEN_WIDTH + BORDER_WIDTH - ballRadius, ballPosition.y));
            ball.setVelocity(sf::Vector2f(-ball.getVelocity().x, ball.getVelocity().y));
        }
        if (ballPosition.y - ballRadius < BORDER_WIDTH) {
            // Ball hit the top wall
            ball.setPosition(sf::Vector2f(ballPosition.x, BORDER_WIDTH + ballRadius));
            ball.setVelocity(sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y));
        }
        if(ballPosition.y + ballRadius > SCREEN_HEIGHT + BORDER_WIDTH && wall)
        {
            // Ball hit the bottom wall
            ball.setPosition(sf::Vector2f(ballPosition.x, SCREEN_HEIGHT + BORDER_WIDTH - ballRadius));
            ball.setVelocity(sf::Vector2f(ball.getVelocity().x, -ball.getVelocity().y));
        }
    }

    //shoot the bullet
    for(auto& bullet:mBullets)
    {
        if(bullet.getIsLanched())
        {
            bullet.update(delta);
        }else
        {
            if(bullet.getLeftOrright())
            {
                bullet.setPosition(sf::Vector2f((mPaddle.getPosition().x)-(mPaddle.getSize().x/6),(mPaddle.getPosition().y)-(mPaddle.getSize().y/2)));
            }else
            {
                bullet.setPosition(sf::Vector2f(sf::Vector2f((mPaddle.getPosition().x) + (mPaddle.getSize().x/6),(mPaddle.getPosition().y)-(mPaddle.getSize().y/2))));
            };
        }
    }
    if(mBulletTimer.getElapsedTime().asSeconds() > 0.5)
    {
        mBulletTimer.restart();
        int shootcount =0;
        for(auto& bullet:mBullets)
        {
            if(shootcount == 2)
            {
                break;
            }
            if(!bullet.getIsLanched())
            {
                shootcount++;
                bullet.setIsLanched(true);
            }
        }
    }
    

    // Check Bullet Collisions
    for(auto& bullet : mBullets)
    {
        for(auto& brick : mBricks)
        {
            if(bullet.checkBrickCollision(brick))
            {
                mComb++;
                mCombTimer.restart();
                bullet.setIshit(true);
            }
        }
    }

    // Remove dead bullets
    mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(), [](const Bullet& bullet) {
        return bullet.getIshit();
    }), mBullets.end());

    // Check ball collisions
    for (auto& ball : mBalls) {
        for (auto& brick : mBricks) {
            if(ball.CheckBrickCollision(brick))
            {
                mComb++;
                mCombTimer.restart();
                if(buff1)
                {
                    buff1 = 0;
                    //生成随机数
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<float> dis(-5,5);
                    float random = dis(gen);
                    //速度顺时针旋转random度
                    float x = ball.getVelocity().x;
                    float y = ball.getVelocity().y;
                    float newx = x * cos(random) - y * sin(random);
                    float newy = x * sin(random) + y * cos(random);
                    sf::Vector2f newVelocity(newx,newy);
                    Ball newBall = Ball(ball.getPosition(),newVelocity,ball.getElementType());
                    newBall.launch(newVelocity);
                    mBalls.push_back(newBall);
                }
            };
        }
        ball.CheckPaddleCollision(mPaddle);
    }
    
    for(auto& brick:mBricks)
    {
        if(brick.getElementType() == ElementType::ElectroCharged)
        {
            for(auto& brick2:mBricks)
            {
                float distance = sqrt(pow(brick.getPosition().x - brick2.getPosition().x,2) + pow(brick.getPosition().y - brick2.getPosition().y,2));\
                if(distance <= 51&&brick.getPosition()!=brick2.getPosition())
                {
                    brick2.setHealth(brick2.getHealth()-1);
                    if(brick2.getHealth()>=0)
                    {
                        mComb++;
                        mCombTimer.restart(); 
                    }
                    if(brick2.getElementType()==brick.getOriginElementType()&&(brick2.getElementType()==ElementType::Electro||brick2.getElementType()==ElementType::Hydro))    
                    {
                        brick2.setElementType(ElementType::ElectroCharged);
                    }
                }
            }
            brick.setElementType(brick.getOriginElementType());
        }
        if(brick.getElementType()==ElementType::Overload)
        {
            for(auto&brick2:mBricks)
            {
                float distance = sqrt(pow(brick.getPosition().x - brick2.getPosition().x,2) + pow(brick.getPosition().y - brick2.getPosition().y,2));
                if(distance <= 26&&brick.getPosition()!=brick2.getPosition())
                {
                    brick2.setHealth(0);
                    mComb++;
                    mCombTimer.restart();
                }
            }
        }
        if(brick.getElementType()==ElementType::Frozen)
        {
            for(auto&brick2:mBricks)
            {
                float distance = sqrt(pow(brick.getPosition().x - brick2.getPosition().x,2) + pow(brick.getPosition().y - brick2.getPosition().y,2));
                if(distance <= 26&&brick.getPosition()!=brick2.getPosition()&&brick2.getElementType()!=ElementType::Frozen&&brick2.getElementType()==brick.getOriginElementType())
                {
                    brick2.setHealth(1);
                    brick2.setElementType(ElementType::Frozen);
                    mComb++;
                    mCombTimer.restart();
                }
            }
        }
    }

    // Frozen 
    for(auto &Brick:mBricks)
    {
        if(Brick.getHealth() <= 0 && Brick.getElementType() == ElementType::Frozen)
        {
            for(auto &Brick2:mBricks)
            {
                if(Brick2.getElementType() == ElementType::Frozen)
                {
                    if(Brick2.getPosition()==Brick.getPosition())
                    {
                        continue;
                    }
                    Brick2.setHealth(0);
                    mComb++;
                    mCombTimer.restart();
                }
            }
            break;
        }
    }

    // Update the comb
    if(mComb > mMaxComb)
    {
        mMaxComb = mComb;
        if(mComb>=10*combforbuff)
        {
            combforbuff++;
            if(buff == 1&&mBalls.size()<3)
            {
                buff1 = 1;
            }else if(buff == 2 && buff2 < 3)
            {
                buff2++;
                for(auto &ball:mBalls)
                {
                    ball.setVelocity(1.2f*ball.getVelocity());
                }
            }else if(buff == 4)
            {
                wall =  1;
                wallTimer.restart();
            }
        }
    }
    if(wallTimer.getElapsedTime().asSeconds() > 6.f)
    {
        wall = 0;
    }
    if(mCombTimer.getElapsedTime().asSeconds() > 5.f)
    {
        combforbuff = 1;
        mComb = 0;
    }

    // Remove dead bricks
    mBricks.erase(std::remove_if(mBricks.begin(), mBricks.end(), [](const Brick& brick) {
        return brick.getHealth() <= 0;
    }), mBricks.end());

    // add the bullet
    if(mBricks.size() <= 2&&!isGetBullet)
    {
        Bullet bullet1(sf::Vector2f(sf::Vector2f((mPaddle.getPosition().x)-(mPaddle.getSize().x/6),(mPaddle.getPosition().y)-(mPaddle.getSize().y/2))));
        bullet1.setLeftOrright(true);
        Bullet bullet2(sf::Vector2f(sf::Vector2f((mPaddle.getPosition().x)+(mPaddle.getSize().x/6),(mPaddle.getPosition().y)-(mPaddle.getSize().y/2))));
        bullet2.setLeftOrright(false);
        for(int i=0;i<8;i++)
        {
            mBullets.push_back(bullet1);
            mBullets.push_back(bullet2);
        }
        isGetBullet = true;
        mBulletTimer.restart();
    }


    // Check if all bricks are gone
    if (mBricks.empty()) {
        // Game Success
        Game::Screen = std::make_shared<GameSuccessScreen>(mTimer.getElapsedTime().asSeconds(), mMaxComb);
    }

     if(mBalls.empty())
    {
        // Game over
        Game::Screen = std::make_shared<GameOverScreen>(mTimer.getElapsedTime().asSeconds(),mMaxComb);
    }
  
}

void GameScreen::render(sf::RenderWindow& window) {
    // Draw bricks
    for (const auto& brick : mBricks) {
        brick.draw(window, sf::RenderStates::Default);
    }

    // Draw balls
    for (const auto& ball : mBalls) {
        ball.draw(window, sf::RenderStates::Default);
    }

    // Draw paddle
    mPaddle.draw(window, sf::RenderStates::Default);

    // Draw border
    for (int i=0;i<3;i++)
    {
        window.draw(mBorder[i]);
    }
    if(wall == 1)
    {
        window.draw(mBorder[3]);
    }

    // Draw bullets
    for(auto& bullet:mBullets)
    {
        if(bullet.getIsLanched())
        {
            bullet.draw(window,sf::RenderStates::Default);
        }
    }

    // Draw time
    sf::Time elapsed = mTimer.getElapsedTime();
    sf::Text timerText;
    timerText.setFont(mFont);
    timerText.setString("Time: " + std::to_string(elapsed.asSeconds()));
    timerText.setPosition(10, 10);
    window.draw(timerText);

    // Draw comb
    sf::Text combText;
    combText.setFont(mFont);
    combText.setString("Comb: " + std::to_string(mComb));
    combText.setPosition(10, 40);
    window.draw(combText);
}
