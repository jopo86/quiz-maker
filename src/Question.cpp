#include "Question.h"

Question::Question(int type) {
	this->type = type;
	question = "";
	answer = "";
	choices = {};
}

Question::Question(int type, std::string question, std::string answer) {
	this->type = type;
	this->question = question;
	this->answer = answer;
	choices = {};
}

void Question::setQuestion(std::string question) {
	this->question = question;
}

void Question::setAnswer(std::string answer) {
	this->answer = answer;
}

void Question::setChoices(std::vector<std::string> choices) {
	if (!(type == MULTIPLE_CHOICE)) throw "Cannot set choices, question is not multiple choice";
	this->choices = choices;
}

void Question::addChoice(std::string choice) {
	if (!(type == MULTIPLE_CHOICE)) throw "Cannot add choices, question is not multiple choice";
	choices.push_back(choice);
}

const int Question::getType() {
	return type;
}

std::string Question::getQuestion() {
	return question;
}

std::string Question::getAnswer() {
	return answer;
}

std::vector<std::string> Question::getChoices() {
	return choices;
}

bool Question::check(std::string answer) {
	return this->answer == answer;
}

bool Question::isChoice(std::string choice) {
	if (!(type == MULTIPLE_CHOICE)) throw "Cannot check choices, question is not multiple choice";
	return Util::Contains(choices, choice);
}
