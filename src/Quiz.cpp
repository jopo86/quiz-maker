#include "Quiz.h"

Quiz::Quiz() {
	name = "";
	questions = {};
}

Quiz::Quiz(std::string name) {
	this->name = name;
	questions = {};
}

Quiz::Quiz(std::string name, std::vector<Question> questions) {
	this->name = name;
	this->questions = questions;
}

void Quiz::setQuestions(std::vector<Question> questions) {
	this->questions = questions;
}

void Quiz::addQuestion(Question question) {
	questions.push_back(question);
}

void Quiz::addQuestions(std::vector<Question> questions) {
	for (Question question : questions) {
		addQuestion(question);
	}
}

void Quiz::setName(std::string name) {
	this->name = name;
}

std::vector<Question> Quiz::getQuestions() {
	return questions;
}

std::string Quiz::getName() {
	return name;
}