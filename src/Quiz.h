#pragma once

#include "Question.h"

#include <vector>

class Quiz
{
private:
	std::string name;
	std::vector<Question> questions;
	bool showCorrectAnswer;

public:
	Quiz();
	Quiz(std::string name);
	Quiz(std::string name, std::vector<Question> questions);

	void setQuestions(std::vector<Question> questions);
	void addQuestion(Question question);
	void addQuestions(std::vector<Question> questions);
	void setQuestion(Question question, int i);
	void setName(std::string name);
	void setShowCorrectAnswer(bool showCorrectAnswer);

	std::string getName();
	std::vector<Question> getQuestions();
	bool showsCorrectAnswer();
};