/*define for shitty WinAPI*/
#define NOMINMAX

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include "StateMachine.h"
#include "DefinedStates.h"
#include "ScoreState.h"

std::vector<std::pair<std::string, int>>  ScoreState::scores;
const std::string ScoreState::pathToScores = "scores.st";
bool ScoreState::isScoreInit = true;
bool ScoreState::isScoreLoaded = false;

ScoreState::ScoreState()
{
	title = new Figure(std::string("figures/score/title.txt"));
	table = new Figure(std::string("figures/score/table.txt"));
}

ScoreState::ScoreState(ScoreState&& s) noexcept
{
	title = s.title;
	table = s.table;

	s.title = nullptr;
	s.table = nullptr;
}

ScoreState::~ScoreState()
{
	delete title;
	delete table;
}

void ScoreState::insertInScore(const std::string& name, const int score)
{
	auto itr = std::find_if(scores.begin(), scores.end(),
		[&name](const std::pair<std::string, int>& p)
		{
			return p.first == name;
		});
	if (itr == scores.end())
	{
		scores.emplace_back(std::make_pair(name, score));
	}
	else
	{
		if (scores.at(scores.end() - itr).second < score)
		{
			scores.at(scores.end() - itr).second = score;
		}
	}

	/*values have to be sorted from largest to smallest*/
	std::sort(scores.begin(), scores.end(),
		[](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) -> bool
		{
			return p1.second > p2.second;
		});

	/*if there are more than 10 pairs, remove excess*/
	if (scores.size() > 10)
	{
		scores.pop_back();
	}
}

void ScoreState::loadScores(void)
{
	if (!isScoreInit)
	{
		return;
	}
	/*FILE STRUCTURE:
	1 line. int string lenght
	2 line. std::string name
	3 line. int score
	*/
	std::fstream scoresFile(pathToScores, std::ios::in | std::ios::binary);

	if (!scoresFile.is_open())
	{
		std::cerr << "WARNING: cannot open " << pathToScores << " for reading" << std::endl;
		std::cerr << "Creating blank file" << std::endl;
		
		scoresFile.open(pathToScores, std::ios::out | std::ios::binary);
		if (scoresFile.is_open())
		{
			scoresFile.close();
			scoresFile.open(pathToScores, std::ios::in | std::ios::binary);
		}
		else
		{
			std::cerr << "FATAL: cannot create blank file. What's wrong with your PC?" << std::endl;
			return;
		}

	}

	/*move file pointer to the end to calculate its size*/
	int bytesRead = 0;
	int bytesInFile = 0;
	scoresFile.ignore(std::numeric_limits<std::streamsize>::max());
	bytesInFile = scoresFile.gcount();
	scoresFile.clear();
	scoresFile.seekg(0, std::ios::beg);
	
	size_t stringLenght = 0;
	std::pair<std::string, int> nameAndScore;

	/*return pointer on the begining*/
	scoresFile.seekg(0, std::ios::beg);

	while (bytesRead < bytesInFile)
	{
		/*get string lenght*/
		scoresFile.read(reinterpret_cast<char*>(&stringLenght), sizeof(stringLenght));

		/*read the name*/
		char ch;
		for (int i = 0; i < stringLenght; i++)
		{
			scoresFile.read(reinterpret_cast<char*>(&ch), sizeof(char));
			nameAndScore.first += ch;
		}

		/*read the score*/
		scoresFile.read(reinterpret_cast<char*>(&nameAndScore.second), sizeof(nameAndScore.second));

		/*save read*/
		scores.emplace_back(std::move(nameAndScore));
		bytesRead += sizeof(stringLenght) + sizeof(nameAndScore.second) + static_cast<int>(stringLenght);
	}

	scoresFile.close();
	/*next 3 steps are needed if we have some troubles inside the file*/
	/*sort scores*/
	std::sort(scores.begin(), scores.end(),
		[](const std::pair<std::string, int>& p1, const std::pair<std::string, int>& p2) -> bool
		{
			return p1.second > p2.second;
		});

	/*keep only unique names*/
	scores.erase(std::unique(scores.begin(), scores.end()), scores.end());

	/*check scores size. It must be <= 10*/
	while (scores.size() > 10)
	{
		scores.pop_back();
	}

	/*scores are loaded now*/
	isScoreLoaded = true;
	isScoreInit = false;
}

void ScoreState::insertScoreInBuffer(void)
{
	/*y line for the first pair name-score*/
	/*
	table.getPosition().y -> ------------------------------
                     strY -> |
	*/
	int strY = table->getPosition().y + 1;
	
	/*insert all pairs from scores into State::buffer*/
	for (auto& s : scores)
	{
		/*make string from int score variable*/
		std::string score = std::to_string(s.second);
		
		/*get sizes of strings*/
		int nameSize = static_cast<int>(s.first.size());
		int scoreSize = static_cast<int>(score.size());
		
		/*counter of the string from which the character is copied*/
		int c = 0;

		/*x positions*/
		int nameX = table->getPosition().x + (tableFieldLenght - nameSize) / 2;
		int scoreX = table->getPosition().x + tableFieldLenght + tableShiftX + (tableFieldLenght - static_cast<int>(score.size())) / 2;

		/*insert name*/
		for (int i = nameX; i < nameX + nameSize; i++)
		{
			State::buffer[strY * State::width + i] = s.first[c];
			c++;
		}

		c = 0;

		/*insert score*/
		for (int i = scoreX; i < scoreX + scoreSize; i++)
		{
			State::buffer[strY * State::width + i] = score[c];
			c++;
		}

		/*go to next line*/
		strY += tableStepY;
	}
}

void ScoreState::saveScores(void)
{
	/*If there are no scores in memory, don't save nothing*/
	if (!isScoreLoaded)
	{
		std::cerr << "WARNING: I have nothing scores to save" << std::endl;
		return;
	}

	std::fstream outputFile(pathToScores, std::ios::out | std::ios::binary | std::ios::trunc);

	if (!outputFile.is_open())
	{
		std::cerr << "FATAL: cannot open " << pathToScores << " for saving" << std::endl;
		return;
	}

	for (auto& p : scores)
	{
		size_t sz = p.first.size();
		outputFile.write(reinterpret_cast<char*>(&sz), sizeof(sz));
		outputFile.write(p.first.c_str(), p.first.size());
		outputFile.write(reinterpret_cast<char*>(&p.second), sizeof(p.second));
	}

	outputFile.close();
}

void ScoreState::handle_input(void)
{
	if (GetAsyncKeyState(static_cast<SHORT>(VK_ESCAPE)) & 1)
	{
		/*we can only return to main menu from this state*/
		StateMachine::addState(std::make_shared<MenuState>(MenuState()));
	}
}

void ScoreState::update(double time_ms)
{
	/*update the buffer*/
	std::fill(buffer.begin(), buffer.end(), ' ');
	State::insertInBuffer(*title);
	State::insertInBuffer(*table);
	insertScoreInBuffer();
}
