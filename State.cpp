#include "State.h"

int State::width;
int State::height;
int State::bufferSize;

buffer_t State::buffer;
HANDLE State::hStdin;
HANDLE State::hConsole;
INPUT_RECORD State::singleBuff;
DWORD State::read;
DWORD State::bytesWritten;

void State::update(double time_ms)
{
}

State::State()
{
}

void State::draw(void)
{
	buffer[bufferSize] = '\0';
	WriteConsoleOutputCharacterW(hConsole, (LPCWSTR)&buffer[0], bufferSize, { 0, 0 }, &bytesWritten);
}

void State::init(const int resX, const int resY)
{
	width = resX;
	height = resY;
	bufferSize = width * height;
	buffer.resize(static_cast<size_t>(bufferSize + 1));

	/*creation of string with command*/
	std::string modeCon = "mode con: cols=" + std::to_string(width) + " lines=" + std::to_string(height);

	/*cmd properties changing*/
	system("title \"PONG\"");
	system(modeCon.c_str());

	hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
}

void State::eraseBuffer(void)
{
	if (!buffer.empty())
	{
		buffer.clear();
		buffer.resize(0);
	}
}

void State::clearBuffer(void)
{
	if (buffer.empty())
	{
		buffer.clear();
	}
}

int State::getWidth(void)
{
	return width;
}

int State::getHeight(void)
{
	return height;
}

void State::insertInBuffer(const Figure& f)
{
	int c = 0;
	int h = f.getSize().height;
	int w = f.getSize().width;
	int y = f.getPosition().y;
	int x = f.getPosition().x;
	int tx = f.getTextPosition().x;
	int ty = f.getTextPosition().y;
	
	if (x < 0 || x + w > State::width)
	{
		return;
	}
	if (y < 0 || y + h > State::height)
	{
		return;
	}

	for (int i = y; i < y + h; i++)
	{
		for (int j = x; j < x + w; j++)
		{
			buffer[i * State::width + j] = f.getFigure()[c];
			c++;
		}
	}

	if (tx > 0 && ty > 0)
	{
		int textWidth = static_cast<int>(f.getText().size());
		c = 0;

		for (int j = tx; j < tx + textWidth; j++)
		{
			buffer[ty * State::width + j] = f.getText()[c];
			c++;
		}
	}
}
