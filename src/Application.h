#pragma once

#define VERSION "0.0.0"

#include <iostream>
#include <string>

#include "CommandHandler.h"
#include "Console.h"
#include "Quiz.h"
#include "QuizTaker.h"
#include "Command.h"

class Application {
private:

    static std::string dir;
    static Quiz workingQuiz;

public:

    static void Start();

    static void PollCommand();
    static void RunCommand(Command command);

    // Commands
    static void Help();
    static void HelpMore();
    static void CreateQuiz();
    static void NameQuiz();
    static void TakeQuiz(bool autosect);
    static void AddQuestion();
    static void AddQuestionMC();
    static void AddQuestionWR();
    static void AddQuestionTF();
    static void Err(std::string msg, bool terminate);
    static void Quit();
    static void ForceQuit();
    
    static std::string GetDir();

};