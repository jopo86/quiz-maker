#include "QuizTaker.h"


void QuizTaker::Take(Quiz& quiz) {
	std::cout << "Taking quiz: " << quiz.getName() << "\n--------------------------------------------------------------------------------------\n\n";
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