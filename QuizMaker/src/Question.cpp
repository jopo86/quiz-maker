#include "Question.h"

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