#include "Question.h"

Question::Question()
{
	this->question = "";
	this->answer = "";
}

Question::Question(std::string question, std::string answer)
{
	this->question = question;
	this->answer = answer;
}

std::string Question::getQuestion()
{
	return this->question;
}

std::string Question::getAnswer()
{
	return this->answer;
}

bool Question::isCorrect(std::string answer)
{
	return this->answer == answer;
}