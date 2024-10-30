#include <utility>
#include <fstream>
#include <chrono>
#include <iostream>
#include "DefinedStates.h"
#include "StateMachine.h"

/*set the cmd resolution in symbols*/
constexpr int resolutionX = 78;
constexpr int resolutionY = 44;

/*limit minimal time for single iteration*/
constexpr std::chrono::milliseconds timestep{16};

/*file name for a file for cerr*/
const std::string cerrOutput{"log.txt"};

int main(int argc, char** argv)
{
	/*redirect error stream*/
	std::ofstream cerrFile(cerrOutput, std::ios::out | std::ios::trunc);
	if (!cerrFile.is_open())
	{
		std::cerr << "Cannot redirect cerr" << std::endl;
		return -1;
	}
	std::cerr.rdbuf(cerrFile.rdbuf());

	/*save scores when exit the program*/
	/*normal exit*/
	SetConsoleCtrlHandler(cmdHandler, TRUE);

	/*abnormal exit*/
	std::set_terminate(myTerminate);

	/*start the state machine
	and put in it the fisrt state - main menu*/
	bool isWorking = true;
	StateMachine::initMachine(&isWorking, resolutionX, resolutionY);
	StateMachine::addState(std::make_shared<MenuState>(MenuState()));

	auto previousTime = std::chrono::high_resolution_clock::now();
	std::chrono::milliseconds lag{0};
	while (isWorking)
	{
		auto currentTime = std::chrono::high_resolution_clock::now();
		auto elapsed = currentTime - previousTime;
		previousTime = currentTime;

		lag += std::chrono::duration_cast<std::chrono::milliseconds>(elapsed);

		StateMachine::getState()->handle_input();

		while (lag >= timestep)
		{
			StateMachine::getState()->update(static_cast<double>(lag.count()));
			lag -= timestep;
		}
		
		StateMachine::getState()->draw();
	}

	ScoreState::saveScores();
	StateMachine::cleanup();
	cerrFile.close();

	return 0;
}