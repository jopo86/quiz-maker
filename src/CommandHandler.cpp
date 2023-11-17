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
    "help",
    "create",
    "name",
    "addq",
    "take"
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_ARGS = {
    { "quit!",  { "" } },
    { "q!",     { "" } },
    { "quit",   { "" } },
    { "q",      { "" } },
    { "help",   { "more" } },
    { "create", { "" } },
    { "name",   { "" } },
    { "addq",   { "mc", "wr", "tf" } },
    { "take",   { "autosect" } }
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_DIRS = {
    { "quit!",  DIR_ANY },
    { "q!",     DIR_ANY },
    { "quit",   DIR_ANY },
    { "q",      DIR_ANY },
    { "help",   DIR_ANY },
    { "create", DIR_ROOT },
    { "name",   DIR_QUIZ },
    { "addq",   DIR_QUIZ },
    { "take",   DIR_QUIZ }
};

std::string CommandHandler::err = "";

bool CommandHandler::Verify(Command command) {
    std::string cmd = command.getCmd();
    std::vector<std::string> args = command.getArgs();


    // check if command exists
    bool exists = false;

    for (int i = 0; i < VALID_COMMANDS.size(); i++) {
        if (cmd == VALID_COMMANDS[i]) {
            exists = true;
        }
    }

    if (!exists) {
        err = "unrecognized command '" + cmd + "'\nUse 'help' to get a list of commands.";
        return false;
    }

    // check if command has valid args
    std::vector<bool> valid(args.size(), false);

    for (int i = 0; i < args.size(); i++) {
        for (int j = 0; j < VALID_ARGS.size(); j++) {
            if (args[i] == VALID_ARGS.at(cmd)[j]) {
                valid[i] = true;
            }
        }
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
    for (int i = 0; i < VALID_DIRS.at(cmd).size(); i++) {
        if (Application::GetDir() == VALID_DIRS.at(cmd)[i]) {
            return true;
        }
    }
    err = "command '" + cmd + "' can only be called from directory: ";
    for (int i = 0; i < VALID_DIRS.at(cmd).size(); i++) {
        err += "'" + VALID_DIRS.at(cmd)[i] + "' ";
    }
    err += "\nUse 'help -more' to get a list of commands with their valid directories.";
    return false;
}

void CommandHandler::Run(Command command) {
    std::string dir = Application::GetDir();
    std::string cmd = command.getCmd();

    if (cmd == "quit!" || cmd =="q!") {
        Application::ForceQuit();
    }
    else if (cmd == "quit" || cmd == "q") {
        Application::Quit();
    }
    else if (cmd == "help") {
        if (command.hasArg("more")) Application::HelpMore();
        else Application::Help();
    } 
    else if (cmd == "create") {
        Application::CreateQuiz();
    }
    else if (cmd == "name") {
        Application::NameQuiz();
    }
    else if (cmd == "addq") {
        if (command.hasArg("mc")) Application::AddQuestionMC();
        else if (command.hasArg("wr")) Application::AddQuestionWR();
        else if (command.hasArg("tf")) Application::AddQuestionTF();
        else Application::AddQuestion();	
    }
    else if (cmd == "take") {
        
    }
}

std::string CommandHandler::GetErr() {
    return err;
}