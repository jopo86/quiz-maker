#pragma once

#include "Question.h"
#include <vector>

class MultipleChoiceQuestion : Question
{
private:
	std::vector<std::string> choices;

public:
	MultipleChoiceQuestion();
	MultipleChoiceQuestion(std::string question, std::string answer, std::vector<std::string> choices);

	std::vector<std::string> getChoices();
};

