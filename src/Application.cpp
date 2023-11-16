#include "Application.h"

std::string Application::dir = "";
Quiz Application::workingQuiz = Quiz();

void Application::Start() {
    dir = "";
    Console::Reset();
    Console::Clear();

    Console::SetColor(Console::CYAN);
    Console::Print(" Quiz Maker v0.0.1\n");
    Console::Reset();
    Console::Print("~~~~~~~~~~~~~~~~~~~\n\n");

    Console::Print("Enter \"help\" for a list of commands.\n\n");

    PollCommand();
}

std::string Application::Input() {
    std::string response;
    std::getline(std::cin, response);
    return response;
}

void Application::PollCommand() {
    const int color = Console::GetColor();
    Console::SetColor(Console::BLUE);
    Console::Print(dir + ">  ");
    Console::SetColor(Console::YELLOW);
    RunCommand(Command::Parse(Input()));
    Console::SetColor(color);
}

void Application::RunCommand(Command command) {
    Console::Reset();

    if (!CommandHandler::Verify(command)) {
        Err(CommandHandler::GetErr(), false);
        PollCommand();
        return;
    }

    CommandHandler::Run(command);
}

void Application::Help() {
    Console::SetColor(Console::BLUE);
    Console::Print("AVAILABLE COMMANDS:\n\n");
    Console::Print("q / quit : end program\n");
    Console::Print("q! / quit! : end program without confirmation (can be dangerous)\n\n");
    Console::Print("help : Display this help message\n\n");
    Console::Print("create : Create a new quiz (when in root directory)\n\n");
    Console::Print("name : Name quiz (when in Quiz directory)\n");
    Console::Print("addq : Add a new question (when in Quiz directory)\n\n");
    Console::Print("\n");
    Console::Reset();
    PollCommand();
}

void Application::CreateQuiz() {
    dir = "Quiz ";
    workingQuiz = Quiz("Untitled");
    Console::Print("Created empty quiz 'Untitled'\n\n");
    PollCommand();
}

void Application::NameQuiz() {
    Console::Print("Enter quiz name:\n");
    std::string name = Input();
    workingQuiz.setName(name);
    Console::Reset();
    Console::Print("Quiz name set to '" + name + "'\n\n");
    PollCommand();
}

void Application::AddQuestion() {
    dir = "Quiz:Question ";
    Console::Reset();
    Console::Print("\nEnter Question: \n");
    std::string question = Input();
    Console::Reset();
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written):\n");
    std::string type = Input();
    if (type == "mc") {
        Question mcq(Question::MULTIPLE_CHOICE);
        Console::Reset();
        dir = "Quiz:Question:Choices ";
        Console::Print("Enter choices (enter '-' when finished):\n");
        std::string choice;
        while (choice != "-") {
            choice = Input();
            if (choice != "-") {
                mcq.addChoice(choice);
            }
        }
        dir = "Quiz:Question ";
        Console::Reset();
        Console::Print("Enter correct choice:\n");
        dir = "Quiz:Question:Answer ";
        std::string answer = Input();
        if (!mcq.isChoice(answer)) {
            Err("answer '" + answer + "' not found in choices, question creation aborted", false);
            dir = "Quiz ";
            PollCommand();
            return;
        }
        mcq.setAnswer(answer);
        workingQuiz.addQuestion(mcq);
        Console::Reset();
        Console::Print("Question created.\n\n");
    }
    else if (type == "wr") {
        Question wq(Question::WRITTEN);
        Console::Reset();
        dir = "Quiz:Question:Answer ";
        Console::Print("Enter answer:\n");
        std::string answer = Input();
        wq.setAnswer(answer);
        workingQuiz.addQuestion(wq);
        Console::Reset();
        Console::Print("Question created.\n\n");
    }
    else {
        Err("unhandled response: '" + type + "', question creation aborted", false);
    }
    dir = "Quiz ";
    PollCommand();
}

void Application::Err(std::string msg, bool terminate) {
    Console::SetColor(Console::RED);
    Console::Print("ERROR: " + msg + "\n\n");
    Console::Reset();
    if (terminate) exit(1);
}

void Application::Quit() {
    Console::SetColor(Console::BLUE);
    Console::Print("Are you sure you want to quit? Progress may not be saved. (y/n)\n");
    std::string response = Input();
    if (response == "y") {
        ForceQuit();
    }
    else if (response == "n") {
        Console::Print("\n");
        PollCommand();
    }
    else {
        Err("unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}

void Application::ForceQuit() {
    exit(0);
}

std::string Application::GetDir() {
    return dir;
}