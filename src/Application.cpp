#include "Application.h"

std::string Application::dir = "";
Quiz Application::workingQuiz = Quiz();

void Application::Run() {
    dir = "";
    Console::Reset();
    Console::Clear();

    Console::SetColor(Console::CYAN);
    std::cout << " Quiz Maker v0.0.1\n";
    Console::Reset();
    std::cout << "~~~~~~~~~~~~~~~~~~~\n\n";

    std::cout << "Enter \"help\" for a list of commands.\n\n";
    PollCommand();
}

std::string Application::Input() {
    const int color = Console::GetColor();
    Console::SetColor(Console::BLUE);
    std::cout << dir << ">  ";
    Console::SetColor(Console::YELLOW);

    std::string response;
    std::getline(std::cin, response);
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
        if (dir == "") {
            CreateQuiz();
        }
        else {
            Err("'create' can only be called from root directory.", false);
            PollCommand();
            return;
        }
    }
    else if (cmd == "name") {
        if (dir == "Quiz ") {
            std::cout << "Enter quiz name:\n";
            std::string name = Input();
            workingQuiz.setName(name);
            Console::Reset();
            std::cout << "Quiz name set to '" << name << "'\n\n";
            PollCommand();
        }
        else {
            Err("'name' can only be called from within Quiz directory", false);
            PollCommand();
            return;
        
        }
    }
    else if (cmd == "addq") {
        if (dir == "Quiz ") {
            AddQuestion();
        }
        else {
            Err("'addq' can only be called from within Quiz directory", false);
            PollCommand();
            return;
        }
    }
    else {
        Err("unrecognized command '" + cmd + "'", false);
        PollCommand();
    }
}

void Application::Help() {
    Console::SetColor(Console::BLUE);
    std::cout << "AVAILABLE COMMANDS:\n\n";
    std::cout << "q / quit : end program\n";
    std::cout << "q! / quit! : end program without confirmation (can be dangerous)\n\n";
    std::cout << "help : Display this help message\n\n";
    std::cout << "create : Create a new quiz (when in root directory)\n\n";
    std::cout << "name : Name quiz (when in Quiz directory)\n";
    std::cout << "addq : Add a new question (when in Quiz directory)\n\n";
    std::cout << "\n";
    Console::Reset();
    PollCommand();
}

void Application::CreateQuiz() {
    dir = "Quiz ";
    workingQuiz = Quiz("Untitled");
    std::cout << "Created empty quiz 'Untitled'\n\n";
    PollCommand();
}

void Application::AddQuestion() {
    dir = "Quiz:Question ";
    Console::Reset();
    std::cout << "\nEnter Question: \n";
    std::string question = Input();
    Console::Reset();
    std::cout << "Enter Question type ('mc' for multiple choice, 'wr' for written):\n";
    std::string type = Input();
    if (type == "mc") {
        MultipleChoiceQuestion mcq = MultipleChoiceQuestion(question);
        std::cout << "Enter choices (enter '_done' when finished):\n";
        std::string choice;
        while (choice != "_done") {
            choice = Input();
            if (choice != "_done") {
                mcq.addChoice(choice);
            }
        }
        Console::Reset();
        std::cout << "Enter correct choice:\n";
        std::string answer = Input();
        if (!Contains(mcq.getChoices(), answer)) {
            Err("answer '" + answer + "' not found in choices, question creation aborted", false);
            dir = "Quiz ";
            PollCommand();
            return;
        }
        mcq.setAnswer(answer);
        workingQuiz.addQuestion(mcq);
        Console::Reset();
        std::cout << "Question created.\n\n";
    }
    else if (type == "wr") {
        WrittenQuestion wq = WrittenQuestion(question);
        std::cout << "Enter answer:\n";
        std::string answer = Input();
        wq.setAnswer(answer);
        workingQuiz.addQuestion(wq);
        std::cout << "Question created.\n\n";
    }
    else {
        Err("unhandled response: '" + type + "', question creation aborted", false);
    }
    dir = "Quiz ";
    PollCommand();
}

void Application::Err(std::string msg, bool terminate) {
    Console::SetColor(Console::RED);
    std::cout << "ERROR: " << msg << "\n\n";
    Console::Reset();
    if (terminate) exit(1);
}

void Application::Quit() {
    Console::SetColor(Console::BLUE);
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
        Err("unhandled response '" + response + "'\n\n", false);
        PollCommand();
    }
}

template <typename T>
bool Application::Contains(std::vector<T> vec, T elem) {
    for (int  i = 0; i < vec.size(); i++) {
        if (vec[i] == elem) return true;
    }
    return false;
}