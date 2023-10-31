#pragma once

#include "Question.h"
#include "Quiz.h"
#include <iostream>

class QuizTaker
{
private:
	Quiz quiz;

public:
	QuizTaker(Quiz quiz);

	void takeQuiz();
	void editQuiz();
};