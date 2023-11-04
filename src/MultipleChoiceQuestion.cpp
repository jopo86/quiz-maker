#include "MultipleChoiceQuestion.h"

MultipleChoiceQuestion::MultipleChoiceQuestion() {
	this->question = "";
	this->answer = "";
	this->choices = {};
}

MultipleChoiceQuestion::MultipleChoiceQuestion(std::string question) {
	this->question = question;
	this->answer = "";
	this->choices = {};
}

MultipleChoiceQuestion::MultipleChoiceQuestion(std::string question, std::string answer, std::vector<std::string> choices) {
	this->question = question;
	this->answer = answer;
	this->choices = choices;
}

void MultipleChoiceQuestion::addChoice(std::string choice) {
	choices.push_back(choice);
}

std::vector<std::string> MultipleChoiceQuestion::getChoices() {
	return this->choices;
}