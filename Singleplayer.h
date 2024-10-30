#ifndef SINGLEPLAYER_H
#define SINGLEPLAYER_H

#include "GameState.h"

class Singleplayer : public GameState
{
public:
	Singleplayer();
	Singleplayer(const Singleplayer&) = delete;
	Singleplayer& operator=(const Singleplayer&) = delete;
	Singleplayer(Singleplayer&&) = default;
	Singleplayer& operator=(Singleplayer&&) = delete;
	~Singleplayer() = default;

	void handle_input(void) override;
	void update(double time_ms) override;

private:
	void checkBallPosition(void) override;
};

#endif
