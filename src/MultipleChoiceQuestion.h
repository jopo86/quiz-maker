#pragma once

#include "Question.h"
#include <vector>

class MultipleChoiceQuestion : public Question
{
private:
	std::vector<std::string> choices;

public:
	MultipleChoiceQuestion();
	MultipleChoiceQuestion(std::string question);
	MultipleChoiceQuestion(std::string question, std::string answer, std::vector<std::string> choices);

	void addChoice(std::string choice);
	std::vector<std::string> getChoices();
};

