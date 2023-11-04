#include "Question.h"

void Question::setAnswer(std::string answer)
{
	this->answer = answer;
}

void Question::setQuestion(std::string question)
{
	this->question = question;
}

std::string Question::getQuestion()
{
	return question;
}

std::string Question::getAnswer()
{
	return answer;
}

bool Question::isCorrect(std::string answer)
{
	return this->answer == answer;
}