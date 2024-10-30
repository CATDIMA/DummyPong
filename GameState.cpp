#include "GameState.h"
#include "StateMachine.h"

GameState::GameState()
{
	ball = new Ball();
	/*load all figures*/
	enterName 			= new Figure("figures/game/enter_name.txt");
	enterFriendName 	= new Figure("figures/game/enter_friend_name.txt");
	field 				= new Figure("figures/game/field.txt");
	platform1 			= new Figure("figures/game/platform.txt");
	platform2 			= new Figure("figures/game/platform.txt");
	playerNameLabel 	= new Figure("figures/game/label.txt");
	friendNameLabel 	= new Figure("figures/game/label.txt");
	playerScoreLabel 	= new Figure("figures/game/label.txt");
	friendScoreLabel 	= new Figure("figures/game/label.txt");
	endScreenLabel 		= new Figure("figures/game/label.txt");
	endScreen 			= new Figure("figures/game/end_screen.txt");
	pressEnter 			= new Figure("figures/game/press_enter.txt");

	/*place platform in field y-centre along the field edges*/
	platform1->setPosition(field->getPosition().x + 1,
		field->getPosition().y + (field->getSize().height - platform1->getSize().height) / 2);
	platform2->setPosition(field->getPosition().x + field->getSize().width - 2,
		field->getPosition().y + (field->getSize().height - platform2->getSize().height) / 2);

	/*place ball in field centre*/
	ball->setPos(field->getPosition().x + (field->getSize().width - ball->getSize().width) / 2,
		field->getPosition().y + (field->getSize().height - ball->getSize().height) / 2);
}

GameState::GameState(GameState&& g) noexcept
{
	isAskingName			= g.isAskingName;
	isPlayerNameCorrect		= g.isPlayerNameCorrect;
	isEndGame				= g.isEndGame;
	isNameLabelConstructed	= g.isNameLabelConstructed;
	playerScore				= g.playerScore;
	friendScore				= g.friendScore;
	playerName				= g.playerName;
	friendName				= g.friendName;
	isEndGame				= g.isEndGame;
	isBallIdle				= g.isBallIdle;
	
	/*--pointers--*/
	title			 = g.title;
	enterName		 = g.enterName;
	enterFriendName  = g.enterFriendName;
	field			 = g.field;
	platform1		 = g.platform1;
	platform2		 = g.platform2;
	ball			 = g.ball;
	playerNameLabel	 = g.playerNameLabel;
	playerScoreLabel = g.playerScoreLabel;
	friendNameLabel  = g.friendNameLabel;
	friendScoreLabel = g.friendScoreLabel;
	endScreenLabel   = g.endScreenLabel;
	endScreen		 = g.endScreen;
	pressEnter		 = g.pressEnter;

	g.title			   = nullptr;
	g.enterName		   = nullptr;
	g.enterFriendName  = nullptr;
	g.field			   = nullptr;
	g.platform1		   = nullptr;
	g.platform2		   = nullptr;
	g.ball			   = nullptr;
	g.playerNameLabel  = nullptr;
	g.playerScoreLabel = nullptr;
	g.friendNameLabel  = nullptr;
	g.friendScoreLabel = nullptr;
	g.endScreenLabel   = nullptr;
	g.endScreen		   = nullptr;
	g.pressEnter	   = nullptr;
}

GameState::~GameState()
{
	delete ball;

	delete title;
	delete enterName;
	delete enterFriendName;
	delete field;
	delete platform1;
	delete platform2;
	delete playerNameLabel;
	delete playerScoreLabel;
	delete friendNameLabel;
	delete friendScoreLabel;
	delete endScreenLabel;
	delete endScreen;
	delete pressEnter;
}

Vec2d GameState::getRandomVec(void)
{
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_real_distribution<double> distr(0.0, 1.0);

	return Vec2d(distr(generator), distr(generator));
}
