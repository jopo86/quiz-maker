#include "QuizTaker.h"


void QuizTaker::Take(Quiz& quiz) {
	Console::Reset();
	std::string title = " Taking quiz: " + quiz.getName() + " ";
	std::cout << title << "\n";
	for (int i = 0; i < title.length(); i++) {
		std::cout << "~";
	}
	for (Question question : quiz.getQuestions()) {
		// TODO
		if (question.getType() == Question::WRITTEN) {
			
		}
	}

}
