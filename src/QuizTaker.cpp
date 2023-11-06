#include "QuizTaker.h"


void QuizTaker::Take(Quiz& quiz) {
	Console::SetColor(Console::BLUE);
	std::string title = " Taking quiz: " + quiz.getName() + " ";
	std::cout << title << "\n";
	for (int i = 0; i < title.length(); i++) {
		std::cout << "~";
	}
	for (Question question : quiz.getQuestions()) {
		std::cout << question.getQuestion() << "\n";
		std::cout << "Answer: ";
		std::string answer;
		std::cin >> answer;
		std::cout << "\n";
		if (question.isCorrect(answer)) {
			std::cout << "Correct!\n\n";
		}
		else {
			std::cout << "Incorrect!\n\n";
		}
	}

}