#include "Ball.h"
#include <cmath>

Vec2d mirrorVec(const Vec2d& vec, const Vec2d& norm)
{
    return vec - 2 * (vec * norm) * norm;
}

Ball::Ball()
{
    ball = new Figure("figures/game/ball.txt");
}

Ball::~Ball()
{
    delete ball;
}

Ball::Ball(Ball&& b) noexcept
{
    isBallIdle = b.isBallIdle;
    posX = b.posX;
    posY = b.posY;
    
    ball = b.ball;
    b.ball = nullptr;
}

Ball& Ball::operator=(Ball&& b) noexcept
{
    if (this != &b)
    {
        isBallIdle = b.isBallIdle;
        posX = b.posX;
        posY = b.posY;

        delete ball;

        ball = b.ball;
        b.ball = nullptr;
    }

    return *this;
}

bool Ball::getBallState(void) const noexcept
{
    return isBallIdle;
}

double Ball::getPosX(void) const noexcept
{
    return posX;
}

double Ball::getPosY(void) const noexcept
{
    return posY;
}

Size Ball::getSize(void) const noexcept
{
    return ball->getSize();
}

Position Ball::getGraphPos(void) const noexcept
{
    return ball->getPosition();
}

void Ball::setPos(double x, double y)
{
    ball->setPosition(static_cast<int>(x), static_cast<int>(y));
    posX = x;
    posY = y;
}

void Ball::setGraphPos(int x, int y)
{
    ball->setPosition(x, y);
}

void Ball::setRealPos(double x, double y)
{
    posX = x;
    posY = y;
}

void Ball::setVec(const Vec2d& v)
{
    ballVec.x = v.x;
    ballVec.y = v.y;
}

void Ball::moveBall(double time_ms)
{
    posX += ballVec.x * time_ms * BALL_VELOCITY;
    posY += ballVec.y * time_ms * BALL_VELOCITY;
    ball->setPosition(static_cast<int>(std::round(posX)),
        static_cast<int>(std::round(posY)));
    checkSpeed();
}

void Ball::checkSpeed(void)
{
    if (std::abs(ballVec.x) > 1)
    {
        if (ballVec.x > 0)
            ballVec.x = 1;
        else
            ballVec.x = -1;
    }
    if (std::abs(ballVec.y) > 1)
    {
        if (ballVec.y > 0)
            ballVec.y = 1;
        else
            ballVec.y = -1;
    }
}

Figure& Ball::getFigure(void) const
{
    return *ball;
}

Vec2d Ball::getVec(void) const noexcept
{
    return ballVec;
}
