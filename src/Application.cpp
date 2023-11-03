#include "Application.h"

std::string Application::dir = "";

void Application::Run() {
    dir = "";
    Console::Reset();
    Console::Clear();

    std::cout << "------------------------------------------------------------------------------------------------------------\n";
    Console::SetColor(Console::BLUE);
    std::cout << "                                             Quiz Maker v0.0.1\n";
    Console::Reset();
    std::cout << "------------------------------------------------------------------------------------------------------------\n\n";

    std::cout << "Enter \"help\" for a list of commands.\n\n";
    PollCommand();
}

std::string Application::Input() {
    const int color = Console::GetColor();
    Console::SetColor(Console::CYAN);
    std::cout << dir << ">  ";
    Console::SetColor(Console::YELLOW);
    std::string response;
    std::cin >> response;
    Console::SetColor(color);
    return response;
}

void Application::PollCommand() {
    Command(Input());
}

void Application::Command(std::string cmd) {
    Console::Reset();

    if (cmd == "quit!" || cmd =="q!") {
        exit(0);
    }
    else if (cmd == "quit" || cmd == "q") {
        Quit();
    }
    else if (cmd == "help") {
        Help();
    } 
    else if (cmd == "create") {
        CreateQuiz();
    }
    else {
        Err("ERROR: unknown command '" + cmd + "'\n\n", false);
        PollCommand();
    }
}

void Application::Help() {
    Console::SetColor(Console::CYAN);
    std::cout << "Available commands:\n";
    std::cout << "q / quit - end program\n";
    std::cout << "q! / quit! - end program without confirmation (can be dangerous)\n";
    std::cout << "help - Display this help message\n";
    std::cout << "create - Create a new quiz\n\n";
    Console::Reset();
    PollCommand();
}

void Application::CreateQuiz() {
    dir = "Quiz ";
    std::cout << "Creating quiz...\n\n";
    PollCommand();
}

void Application::Err(std::string msg, bool terminate) {
    Console::SetColor(Console::RED);
    std::cout << msg;
    Console::Reset();
    if (terminate) exit(1);
}

void Application::Quit() {
    Console::SetColor(Console::CYAN);
    std::cout << "Are you sure you want to quit? Progress may not be saved. (y/n)\n";
    std::string response = Input();
    if (response == "y") {
        exit(0);
    }
    else if (response == "n") {
        std::cout << "\n";
        PollCommand();
    }
    else {
        Err("ERROR: unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}