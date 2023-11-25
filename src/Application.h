#pragma once

#define VERSION "1.0.0"

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
    static std::string lastCommand;

    static void PollCommand();
    static void RunCommand(Command command);

    static void SuccessMsg(std::string msg);

    static std::string VerifyQuestionNumInput(std::string inp);

public:

    static void Start();

    // Commands
    static void Help();
    static void HelpMore();
    static void Docs();
    static void Tut();
    static void Version();
    static void CreateQuiz();
    static void SetSCA();
    static void RenameQuiz();
    static void AddQuestion();
    static void AddQuestion(const int type);
    static void InsertQuestion();
    static void InsertQuestion(const int type);
    static void ListQuestions(bool more);
    static void EditQuestion(bool q, bool c, bool a, int qNum);
    static void DeleteQuestion();
    static void SwapQuestions();
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