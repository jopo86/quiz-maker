#pragma once

#include <string>
#include <vector>

#include "Util.h"

class Question
{
private:

	int type;
	std::string question;
	std::string answer;
	std::vector<std::string> choices;

public:

	static const int WRITTEN = 0;
	static const int MULTIPLE_CHOICE = 1;
	static const int TRUE_FALSE = 2;

	Question() : type(-1) {}
	Question(const int type);
	Question(const int type, std::string question, std::string answer);
	void setQuestion(std::string question);
	void setAnswer(std::string answer);
	void setChoices(std::vector<std::string> choices);
	void addChoice(std::string choice);
	const int getType();
	std::string getQuestion();
	std::string getAnswer();
	std::vector<std::string> getChoices();
	bool check(std::string answer);
	bool isChoice(std::string choice);
};
