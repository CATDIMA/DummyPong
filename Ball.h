#ifndef BALL_H
#define BALL_H

#include "Figure.h"

struct Vec2d
{
	Vec2d(double x, double y) : x(x), y(y)
	{}

	/*scalar multiplication*/
	friend double operator*(const Vec2d& a, const Vec2d& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/*multiplying a vector by a number*/
	friend Vec2d operator*(const Vec2d& a, const double& b)
	{
		return Vec2d(a.x * b, a.y * b);
	}
	friend Vec2d operator*(const double& a, const Vec2d& b)
	{
		return Vec2d(b.x * a, b.y * a);
	}

	/*vector subtraction*/
	friend Vec2d operator-(const Vec2d& a, const Vec2d& b)
	{
		return Vec2d(a.x - b.x, a.y - b.y);
	}

	double x;
	double y;
};

Vec2d mirrorVec(const Vec2d& vec, const Vec2d& norm);

class Ball
{
public:
	Ball();
	Ball(Ball&) = delete;
	Ball& operator=(const Ball&) = delete;
	Ball(Ball&&) noexcept;
	Ball& operator=(Ball&&) noexcept;
	~Ball();

	bool getBallState(void) const noexcept;
	double getPosX(void) const noexcept;
	double getPosY(void) const noexcept;
	Size getSize(void) const noexcept;
	Position getGraphPos(void) const noexcept;
	Figure& getFigure(void) const;
	Vec2d getVec(void) const noexcept;
	void setPos(double, double);
	void setGraphPos(int, int);
	void setRealPos(double, double);
	void setVec(const Vec2d&);

	void moveBall(double time_ms);

private:
	const double BALL_VELOCITY = 0.1;

	bool isBallIdle = true;
	double posX = 0;
	double posY = 0;
	Vec2d ballVec = Vec2d(0, 0);

	Figure* ball = nullptr;

	void checkSpeed(void);
};

#endif