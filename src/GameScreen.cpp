#include "../GameScreen.h"
#include "../LevelLoader.h"
#include "../ElementType.h"
#include "../GameOverScreen.h"
#include "../Game.h"
#include "../GameSuccessScreen.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define BORDER_WIDTH 10

using namespace sfAkitsu;

GameScreen::GameScreen(int level) : mycurrentLevel(level){
    // Load font
    mFont.loadFromFile("../src/Fonts/85W.ttf");
    levelcount = 2;
    // Load level
    mBricks = LevelLoader::loadLevel("../src/Levels/level" + std::to_string(mycurrentLevel) + ".txt");
    mPaddle = Paddle();
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
    //init the comb
    mComb = mMaxComb = 0;
    //init the timer
    mTimer.restart();
    mCombTimer.restart();
    // init the bullet
    isGetBullet = 0;
}

void GameScreen::handleInput(sf::RenderWindow& window) {
    mPaddle.handleInput();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		window.close();
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
    if(mPaddle.getPosition().y + mPaddle.getVelocity().y*delta.asSeconds() < SCREEN_HEIGHT - 100)
    {
        mPaddle.setVelocity(sf::Vector2f(0,0));
    }else if(mPaddle.getPosition().y + mPaddle.getVelocity().y*delta.asSeconds() > SCREEN_HEIGHT - mPaddle.getSize().y)
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
            };
        }
        ball.CheckPaddleCollision(mPaddle);
    }

    // Update the comb
    if(mComb > mMaxComb)
    {
        mMaxComb = mComb;
    }
    if(mCombTimer.getElapsedTime().asSeconds() > 2.f)
    {
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
    for (const auto& border : mBorder) {
        window.draw(border); 
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
