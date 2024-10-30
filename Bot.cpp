#include "Bot.h"
#include <random>

PLATFORM_PART Bot::part;

void Bot::move(const Figure& target, Figure& platform, const Figure& field)
{
	int targetY = target.getPosition().y;
	int platformPartY = static_cast<int>(part) + platform.getPosition().y;

	if (targetY < platformPartY)
	{
		platform.movePosition(0, -1);
	}
	else if (targetY > platformPartY)
	{
		platform.movePosition(0, 1);
	}

	if (platform.getPosition().y > field.getPosition().y + 1)
	{
		platform.movePosition(0, -1);
	}
	if (platform.getPosition().y + platform.getSize().height <
		field.getPosition().y + field.getSize().height - 1)
	{
		platform.movePosition(0, 1);
	}
}

void Bot::setRandomPlatformPart(void)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distr(0, 2);

	switch(distr(generator))
	{
	case 0:
		part = PLATFORM_PART::UPPER;
		break;
	case 1:
		part = PLATFORM_PART::MIDDLE;
		break;
	case 2:
		part = PLATFORM_PART::BOTTOM;
		break;
	default:
		break;
	}
}
