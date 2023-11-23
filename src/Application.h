#pragma once

#define VERSION "0.2.0 (alpha)"

#include <iostream>
#include <string>

#include "CommandHandler.h"
#include "Console.h"
#include "Quiz.h"
#include "Command.h"
#include "QMS.h"

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
    static void AddQuestionWR();
    static void AddQuestionMC();
    static void AddQuestionTF();
    static void ListQuestions(bool more);
    static void EditQuestion(bool q, bool c, bool a, int qNum);
    static void DeleteQuestion();
    static void TakeQuiz();
    static void SaveQuiz();
    static void LoadQuiz();
    static void Root();
    static void Clr();
    static void Err(std::string msg, bool fatal);
    static void Quit();
    static void ForceQuit();
    
    static std::string GetDir();

};