#ifndef _MENU_STATE_H
#define _MENU_STATE_H

#include "State.h"
#include "Figure.h"

class MenuState : public State
{
public:
	MenuState();
	MenuState(const MenuState&) = delete;
	MenuState& operator=(const MenuState&) = delete;
	MenuState& operator=(MenuState&&) = delete;
	MenuState(MenuState&& m) noexcept;
	~MenuState();

	void handle_input(void) override;
	void update(double time_ms) override;

private:
	/*figures that are used in this state*/
	Figure *cursor = nullptr; 
	Figure *title = nullptr; 
	Figure *mainMenuLabel = nullptr; 
	Figure *variants = nullptr; 

	int cursorPos = 0; /*position of cursor in menu strings*/
};

#endif
