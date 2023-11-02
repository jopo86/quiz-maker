#pragma once
#include <string>

class Question
{
protected:
	std::string question;
	std::string answer;

public:

	std::string getQuestion();
	std::string getAnswer();
	bool isCorrect(std::string answer);
};
