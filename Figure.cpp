#include <sstream>
#include <iostream>
#include <fstream>
#include "Figure.h"
#include "State.h"

Figure::Figure(std::string fileName)
{
	std::ifstream fileToRead(fileName, std::ios::in);
	if (!fileToRead.is_open())
	{
		/*cannot read figure*/
		std::cerr << "WARNING: cannot load figure from :" << fileName << std::endl;
	}
	else
	{
		/*
		FILE STRUCTURE:
		1 line. bool isChangable
		2 line. int x int y position
		3 line. int x int y text position
		4-n lines. ascii image
		*/
		std::string readLine;
		try
		{
			/*1st line*/
			std::getline(fileToRead, readLine);
			isChangable = stob(readLine);

			/*2nd line*/
			std::getline(fileToRead, readLine, ' ');
			int firstInt = std::stoi(readLine);
			std::getline(fileToRead, readLine);
			int secondInt = std::stoi(readLine);
			position = new Position(firstInt, secondInt);

			/*3rd line*/
			std::getline(fileToRead, readLine, ' ');
			firstInt = std::stoi(readLine);
			std::getline(fileToRead, readLine);
			secondInt = std::stoi(readLine);
			textPosition = new Position(firstInt, secondInt);

			/*4th - Nth lines*/
			int h = 0;
			
			figure = new buffer_t();
			while (std::getline(fileToRead, readLine))
			{
				for (int i = 0; i < readLine.size(); i++)
				{
					figure->push_back(readLine[i]);
				}
				h++;
			}

			/*if file is empty set h = 1*/
			if (h == 0)
			{
				h = 1;
			}

			/*set calculated size*/
			size = new Size(static_cast<int>(figure->size() / h), h);
		}
		catch (std::exception e)
		{
			std::cerr << "Exception in " << this << ": " << e.what() << std::endl;
			isChangable = false;
			position = new Position(56, 56);
			size = new Size(3, 1);
			textPosition = new Position();
			textToShow = new std::string("");
			figure = new buffer_t{ 'E', 'X', 'C' };
		}
		fileToRead.close();
	}
}

Figure& Figure::operator=(Figure&& f) noexcept
{
	if (this != &f)
	{
		isChangable = f.isChangable;

		delete position;
		delete size;
		delete textPosition;
		delete textToShow;
		delete figure;

		position = f.position;
		size = f.size;
		textPosition = f.textPosition;
		textToShow = f.textToShow;
		figure = f.figure;

		f.position = nullptr;
		f.size = nullptr;
		f.textPosition = nullptr;
		f.textToShow = nullptr;
		f.figure = nullptr;
	}

	return *this;
}

Figure::~Figure()
{
	delete position;
	delete size;
	delete textPosition;
	delete textToShow;
	delete figure;
}

void Figure::movePosition(int dx, int dy)
{
	if (!(dx + this->position->x < 0 || dx + this->position->x > State::getWidth()))
	{
		this->position->x += dx;
	}
	if (!(dy + this->position->y < 0 || dy + this->position->y > State::getHeight()))
	{
		this->position->y += dy;
	}
}

void Figure::setPosition(int x, int y)
{
	if (!(x < 0 || x > State::getWidth()))
	{
		this->position->x = x;
	}
	if (!(y < 0 || y > State::getHeight()))
	{
		this->position->y = y;
	}

	/*set full-changable figures on position without getting textPosition*/
	if (isChangable && figure->empty())
	{
		textPosition->x = position->x;
		textPosition->y = position->y;
	}
}

void Figure::setText(const std::string& fig)
{
	if (isChangable && textPosition->x > 0 && textPosition->y > 0)
	{
		if (!textToShow)
		{
			textToShow = new std::string();
		}
		*textToShow = fig;
	}
}

Position Figure::getPosition(void) const
{
	return *position;
}

Position Figure::getTextPosition(void) const
{
	return *textPosition;
}

Size Figure::getSize(void) const
{
	return *size;
}

const buffer_t& Figure::getFigure(void) const
{
	return *figure;
}

const std::string& Figure::getText(void) const
{
	return *textToShow;
}

bool stob(std::string s)
{
	auto result = false;

	std::istringstream is(s);
	is >> result;

	if (is.fail())
	{
		is.clear();
		is >> std::boolalpha >> result;
	}

	if (is.fail())
	{
		throw std::invalid_argument(s.append(" isn't convertable to bool"));
	}

	return result;
}

Position::Position(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
}

Position::Position(Position&& pos) noexcept
{
	x = pos.x;
	y = pos.y;
	pos.x = 0;
	pos.y = 0;
}

Position& Position::operator=(Position&& pos) noexcept
{
	x = pos.x;
	y = pos.y;
	pos.x = 0;
	pos.y = 0;

	return *this;
}

Size::Size(int w, int h) noexcept
{
	width = w;
	height = h;
}

Size::Size(Size&& sz) noexcept
{
	height = sz.height;
	width = sz.width;
	sz.height = 0;
	sz.width = 0;
}

Size& Size::operator=(Size&& sz) noexcept
{
	height = sz.height;
	width = sz.width;
	sz.height = 0;
	sz.width = 0;

	return *this;
}
