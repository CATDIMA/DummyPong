#ifndef _STATE_H
#define _STATE_H

#include <Windows.h>
#include <conio.h>
#include <string>
#include "Figure.h"

class State
{
public:
	/*static variables for working with windows terminal*/
	static HANDLE hStdin;
	static HANDLE hConsole;
	static INPUT_RECORD singleBuff;
	static DWORD read;
	static DWORD bytesWritten;

	State();
	State(State&& st) = default;
	State& operator=(const State&) = delete; /*delete copy = operator*/
	State(const State&) = delete;	/*delete copy constructor*/
	State& operator=(State&&) = delete;		/*delete move assigned operator*/
	virtual ~State() = default;
	
	static void init(const int resX, const int resY);
	static void eraseBuffer(void);
	static void clearBuffer(void);
	static int getWidth(void);
	static int getHeight(void);

	virtual void handle_input(void) = 0;
	virtual void update(double time_ms) = 0;
	void draw(void);
	
protected:
	static int width;
	static int height;
	static int bufferSize;
	static buffer_t buffer;

	static void insertInBuffer(const Figure&);
};

#endif 
