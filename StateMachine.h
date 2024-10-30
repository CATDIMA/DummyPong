#ifndef _STATE_MACHINE_H
#define _STATE_MACHINE_H

#include <list>
#include <utility>
#include <memory>
#include "State.h"

BOOL WINAPI cmdHandler(DWORD type);

void myTerminate(void);

class StateMachine
{
public:
	StateMachine() = delete;
	StateMachine(const StateMachine&) = delete;
	StateMachine& operator=(const StateMachine&) = delete;
	StateMachine(StateMachine&&) = delete;
	StateMachine& operator=(StateMachine&&) = delete;
	~StateMachine();

	static const std::shared_ptr<State>& getState(void);

	static void initMachine(bool*, int x, int y);
	static void addState(std::shared_ptr<State>&&);
	static void stop(void);
	static void cleanup(void);
private:
	static bool* isWorking;
	static std::list<std::shared_ptr<State>> states;
};

#endif
