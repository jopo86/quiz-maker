#pragma once

#include "WrittenQuestion.h"
#include "MultipleChoiceQuestion.h"

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

	void save(std::string path);
	static Quiz Load(std::string path);

	void addQuestion(Question question);
	void addQuestions(std::vector<Question> questions);

	void setName(std::string name);
	std::string getName();
	std::vector<Question> getQuestions();
};