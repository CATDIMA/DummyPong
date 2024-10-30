#ifndef _FIGURE_H
#define _FIGURE_H

#include <string>
#include <vector>

using buffer_t = std::vector<wchar_t>;

bool stob(std::string s);

struct Position
{
	/*if value < 0, then value is invalid and can't be used*/
	int x = -1;
	int y = -1;

	Position() = default;
	Position(const Position&) = default;

	Position(int x, int y) noexcept;
	Position(Position&& pos) noexcept;
	Position& operator=(Position&& pos) noexcept;
};

struct Size
{
	int height = -1;
	int width = -1;

	Size() = default;
	Size(const Size&) = default;

	Size(int w, int h) noexcept;
	Size(Size&& sz) noexcept;
	Size& operator=(Size&& sz) noexcept;
};

class Figure
{
public:
	Figure() = default;
	Figure(std::string fileName);
	Figure(const Figure&) = default;
	Figure& operator=(const Figure&) = delete;
	Figure(Figure&&) = delete;
	Figure& operator=(Figure&&) noexcept;
	~Figure();

	void movePosition(int dx, int dy);
	void setPosition(int x, int y);
	void setText(const std::string&);
	Position getPosition(void) const;
	Position getTextPosition(void) const;
	Size getSize(void) const;
	const buffer_t& getFigure(void) const;
	const std::string& getText(void) const;
private:
	bool isChangable = false; /*can you change its appearance*/
	Position* position = nullptr; /*position on the screen*/
	Size* size = nullptr; /*size of displayed shape*/
	Position* textPosition = nullptr; /*where changable text is located*/
	std::string* textToShow = nullptr;	/*what to show*/
	buffer_t* figure = nullptr;
};

#endif
