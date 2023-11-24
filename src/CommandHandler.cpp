#include "CommandHandler.h"

const std::vector<std::string> CommandHandler::DIR_ANY = { "", "Quiz", "Quiz:Question", "Quiz:Question:Choices", "Quiz:Question:Answer" };
const std::vector<std::string> CommandHandler::DIR_ROOT = { "" };
const std::vector<std::string> CommandHandler::DIR_QUIZ = { "Quiz" };
const std::vector<std::string> CommandHandler::DIR_QUESTION = { "Quiz:Question" };
const std::vector<std::string> CommandHandler::DIR_CHOICES = { "Quiz:Question:Choices" };
const std::vector<std::string> CommandHandler::DIR_ANSWER = { "Quiz:Question:Answer" };

const std::vector<std::string> CommandHandler::VALID_COMMANDS = {
    "quit!",
    "q!",
    "quit",
    "q",
    "v",
    "version",
    "root",
    "clr",
    "help",
    "docs",
    "tut",
    "create",
    "sca",
    "rename",
    "addq",
    "insq",
    "listq",
    "editq",
    "delq",
    "swapq",
    "take",
    "save",
    "load"
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_ARGS = {
    { "quit!",   { "" } },
    { "q!",      { "" } },
    { "quit",    { "" } },
    { "q",       { "" } },
    { "v",       { "" } },
    { "version", { "" } },
    { "root",    { "" } },
    { "clr",     { "" }},
    { "help",    { "more" } },
    { "docs",    { "" } },
    { "tut",     { "" } },
    { "create",  { "" } },
    { "sca",     { "" } },
    { "rename",  { "" } },
    { "addq",    { "mc", "wr", "tf" } },
    { "insq",    { "mc", "wr", "tf" } },
    { "listq",   { "more" } },
    { "editq",   { "q", "c", "a" } },
    { "delq",    { "" } },
    { "swapq",   { "" } },
    { "take",    { "" } },
    { "save",    { "" } },
    { "load",    { "" } }
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_DIRS = {
    { "quit!",   DIR_ANY },
    { "q!",      DIR_ANY },
    { "quit",    DIR_ANY },
    { "q",       DIR_ANY },
    { "v",       DIR_ANY },
    { "version", DIR_ANY },
    { "root",    DIR_ANY },
    { "clr",     DIR_ANY },
    { "help",    DIR_ANY },
    { "docs",    DIR_ANY},
    { "tut",     DIR_ANY},
    { "create",  DIR_ROOT },
    { "sca",     DIR_QUIZ },
    { "rename",  DIR_QUIZ },
    { "addq",    DIR_QUIZ },
    { "insq",    DIR_QUIZ },
    { "listq",   DIR_QUIZ },
    { "editq",   DIR_QUIZ },
    { "delq",    DIR_QUIZ },
    { "swapq",   DIR_QUIZ },
    { "take",    DIR_QUIZ },
    { "save",    DIR_QUIZ },
    { "load",    DIR_ROOT }
};

std::string CommandHandler::err = "";

bool CommandHandler::Verify(Command command) {
    std::string cmd = Util::ToLower(command.getCmd());
    std::vector<std::string> args = {};
    for (int i = 0; i < command.getArgs().size(); i++) {
        args.push_back(Util::ToLower(command.getArgs()[i]));
    }


    // check if command exists
    if (!Util::Contains(VALID_COMMANDS, cmd)) {
        err = "unrecognized command '" + cmd + "'\nUse 'help' to get a list of commands.";
        return false;
    }

    // check if command has valid args
    std::vector<bool> valid(args.size(), false);

    for (int i = 0; i < args.size(); i++) {
        valid[i] = Util::Contains(VALID_ARGS.at(cmd), args[i]);
    }

    bool allArgsValid = true;
    err = "unrecognized argument(s): ";
    for (int i = 0; i < args.size(); i++) {
        if (!valid[i]) {
            allArgsValid = false;
            err += "'" + args[i] + "' ";
        }
    }
    err += "for command '" + cmd + "'\nUse 'help -more' to get a list of commands with their arguments.";

    if (!allArgsValid) return false;
    err = "";

    // check if command is valid in current directory
    if (Util::Contains(VALID_DIRS.at(cmd), Application::GetDir())) return true;

    err = "command '" + cmd + "' can only be called from directory: ";
    for (int i = 0; i < VALID_DIRS.at(cmd).size(); i++) {
        err += "'" + (VALID_DIRS.at(cmd)[i] == "" ? "root" : VALID_DIRS.at(cmd)[i]) + "' " + (i == VALID_DIRS.at(cmd).size() - 1 ? "" : "or ");
    }
    err += "\nUse 'help -more' to get a list of commands with their valid directories.";
    return false;
}

void CommandHandler::Run(Command command) {
    std::string dir = Application::GetDir();
    std::string cmd = command.getCmd();

    if (cmd == "quit!" || cmd == "q!") {
        Application::ForceQuit();
    } 
    else if (cmd == "quit" || cmd == "q") {
        Application::Quit();
    }
    else if (cmd == "v" || cmd == "version") {
        Application::Version();
    }
    else if (cmd == "root") {
        Application::Root();
    }
    else if (cmd == "clr") {
        Application::Clr();
    }
    else if (cmd == "help") {
        if (command.hasArg("more")) Application::HelpMore();
        else Application::Help();
    }
    else if (cmd == "docs") {
        Application::Docs();
    }
    else if (cmd == "tut") {
        Application::Tut();
    }
    else if (cmd == "create") {
        Application::CreateQuiz();
    }
    else if (cmd == "sca") {
        Application::SetSCA();
    }
    else if (cmd == "rename") {
        Application::RenameQuiz();
    }
    else if (cmd == "addq") {
        if (command.hasArg("wr")) Application::AddQuestion(Question::WRITTEN);
        else if (command.hasArg("mc")) Application::AddQuestion(Question::MULTIPLE_CHOICE);
        else if (command.hasArg("tf")) Application::AddQuestion(Question::TRUE_FALSE);
        else Application::AddQuestion();	
    }
    else if (cmd == "insq") {
        if (command.hasArg("wr")) Application::InsertQuestion(Question::WRITTEN);
        else if (command.hasArg("mc")) Application::InsertQuestion(Question::MULTIPLE_CHOICE);
        else if (command.hasArg("tf")) Application::InsertQuestion(Question::TRUE_FALSE);
        else Application::InsertQuestion();	
    }
    else if (cmd == "listq") {
        if (command.hasArg("more")) Application::ListQuestions(true);
        else Application::ListQuestions(false);
    }
    else if (cmd == "editq") {
        Application::EditQuestion(command.hasArg("q"), command.hasArg("c"), command.hasArg("a"), -1);
    }
    else if (cmd == "delq") {
        Application::DeleteQuestion();
    }
    else if (cmd == "swapq") {
        Application::SwapQuestions();
    }
    else if (cmd == "take") {
        Application::TakeQuiz();
    }
    else if (cmd == "save") {
        Application::SaveQuiz();
    }
    else if (cmd == "load") {
        Application::LoadQuiz();
    }
}

std::string CommandHandler::GetErr() {
    return err;
}
