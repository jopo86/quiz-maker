#pragma once

#include "Question.h"

#include <vector>

class Quiz
{
private:
	std::string name;
	std::vector<Question> questions;

public:
	Quiz();
	Quiz(std::string name);
	Quiz(std::string name, std::vector<Question> questions);

	void setQuestions(std::vector<Question> questions);
	void addQuestion(Question question);
	void addQuestions(std::vector<Question> questions);

	void setName(std::string name);
	std::string getName();
	std::vector<Question> getQuestions();
};