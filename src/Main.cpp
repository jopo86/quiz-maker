#include <iostream>
#include "Console.h"
#include "Quiz.h"
#include "QuizTaker.h"
#include "WrittenQuestion.h"

int main()
{
	Console::SetColor(Console::BLUE);
	Quiz quiz("Test Quiz", std::vector<Question>({ WrittenQuestion("what is 2 + 2", "4"), WrittenQuestion("what is 1 + 1", "2")  }));
	QuizTaker taker(quiz);

	taker.takeQuiz();

	return 0;
}