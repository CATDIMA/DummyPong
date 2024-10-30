#include "Singleplayer.h"
#include "getchar.h"
#include "DefinedStates.h"
#include "StateMachine.h"
#include "Bot.h"

Singleplayer::Singleplayer()
{
	/*load title for singleplayer*/
	title = new Figure("figures/game/single_title.txt");

	/*set the second name*/
	friendName = "BOT";
	isPlayerNameCorrect = true;
	friendNameLabel->setText(friendName);
	friendNameLabel->setPosition(field->getPosition().x + field->getSize().width -
		/*friendNameLabel.getSize().width / 2 - */ 1 -
		(field->getSize().width / 2 - friendNameLabel->getSize().width) / 2, -1);
}

void Singleplayer::handle_input(void)
{
	if (isAskingName)
	{
		char ch = myGetChar();
		switch (ch)
		{
		case '\r':
			if (playerName.size() > 0)
			{
				playerName.pop_back();
			}
			break;
		case '\n':
			isAskingName = false;
			break;
		default:
			if (ch != '\0')
			{
				playerName += ch;
			}
			break;
		}
	}
	else
	{
		if (isBallIdle)
		{
			/*the handler obtains only 1 player inputs
			and gets move commands from bot*/
			if (GetAsyncKeyState('W') & 1)
			{
				if (platform1->getPosition().y > field->getPosition().y + 1)
				{
					platform1->movePosition(0, -1);
					ball->setVec(getRandomVec());
					Bot::setRandomPlatformPart();
					isBallIdle = false;
				}
			}
			if (GetAsyncKeyState('S') & 1)
			{
				if (platform1->getPosition().y + platform1->getSize().height <
					field->getPosition().y + field->getSize().height - 1)
				{
					platform1->movePosition(0, 1);
					ball->setVec(getRandomVec());
					Bot::setRandomPlatformPart();
					isBallIdle = false;
				}
			}
		}
		else
		{
			/*the handler obtains only 1 player inputs
			and gets move commands from bot*/
			if (GetAsyncKeyState('W') & 1)
			{
				if (platform1->getPosition().y > field->getPosition().y + 1)
				{
					platform1->movePosition(0, -1);
				}
			}
			if (GetAsyncKeyState('S') & 1)
			{
				if (platform1->getPosition().y + platform1->getSize().height <
					field->getPosition().y + field->getSize().height - 1)
				{
					platform1->movePosition(0, 1);
				}
			}
		}

		Bot::move(ball->getFigure(), *platform2, *field);
	}

	/*to exit from game*/
	if (GetAsyncKeyState(VK_ESCAPE) & 1)
	{
		isEndGame = true;
		/*show end screen and wait for enter*/
	}

	if (isEndGame && (GetAsyncKeyState(VK_RETURN) & 0x8000))
	{
		StateMachine::addState(std::make_shared<MenuState>(MenuState()));
	}
}

void Singleplayer::update(double time_ms)
{
	/*check hp*/
	if (!isEndGame && (playerLives == 0 || friendLives == 0))
	{
		isEndGame = true;
		/*show end screen and wait for enter*/
	}

	if (!isEndGame)
	{
		/*check ball position*/
		checkBallPosition();

		/*move ball to the next coordinates*/
		ball->moveBall(time_ms);
	}

	/*update buffer*/
	std::fill(buffer.begin(), buffer.end(), ' ');

	/*show ending screens and save high score*/
	if (isEndGame)
	{
		/*if player won*/
		if (playerScore > friendScore)
		{
			endScreenLabel->setText("YOU WIN! ^_^");

			endScreenLabel->setPosition(field->getPosition().x +
				(field->getSize().width - endScreenLabel->getSize().width) / 2, 15);

			playerScoreLabel->setText(std::string("YOUR SCORE: ") + std::to_string(playerScore));
			playerScoreLabel->setPosition(field->getPosition().x +
				(field->getSize().width - playerScoreLabel->getSize().width) / 2, 16);

			ScoreState::insertInScore(playerName, playerScore);

			State::insertInBuffer(*playerScoreLabel);
		}
		/*if player lose*/
		else if (playerScore < friendScore)
		{

			/*say player that they have lost the game*/
			endScreenLabel->setText("YOU LOSE. V_V");

			playerScoreLabel->setText(std::string("YOUR SCORE: ") + std::to_string(playerScore));
			playerScoreLabel->setPosition(field->getPosition().x +
				(field->getSize().width - playerScoreLabel->getSize().width) / 2, 16);

			ScoreState::insertInScore(playerName, playerScore);
			State::insertInBuffer(*playerScoreLabel);
		}
		/*if there is a draw*/
		else
		{
			/*say that's draw and dont save any scores*/
			endScreenLabel->setText("DRAW!");
			endScreenLabel->setPosition(field->getPosition().x +
				(field->getSize().width - endScreenLabel->getSize().width) / 2, 15);
		}
		State::insertInBuffer(*endScreenLabel);
		State::insertInBuffer(*pressEnter);
	}

	/*calculate score labels positions*/
	playerScoreLabel->setText(std::to_string(playerScore));
	playerScoreLabel->setPosition(field->getPosition().x +
		(field->getSize().width / 2 - playerScoreLabel->getSize().width) / 2, 17);
	friendScoreLabel->setText(std::to_string(friendScore));
	friendScoreLabel->setPosition(field->getPosition().x + field->getSize().width - 1 -
		(field->getSize().width / 2 - friendScoreLabel->getSize().width) / 2, 17);

	if (!isEndGame)
	{
		State::insertInBuffer(*title);
		/*is name entered?*/
		if (isAskingName)
		{
			enterName->setText(playerName);
			State::insertInBuffer(*enterName);
		}
		else
		{
			if (!isNameLabelConstructed)
			{
				playerNameLabel->setText(playerName);
				playerNameLabel->setPosition(field->getPosition().x /*- playerNameLabel.getSize().width / 2*/ +
					(field->getSize().width / 2 - playerNameLabel->getSize().width) / 2, -1);
				State::insertInBuffer(*playerNameLabel);
				isNameLabelConstructed = true;
			}
			else
			{
				State::insertInBuffer(*playerNameLabel);
			}

			State::insertInBuffer(*field);
			State::insertInBuffer(*friendNameLabel);
			State::insertInBuffer(*playerScoreLabel);
			State::insertInBuffer(*friendScoreLabel);
			State::insertInBuffer(*platform1);
			State::insertInBuffer(*platform2);
			State::insertInBuffer(ball->getFigure());
		}
	}
}

void Singleplayer::checkBallPosition(void)
{
	/*check ball position*/
	ball->getPosX();
	ball->getPosY();
	/*1. ball collided with horizontal bounds*/
	/*top*/
	if (ball->getPosY() <= field->getPosition().y + 0.5)
	{
		ball->setVec(mirrorVec(ball->getVec(), upperBound));
		return;
	}
	/*bottom*/
	if (ball->getPosY() + ball->getSize().height >= field->getPosition().y + field->getSize().height - 0.5)
	{
		ball->setVec(mirrorVec(ball->getVec(), bottomBound));
		return;
	}

	/*2. ball collided with the left platform*/
	if ((ball->getPosX() <= platform1->getPosition().x + platform1->getSize().width + 0.5) &&
		(ball->getGraphPos().y >= platform1->getPosition().y &&
			ball->getGraphPos().y <= platform1->getPosition().y + platform1->getSize().height))
	{
		/*the ball's reflection depends on where it hits*/
		if (ball->getGraphPos().y == platform1->getPosition().y)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform1Up));
		}
		if (ball->getGraphPos().y == platform1->getPosition().y + 1)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform1Mid));
		}
		if (ball->getGraphPos().y == platform1->getPosition().y + 2)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform1Down));
		}

		/*set setting to the bot*/
		Bot::setRandomPlatformPart();

		playerScore++;
		return;
	}
	/*ball collided with the right platform*/
	if ((ball->getPosX() >= platform2->getPosition().x - 0.5) &&
		(ball->getGraphPos().y >= platform2->getPosition().y &&
			ball->getGraphPos().y <= platform2->getPosition().y + platform2->getSize().height))
	{
		/*the ball's reflection depends on where it hits*/
		if (ball->getGraphPos().y == platform2->getPosition().y)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform2Up));
		}
		if (ball->getGraphPos().y == platform2->getPosition().y + 1)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform2Mid));
		}
		if (ball->getGraphPos().y == platform2->getPosition().y + 2)
		{
			ball->setVec(mirrorVec(ball->getVec(), platform2Down));
		}

		/*set setting to the bot*/
		Bot::setRandomPlatformPart();

		friendScore++;
		return;
	}

	/*3. ball collided with vecrtical bounds*/
	/*left*/
	if (ball->getPosX() <= field->getPosition().x + 1.5)
	{
		/*remove 1 live from player and set ball in centre*/
		playerLives--;
		friendScore += 10;
		ball->setPos(field->getPosition().x + (field->getSize().width - ball->getSize().width) / 2,
			field->getPosition().y + (field->getSize().height - ball->getSize().height) / 2);
		isBallIdle = true;
		return;
	}
	/*right*/
	if (ball->getPosX() >= field->getPosition().x + field->getSize().width - 1.5)
	{
		/*remove 1 live from friend and set ball in centre*/
		friendLives--;
		playerScore += 10;
		ball->setPos(field->getPosition().x + (field->getSize().width - ball->getSize().width) / 2,
			field->getPosition().y + (field->getSize().height - ball->getSize().height) / 2);
		isBallIdle = true;
		return;
	}
}
