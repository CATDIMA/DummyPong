#ifndef _SCORE_STATE_H
#define _SCORE_STATE_H

#include "State.h"

class ScoreState : public State
{
public:
	const int tableFieldLenght = 36;
	const int tableStepY = 2;
	const int tableShiftX = 2;

	ScoreState();
	ScoreState(const ScoreState&) = delete;
	ScoreState& operator=(const ScoreState&) = delete;
	ScoreState& operator=(ScoreState&&) = delete;
	ScoreState(ScoreState&&) noexcept;
	~ScoreState();

	static void insertInScore(const std::string&, const int);
	static void loadScores(void);
	void insertScoreInBuffer(void);
	static void saveScores(void);

	void handle_input(void) override;
	void update(double time_ms) override;

private:
	static bool isScoreInit;
	static bool isScoreLoaded;
	static const std::string pathToScores;
	static std::vector<std::pair<std::string, int>> scores;

	/*figures that are used in this state*/
	Figure* title = nullptr; 
	Figure* table = nullptr; 
};

#endif