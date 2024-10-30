#include "StateMachine.h"
#include "DefinedStates.h"

BOOL WINAPI cmdHandler(DWORD type)
{
	switch (type)
	{
	case CTRL_CLOSE_EVENT:
	case CTRL_LOGOFF_EVENT:
	case CTRL_SHUTDOWN_EVENT:
		ScoreState::saveScores();
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

bool* StateMachine::isWorking;
std::list<std::shared_ptr<State>> StateMachine::states;

void StateMachine::cleanup(void)
{
	states.back().reset();
	states.pop_back();
}

StateMachine::~StateMachine()
{
	if (!states.empty())
	{
		states.clear();
	}
}

const std::shared_ptr<State>& StateMachine::getState(void)
{
	return states.front();
}

void StateMachine::initMachine(bool* boolPrt, int x, int y)
{
	StateMachine::isWorking = boolPrt;
	State::init(x, y);
	ScoreState::loadScores();
}

void StateMachine::addState(std::shared_ptr<State>&& state)
{
	states.emplace_front(std::move(state));
	if (states.size() > 1)
	{
		cleanup();
	}
}

void StateMachine::stop(void)
{
	*isWorking = false;
}

void myTerminate(void)
{
	ScoreState::saveScores();
	abort();
}