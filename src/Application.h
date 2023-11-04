#include <iostream>
#include <string>

#include "Console.h"
#include "Quiz.h"

class Application
{
private:
    static std::string dir;
    static Quiz workingQuiz;

    template<typename T> 
    static bool Contains(std::vector<T> vec, T elem);

public:
    static void Run();

    static std::string Input();
    static void PollCommand();
    static void Command(std::string cmd);

    static void Help();
    static void CreateQuiz();
    static void AddQuestion();

    static void Err(std::string msg, bool terminate);
    static void Quit();

};