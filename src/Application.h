#include <iostream>
#include <string>

#include "Console.h"

class Application
{
private:
    static std::string dir;

public:

    static void Run();

    static std::string Input();
    static void PollCommand();
    static void Command(std::string cmd);

    static void Help();
    static void CreateQuiz();

    static void Err(std::string msg, bool terminate);
    static void Quit();

};