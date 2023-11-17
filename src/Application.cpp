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

void Application::PollCommand() {
    const int color = Console::GetColor();
    Console::SetColor(Console::BLUE);
    Console::Print(dir + "> ");
    Console::SetColor(Console::YELLOW);
    RunCommand(Command::Parse(Console::Input()));
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
    Console::Print("COMMANDS:\n");
    Console::Print("q / quit   : quit program\n");
    Console::Print("q! / quit! : force quit program\n");
    Console::Print("help       : display this help message\n");
    Console::Print("create     : create new quiz\n");
    Console::Print("name       : name quiz\n");
    Console::Print("addq       : add question\n");
    Console::Print("\n");
    Console::Reset();
    PollCommand();
}

void Application::HelpMore() {
    Console::SetColor(Console::BLUE);
    Console::Print("---------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("|     COMMAND     |         EXPLANATION         |    ARGUMENTS   |             ARGS EXPLANATION             |  DIRECTORY  |\n");
    Console::Print("|-------------------------------------------------------------------------------------------------------------------------|\n");
    Console::Print("|     q / quit    |        quit program         |      none      |                   N/A                    |     any     |\n");
    Console::Print("|    q! / quit!   |      force quit program     |      none      |                   N/A                    |     any     |\n");
    Console::Print("|      help       |     display help message    |      -more     |           more detailed help msg         |     any     |\n");
    Console::Print("|     create      |       create new quiz       |      none      |                   N/A                    |     Root    |\n");
    Console::Print("|      name       |          name quiz          |      none      |                   N/A                    |     Quiz    |\n");
    Console::Print("|      addq       |         add question        |  -mc, -wr, -tf |   multiple choice, written, true/false   |     Quiz    |\n");
    Console::Print("|      take       |          take quiz          |   -autosect    |     automatically make quiz sections     |     Quiz    |\n");
    Console::Print("|                 |                             |                |                                          |             |\n");
    Console::Print("---------------------------------------------------------------------------------------------------------------------------\n");
    Console::Print("\n");
    Console::Reset();
    PollCommand();
}

void Application::CreateQuiz() {
    // TODO: improve quiz creation process
    dir = "Quiz";
    workingQuiz = Quiz("Untitled");
    Console::Reset();
    Console::Print("Created empty quiz 'Untitled'\n\n");
    PollCommand();
}

void Application::NameQuiz() {
    Console::Print("Enter quiz name:\n");
    std::string name = Console::Input();
    workingQuiz.setName(name);
    Console::Reset();
    Console::Print("Quiz name set to '" + name + "'\n\n");
    PollCommand();
}

void Application::TakeQuiz(bool autosect) {
    // TODO
}

void Application::AddQuestion() {
    Console::Reset();
    Console::Reset();
    Console::Print("Enter Question type ('mc' for multiple choice, 'wr' for written):\n");
    std::string type = Console::Input();
    if (type == "mc") {
        AddQuestionMC();
    }
    else if (type == "wr") {
        AddQuestionWR();
    }
    else {
        Err("unrecognized response: '" + type + "', question creation aborted", false);
    }
    dir = "Quiz";
    PollCommand();
}

void Application::AddQuestionMC() {
    dir = "Quiz:Question";
    Question mcq(Question::MULTIPLE_CHOICE);
    Console::Print("\nEnter Question: \n");
    std::string question = Console::Input();
    mcq.setQuestion(question);
    Console::Reset();
    dir = "Quiz:Question:Choices";
    Console::Print("Enter choices (enter '-' when finished):\n");
    std::string choice;
    while (choice != "-") {
        choice = Console::Input();
        if (choice != "-") {
            mcq.addChoice(choice);
        }
    }
    dir = "Quiz:Question:Answer";
    Console::Reset();
    Console::Print("Enter correct choice:\n");
    dir = "Quiz:Question:Answer";
    std::string answer = Console::Input();
    if (!mcq.isChoice(answer)) {
        Err("answer '" + answer + "' not found in choices, question creation aborted", false);
        dir = "Quiz";
        PollCommand();
        return;
    }
    mcq.setAnswer(answer);
    workingQuiz.addQuestion(mcq);
    Console::Reset();
    Console::Print("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionWR() {
    dir = "Quiz:Question";
    Question wq(Question::WRITTEN);
    Console::Print("\nEnter Question: \n");
    std::string question = Console::Input();
    wq.setQuestion(question);
    Console::Reset();
    dir = "Quiz:Question:Answer";
    Console::Print("Enter answer:\n");
    std::string answer = Console::Input();
    wq.setAnswer(answer);
    workingQuiz.addQuestion(wq);
    Console::Reset();
    Console::Print("Question created.\n\n");
    PollCommand();
}

void Application::AddQuestionTF() {
    dir = "Quiz:Question";
    // TODO: actually make true/false question and stuff
}

void Application::Err(std::string msg, bool terminate) {
    Console::SetColor(Console::RED);
    Console::Print("ERROR: " + msg + "\n\n");
    Console::Reset();
    if (terminate) exit(1);
}

void Application::Quit() {
    Console::Reset();
    Console::Print("Are you sure you want to quit? Progress may be lost. (y/n)\n");
    std::string response = Console::Input();
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
    return;
}

std::string Application::GetDir() {
    return dir;
}