#include "Application.h"

void Application::Run() {
    Console::Reset();
    Console::Clear();

    std::cout << "------------------------------------------------------\n";
    Console::SetColor(Console::BLUE);
    std::cout << "                  Quiz Maker v0.0.1\n";
    Console::Reset();
    std::cout << "------------------------------------------------------\n\n";

    std::cout << "Type \"help\" for a list of commands.\n\n";
    PollCommand();
}

void Application::PollCommand()
{
    Console::SetColor(Console::YELLOW);
    std::string response;
    std::cin >> response;
    Console::Reset();
    if (response == "help") 
    {
        Help();
    } 
    else if (response == "create") 
    {
        CreateQuiz();
    }
}

void Application::CreateQuiz()
{
    std::cout << "Creating quiz...\n";
}

void Application::Help()
{
    std::cout << "\n\nAvailable commands:\n";
    std::cout << "help - Display this help message\n";
    std::cout << "create - Create a new quiz\n";
}