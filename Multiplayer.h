#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include "GameState.h"

class Multiplayer : public GameState
{
public:
	Multiplayer();
	Multiplayer(const Multiplayer&) = delete;
	Multiplayer& operator=(const Multiplayer&) = delete;
	Multiplayer(Multiplayer&&) = default;
	Multiplayer& operator=(Multiplayer&&) = delete;
	~Multiplayer() = default;

	void handle_input(void) override;
	void update(double time_ms) override;

private:
	void checkBallPosition(void) override;
};

#endif