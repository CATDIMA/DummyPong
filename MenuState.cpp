#include <memory>
#include "DefinedStates.h"
#include "StateMachine.h"
#include "MenuState.h"

MenuState::MenuState()
{
	cursor = new Figure(std::string("figures/main_menu/cursor.txt"));
	title = new Figure(std::string("figures/main_menu/title.txt"));
	mainMenuLabel = new Figure(std::string("figures/main_menu/menu.txt"));
	variants = new Figure(std::string("figures/main_menu/choice.txt"));
}

MenuState::MenuState(MenuState&& m) noexcept
{
	cursor = m.cursor;
	title = m.title;
	mainMenuLabel = m.mainMenuLabel;
	variants = m.variants;

	m.cursor = nullptr;
	m.title = nullptr;
	m.mainMenuLabel = nullptr;
	m.variants = nullptr;
}

MenuState::~MenuState()
{
	delete cursor;
	delete title;
	delete mainMenuLabel;
	delete variants;
}

void MenuState::handle_input(void)
{
	if ((GetAsyncKeyState(static_cast<SHORT>('W')) & 1) ||
		(GetAsyncKeyState(static_cast<SHORT>(VK_UP)) & 1))
	{
		/*cursor goes up*/
		if (cursorPos > 0)
		{
			cursor->movePosition(0, -2);
			cursorPos--;
		}
	}
	if ((GetAsyncKeyState(static_cast<SHORT>('S')) & 1) ||
		(GetAsyncKeyState(static_cast<SHORT>(VK_DOWN)) & 1))
	{
		/*cursor goes down*/
		if (cursorPos < 3)
		{
			cursor->movePosition(0, 2);
			cursorPos++;
		}
	}
	if (GetAsyncKeyState(static_cast<SHORT>(VK_RETURN)) & 1)
	{
		switch (cursorPos)
		{
		case 0:
			StateMachine::addState(std::make_shared<Multiplayer>(Multiplayer()));
			break;
		case 1:
			StateMachine::addState(std::make_shared<Singleplayer>(Singleplayer()));
			break;
		case 2:
			StateMachine::addState(std::make_shared<ScoreState>(ScoreState()));
			break;
		case 3:
			StateMachine::stop();
			break;
		default:
			break;
		}
	}
	if (GetAsyncKeyState(static_cast<SHORT>(VK_ESCAPE)) & 1)
	{
		/*esc provides exit*/
		StateMachine::stop();
	}
}

void MenuState::update(double time_ms)
{
	/*update the buffer*/
	std::fill(buffer.begin(), buffer.end(), ' ');
	State::insertInBuffer(*title);
	State::insertInBuffer(*mainMenuLabel);
	State::insertInBuffer(*cursor);
	State::insertInBuffer(*variants);
}
