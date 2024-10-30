#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <math.h>
#include <random>
#include "State.h"
#include "Ball.h"

class GameState : public State
{
public:
	GameState(); 
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;
	GameState& operator=(GameState&& g) = delete;
	GameState(GameState&& g) noexcept;
	~GameState();

	virtual void handle_input(void) = 0;
	virtual void update(double time_ms) = 0;

protected:
	bool isAskingName = true;
	bool isPlayerNameCorrect = false;
	bool isEndGame = false;
	bool isNameLabelConstructed = false;
	bool isBallIdle = true;
	int playerScore = 0;
	int friendScore = 0;
	int playerLives = 3;
	int friendLives = 3;
	std::string playerName = "";
	std::string friendName = "";

	Vec2d upperBound = Vec2d(0, 1);
	Vec2d bottomBound = Vec2d(0, -1);

	Vec2d platform1Up = Vec2d(1, -1);
	Vec2d platform1Mid = Vec2d(1, 0);
	Vec2d platform1Down = Vec2d(1, 1);

	Vec2d platform2Up = Vec2d(-1, -1);
	Vec2d platform2Mid = Vec2d(-1, 0);
	Vec2d platform2Down = Vec2d(-1, 1);

	Ball* ball = nullptr;

	Figure* title = nullptr;
	Figure* enterName = nullptr; 
	Figure* enterFriendName = nullptr; 
	Figure* field = nullptr; 
	Figure* platform1 = nullptr; 
	Figure* platform2 = nullptr; 
	Figure* playerNameLabel = nullptr; 
	Figure* friendNameLabel = nullptr; 
	Figure* playerScoreLabel = nullptr;
	Figure* friendScoreLabel = nullptr; 
	Figure* endScreenLabel = nullptr; 
	Figure* endScreen = nullptr; 
	Figure* pressEnter = nullptr; 

	virtual void checkBallPosition(void) = 0;
	Vec2d getRandomVec(void);
};

#endif
