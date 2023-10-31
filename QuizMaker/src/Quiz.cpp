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

void Quiz::save(std::string path)
{
	// save quiz as json
}

Quiz Quiz::Load(std::string path) {
	// load quiz from json
}

void Quiz::addQuestion(Question question) {
	questions.push_back(question);
}

void Quiz::addQuestions(std::vector<Question> questions) {
	for (Question question : questions) {
		addQuestion(question);
	}
}

std::vector<Question> Quiz::getQuestions() {
	return questions;
}

std::string Quiz::getName() {
	return name;
}