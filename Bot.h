#ifndef _BOT_H
#define _BOT_H

#include "Figure.h"

enum class PLATFORM_PART
{
	UPPER,
	MIDDLE,
	BOTTOM
};

class Bot
{
public:
	static void move(const Figure&, Figure&, const Figure&);
	static void setRandomPlatformPart(void);
private:
	static PLATFORM_PART part;
};

#endif
