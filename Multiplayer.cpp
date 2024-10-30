#include "Multiplayer.h"
#include "DefinedStates.h"
#include "StateMachine.h"
#include "getchar.h"

Multiplayer::Multiplayer()
{
	/*load title for multiplayer*/
	title = new Figure("figures/game/multi_title.txt");
}

void Multiplayer::handle_input(void)
{
	if (isAskingName)
	{
		char ch = myGetChar();
		if (isPlayerNameCorrect)
		{
			switch (ch)
			{
			case '\r':
				if (friendName.size() > 0)
				{
					friendName.pop_back();
				}
				break;
			case '\n':
				isAskingName = false;
				break;
			default:
				if (ch != '\0')
				{
					friendName += ch;
				}
				break;
			}
		}
		else
		{
			switch (ch)
			{
			case '\r':
				if (playerName.size() > 0)
				{
					playerName.pop_back();
				}
				break;
			case '\n':
				isPlayerNameCorrect = true;
				break;
			default:
				if (ch != '\0')
				{
					playerName += ch;
				}
				break;
			}
		}
	}
	/*the handler obtains inputs from both players*/
	else
	{
		if (isBallIdle)
		{
			if (GetAsyncKeyState('W') & 1)
			{
				if (platform1->getPosition().y > field->getPosition().y + 1)
				{
					platform1->movePosition(0, -1);
					ball->setVec(getRandomVec());
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
					isBallIdle = false;
				}
			}
			if (GetAsyncKeyState(VK_UP) & 1)
			{
				if (platform2->getPosition().y > field->getPosition().y + 1)
				{
					platform2->movePosition(0, -1);
					ball->setVec(getRandomVec());
					isBallIdle = false;
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 1)
			{
				if (platform2->getPosition().y + platform2->getSize().height <
					field->getPosition().y + field->getSize().height - 1)
				{
					platform2->movePosition(0, 1);
					ball->setVec(getRandomVec());
					isBallIdle = false;
				}
			}
		}
		else
		{
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
			if (GetAsyncKeyState(VK_UP) & 1)
			{
				if (platform2->getPosition().y > field->getPosition().y + 1)
				{
					platform2->movePosition(0, -1);
				}
			}
			if (GetAsyncKeyState(VK_DOWN) & 1)
			{
				if (platform2->getPosition().y + platform2->getSize().height <
					field->getPosition().y + field->getSize().height - 1)
				{
					platform2->movePosition(0, 1);
				}
			}
		}
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

void Multiplayer::update(double time_ms)
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
			endScreenLabel->setText(playerName + " WIN!");

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
			
			/*show winner name and their score*/
			endScreenLabel->setText(friendName + " WIN!");
			endScreenLabel->setPosition(field->getPosition().x +
				(field->getSize().width - endScreenLabel->getSize().width) / 2, 15);

			playerScoreLabel->setText(std::string("YOUR SCORE: ") + std::to_string(friendScore));
			playerScoreLabel->setPosition(field->getPosition().x +
				(field->getSize().width - playerScoreLabel->getSize().width) / 2, 16);

			ScoreState::insertInScore(friendName, friendScore);
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
			if (isPlayerNameCorrect)
			{
				enterName->setText(playerName);
				State::insertInBuffer(*enterName);
				enterFriendName->setText(friendName);
				State::insertInBuffer(*enterFriendName);
			}
			else
			{
				enterName->setText(playerName);
				State::insertInBuffer(*enterName);
			}
		}
		else
		{
			if (!isNameLabelConstructed)
			{
				playerNameLabel->setText(playerName);
				playerNameLabel->setPosition(field->getPosition().x /*- playerNameLabel.getSize().width / 2*/ +
					(field->getSize().width / 2 - playerNameLabel->getSize().width) / 2, -1);
				State::insertInBuffer(*playerNameLabel);
				friendNameLabel->setText(friendName);
				friendNameLabel->setPosition(field->getPosition().x + field->getSize().width -
					/*friendNameLabel.getSize().width / 2 - */ 1 -
					(field->getSize().width / 2 - friendNameLabel->getSize().width) / 2, -1);
				isNameLabelConstructed = true;
			}
			else
			{
				State::insertInBuffer(*playerNameLabel);
				State::insertInBuffer(*friendNameLabel);
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

void Multiplayer::checkBallPosition(void)
{
	/*check ball position*/
	double x = ball->getPosX();
	double y = ball->getPosY();
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
