#include "WrittenQuestion.h"

WrittenQuestion::WrittenQuestion() {
	this->question = "";
	this->answer = "";
}

WrittenQuestion::WrittenQuestion(std::string question) {
	this->question = question;
	this->answer = "";
}

WrittenQuestion::WrittenQuestion(std::string question, std::string answer) {
	this->question = question;
	this->answer = answer;
}