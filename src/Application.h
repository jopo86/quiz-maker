#pragma once

#define VERSION "0.0.2 (dev)"

#include <iostream>
#include <string>

#include "CommandHandler.h"
#include "Console.h"
#include "Quiz.h"
#include "Command.h"

class Application {
private:

    static std::string dir;
    static Quiz workingQuiz;

    static void PollCommand();
    static void RunCommand(Command command);

    static void SuccessMsg(std::string msg);

public:

    static void Start();

    // Commands
    static void Help();
    static void HelpMore();
    static void Docs();
    static void CreateQuiz();
    static void RenameQuiz();
    static void AddQuestion();
    static void AddQuestionMC();
    static void AddQuestionWR();
    static void AddQuestionTF();
    static void TakeQuiz(bool autosect);
    static void Clr();
    static void Err(std::string msg, bool terminate);
    static void Quit();
    static void ForceQuit();
    
    static std::string GetDir();

};