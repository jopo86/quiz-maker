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
    "root",
    "clr",
    "help",
    "docs",
    "create",
    "rename",
    "addq",
    "take",
    "save",
    "load"
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_ARGS = {
    { "quit!",  { "" } },
    { "q!",     { "" } },
    { "quit",   { "" } },
    { "q",      { "" } },
    { "root",   { "" } },
    { "clr",    { "" }},
    { "help",   { "more" } },
    { "docs",   { "" } },
    { "create", { "" } },
    { "rename", { "" } },
    { "addq",   { "mc", "wr", "tf" } },
    { "take",   { "autosect", "clr" } },
    { "save",   { "" } },
    { "load",   { "" } }
};

const std::map<std::string, std::vector<std::string>> CommandHandler::VALID_DIRS = {
    { "quit!",  DIR_ANY },
    { "q!",     DIR_ANY },
    { "quit",   DIR_ANY },
    { "q",      DIR_ANY },
    { "root",   DIR_ANY },
    { "clr",    DIR_ANY },
    { "help",   DIR_ANY },
    { "docs",   DIR_ANY},
    { "create", DIR_ROOT },
    { "rename", DIR_QUIZ },
    { "addq",   DIR_QUIZ },
    { "take",   DIR_QUIZ },
    { "save",   DIR_QUIZ },
    { "load",   DIR_ROOT }
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
        err += "'" + VALID_DIRS.at(cmd)[i] + "' ";
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
    else if (cmd == "create") {
        Application::CreateQuiz();
    }
    else if (cmd == "rename") {
        Application::RenameQuiz();
    }
    else if (cmd == "addq") {
        if (command.hasArg("mc")) Application::AddQuestionMC();
        else if (command.hasArg("wr")) Application::AddQuestionWR();
        else if (command.hasArg("tf")) Application::AddQuestionTF();
        else Application::AddQuestion();	
    }
    else if (cmd == "take") {
        if (command.hasArg("autosect") && command.hasArg("clr")) {
            Application::Clr();
            Application::TakeQuiz(true);
        }
        else if (command.hasArg("autosect")) Application::TakeQuiz(true);
        else if (command.hasArg("clr")) {
            Application::Clr();
            Application::TakeQuiz(false);
        }
        else Application::TakeQuiz(false);
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