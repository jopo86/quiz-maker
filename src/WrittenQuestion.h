#pragma once

#include "Question.h"

class WrittenQuestion : public Question
{
public:
	WrittenQuestion();
	WrittenQuestion(std::string question);
	WrittenQuestion(std::string question, std::string answer);
};